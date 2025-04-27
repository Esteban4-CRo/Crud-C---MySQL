#pragma once // Asegura de que el archivo se incluya solo una vez cuando se compila

#include <iostream>  // Para std::cerr
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/connection.h"
#include "cppconn/prepared_statement.h"

// Conexión con la base de datos 
namespace Conexion
{
    // Función para abrir la conexión con la base de datos 
    inline sql::Connection* abrirConexion(const std::string& _db_name) {
        try {
            sql::Connection* conn = get_driver_instance()->connect(
                "tcp://127.0.0.1:3306",  // Especificar "tcp://" si es necesario
                "root",
                ""); // Si es necesario, agregar la contraseña aquí
            conn->setSchema(_db_name);
            return conn; // Devolvemos la conexión para usarla externamente
        }
        catch (sql::SQLException& e) { //Toma el error de SQLException y lo muestra al usuario, además se devuelve un puntero 
            //nulo en case de que no se pueda establecer la conexión 
            std::cerr << "Error de conexión: " << e.what() << std::endl;
            return nullptr; // Si la conexión falla, retornamos nullptr
        }
    }

    // Función para cerrar la conexión con la base de datos
    inline void cerrarConexion(sql::Connection*& _conn) {
        if (_conn) {
            if (!_conn->isClosed()) {
                _conn->close();
            }
            delete _conn; // Liberamos la memoria asignada al objeto conexión
            _conn = nullptr; // Establecemos el puntero a nullptr para evitar el acceso a memoria liberada
        }
    }

    // Estructura Cliente con 4 atributos de tipo string, inicializados como cadenas vacías
    struct Cliente
    {
        std::string nombre, di, contrasena, correo;

        // Constructor con atributos incializados
        Cliente(const std::string& _nombre = "",
            const std::string& _di = "",
            const std::string& _contrasena = "",
            const std::string& _correo = "")
            : nombre(_nombre), di(_di), contrasena(_contrasena), correo(_correo) {}

        // Sobrecarga del operador bool para verificar si todos los campos están llenos
        inline operator bool() const
        {
            return !nombre.empty() && !di.empty() && !contrasena.empty() && !correo.empty();
        }
    };

}
