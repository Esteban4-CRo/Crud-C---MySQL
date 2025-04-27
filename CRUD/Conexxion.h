#pragma once // Asegura de que el archivo se incluya solo una vez cuando se compila

#include <iostream>  // Para std::cerr
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/connection.h"
#include "cppconn/prepared_statement.h"

// Conexi�n con la base de datos 
namespace Conexion
{
    // Funci�n para abrir la conexi�n con la base de datos 
    inline sql::Connection* abrirConexion(const std::string& _db_name) {
        try {
            sql::Connection* conn = get_driver_instance()->connect(
                "tcp://127.0.0.1:3306",  // Especificar "tcp://" si es necesario
                "root",
                ""); // Si es necesario, agregar la contrase�a aqu�
            conn->setSchema(_db_name);
            return conn; // Devolvemos la conexi�n para usarla externamente
        }
        catch (sql::SQLException& e) { //Toma el error de SQLException y lo muestra al usuario, adem�s se devuelve un puntero 
            //nulo en case de que no se pueda establecer la conexi�n 
            std::cerr << "Error de conexi�n: " << e.what() << std::endl;
            return nullptr; // Si la conexi�n falla, retornamos nullptr
        }
    }

    // Funci�n para cerrar la conexi�n con la base de datos
    inline void cerrarConexion(sql::Connection*& _conn) {
        if (_conn) {
            if (!_conn->isClosed()) {
                _conn->close();
            }
            delete _conn; // Liberamos la memoria asignada al objeto conexi�n
            _conn = nullptr; // Establecemos el puntero a nullptr para evitar el acceso a memoria liberada
        }
    }

    // Estructura Cliente con 4 atributos de tipo string, inicializados como cadenas vac�as
    struct Cliente
    {
        std::string nombre, di, contrasena, correo;

        // Constructor con atributos incializados
        Cliente(const std::string& _nombre = "",
            const std::string& _di = "",
            const std::string& _contrasena = "",
            const std::string& _correo = "")
            : nombre(_nombre), di(_di), contrasena(_contrasena), correo(_correo) {}

        // Sobrecarga del operador bool para verificar si todos los campos est�n llenos
        inline operator bool() const
        {
            return !nombre.empty() && !di.empty() && !contrasena.empty() && !correo.empty();
        }
    };

}
