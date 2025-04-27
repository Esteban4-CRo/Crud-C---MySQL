#include <iostream>
#include <locale.h>
#include "ModeloCliente.h"
#include <vector>
using namespace std;

int main(void) {
    int opc;
    setlocale(LC_ALL, "spanish");

    do {
        cout << "------------ MENÚ ------------" << endl;
        cout << "1. Agregar" << endl;
        cout << "2. Insertar nuevos datos" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Mostrar todos los usuarios" << endl;  
        cout << "5. Salir" << endl;
        cout << "Por favor digite la opción que desea realizar [1-5]: " << endl;
        cin >> opc;
        cin.ignore();

        switch (opc) {
        case 1: {
            char nombre[50] = {}, di[11] = {}, contrasena[15] = {}, correo[50] = {};
            cout << "-------------- REGISTRO --------------" << endl;
            cout << "Nombre: " << endl;
            cin.getline(nombre, 50);
            cout << "TI: " << endl;
            cin.getline(di, 10);
            cout << "Contraseña: " << endl;
            cin.getline(contrasena, 15);
            cout << "Correo: " << endl;
            cin.getline(correo, 50);

            cout << (ModeloCliente::agregarUsuario(nombre, di, contrasena, correo) ?
                "Cliente agregado\n" :
                "Error al agregar\n");

            break;
        }
        case 2: {
            char di[11] = { 0 };
            int menu;
            char nombre[50] = {}, contrasena[15] = {}, correo[50] = {};
            cout << "Ingrese el TI del cliente: " << endl;
            cin.getline(di, 11);

            Conexion::Cliente cliente;

            if (!(cliente = ModeloCliente::consultarUsuario(di))) {  // Verificar si el cliente no existe
                cout << "El cliente no está registrado." << endl;
                break;
            }

            do {
                cout << "------ DATOS DEL USUARIO ------" << endl; 
                cout << "\n1. Nombre: " << cliente.nombre
                    << "\n2. Contraseña: " << cliente.contrasena
                    << "\n3. Correo: " << cliente.correo
                    << "\n4. Salir"
                    << "\n Ingrese la opción a realizar [1-4]: " << endl;
                cin >> menu;
                cin.ignore();

                switch (menu) {
                case 1:
                    cout << "Ingrese el nuevo nombre: " << endl;
                    cin.getline(nombre, 50);
                    cliente.nombre = nombre;
                    break;
                case 2:
                    cout << "Ingrese la nueva contraseña: " << endl;
                    cin.getline(contrasena, 15);
                    cliente.contrasena = contrasena;
                    break;
                case 3:
                    cout << "Ingrese el nuevo correo: " << endl;
                    cin.getline(correo, 50);
                    cliente.correo = correo;
                    break;
                case 4:
                    cout << "Saliendo del menú de actualización." << endl;
                    break;
                default:
                    cout << "Usted seleccionó una opción no válida." << endl;
                    break;
                }
            } while (menu != 4);

            cout << (ModeloCliente::actualizarUsuario(cliente) ? "Cliente actualizado\n" : "Error al actualizar\n");
            break;
        }
        case 3: {
            char di[11] = {};
            cout << "Ingrese el TI del cliente a eliminar: " << endl;
            cin.getline(di, 10);
            cout << (ModeloCliente::eliminarUsuario(di) ? "Cliente eliminado\n" : "Error al eliminar\n") << endl;
            break;
        }
        case 4: {
            vector<Conexion::Cliente> usuarios = ModeloCliente::obtenerTodosLosUsuarios();
            if (usuarios.empty()) {
                cout << "No hay usuarios registrados." << endl;
            }
            else {
                cout << "----- Todos los Usuarios -----" << endl;
                for (const auto& usuario : usuarios) {
                    cout << "Nombre: " << usuario.nombre << "\n"
                        << "TI: " << usuario.di << "\n"
                        << "Correo: " << usuario.correo << "\n"
                        << "----------------------------\n";
                }
            }
            break;
        }
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Usted digitó una opción incorrecta." << endl;
            break;
        }
    } while (opc != 5);

    return 0;
}
