#pragma once
#include <vector>
#include "Conexxion.h"

namespace ModeloCliente {

    Conexion::Cliente consultarUsuario(const std::string& _di); // Declaración

    bool agregarUsuario(
        const std::string& _nombre,
        const std::string& _di,
        const std::string& _contrasena,
        const std::string& _correo
    ) {
        // Si alguno de los campos está vacío o ya existe un usuario con el mismo TI
        if (_nombre.empty() || _di.empty() || _contrasena.empty() || _correo.empty() || consultarUsuario(_di))
        {
            return false;  // Devolver 'false' si hay campos vacíos o el usuario ya existe
        }

        sql::Connection* conn = Conexion::abrirConexion("crud");  // Abrir conexión con la base de datos
        if (!conn) return false;

        try {
            sql::PreparedStatement* prep_statement = conn->prepareStatement(
                "INSERT INTO cliente(nombre, di, contrasena, correo) VALUES (?,?,?,?)"
            ); // Insertar datos en los campos de la bd

            prep_statement->setString(1, _nombre);
            prep_statement->setString(2, _di);
            prep_statement->setString(3, _contrasena);
            prep_statement->setString(4, _correo);

            bool result = prep_statement->executeUpdate() > 0;  // Si afectó al menos una fila

            prep_statement->close();
            delete prep_statement;

            Conexion::cerrarConexion(conn);  // Cerrar conexión con la base de datos

            return result;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Error en agregarUsuario: " << e.what() << std::endl;
            Conexion::cerrarConexion(conn);
            return false;
        }
    }

    bool actualizarUsuario(const Conexion::Cliente& _cliente) {
        sql::Connection* conn = Conexion::abrirConexion("crud");
        if (!conn) return false;

        try {
            sql::PreparedStatement* prep_statement = conn->prepareStatement(
                "UPDATE cliente SET nombre=?, contrasena=?, correo=? WHERE di=?"
            );

            prep_statement->setString(1, _cliente.nombre);
            prep_statement->setString(2, _cliente.contrasena);
            prep_statement->setString(3, _cliente.correo);
            prep_statement->setString(4, _cliente.di);

            bool result = prep_statement->executeUpdate() > 0;

            prep_statement->close();
            delete prep_statement;

            Conexion::cerrarConexion(conn);
            return result;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Error en actualizarUsuario: " << e.what() << std::endl;
            Conexion::cerrarConexion(conn);
            return false;
        }
    }

    bool eliminarUsuario(const std::string& _di) {
        sql::Connection* conn = Conexion::abrirConexion("crud");
        if (!conn) return false;

        try {
            sql::PreparedStatement* prep_statement = conn->prepareStatement(
                "DELETE FROM cliente WHERE di=?"
            );
            prep_statement->setString(1, _di);

            bool result = prep_statement->execute();  // execute() devuelve un valor booleano

            prep_statement->close();
            delete prep_statement;

            Conexion::cerrarConexion(conn);
            return result;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Error en eliminarUsuario: " << e.what() << std::endl;
            Conexion::cerrarConexion(conn);
            return false;
        }
    }

    Conexion::Cliente consultarUsuario(const std::string& _di) {
        Conexion::Cliente cliente = {};

        // Si no tiene TI, devolvemos un cliente vacío
        if (_di.empty())
        {
            return cliente;
        }

        sql::Connection* conn = Conexion::abrirConexion("crud");
        if (!conn) return cliente;

        try {
            sql::PreparedStatement* prep_statement = conn->prepareStatement(
                "SELECT nombre, di, contrasena, correo FROM cliente WHERE di=?"
            );
            prep_statement->setString(1, _di);  // Corregido el índice a 1

            sql::ResultSet* rest_set = prep_statement->executeQuery();

            if (rest_set->next()) {
                cliente = {
                    rest_set->getString("nombre"),
                    rest_set->getString("di"),
                    rest_set->getString("contrasena"),
                    rest_set->getString("correo")
                };
            }

            rest_set->close();
            delete rest_set;
            prep_statement->close();
            delete prep_statement;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Error en consultarUsuario: " << e.what() << std::endl;
        }

        Conexion::cerrarConexion(conn);
        return cliente;
    }


    // Declaración de la nueva función para obtener todos los clientes 
    std::vector<Conexion::Cliente> obtenerTodosLosUsuarios();

    // Implementación de la función
    std::vector<Conexion::Cliente> obtenerTodosLosUsuarios() {
        std::vector<Conexion::Cliente> clientes;

        sql::Connection* conn = Conexion::abrirConexion("crud");
        if (!conn) return clientes;

        try {
            sql::PreparedStatement* prep_statement = conn->prepareStatement(
                "SELECT nombre, di, contrasena, correo FROM cliente"
            );

            sql::ResultSet* rest_set = prep_statement->executeQuery();

            while (rest_set->next()) {
                Conexion::Cliente cliente = {
                    rest_set->getString("nombre"),
                    rest_set->getString("di"),
                    rest_set->getString("contrasena"),
                    rest_set->getString("correo")
                };
                clientes.push_back(cliente);
            }

            rest_set->close();
            delete rest_set;
            prep_statement->close();
            delete prep_statement;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Error al obtener todos los usuarios: " << e.what() << std::endl;
        }

        Conexion::cerrarConexion(conn);
        return clientes;
    }

}
