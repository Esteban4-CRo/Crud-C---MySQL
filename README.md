# CRUD C++ - MySQL

Configuración de MySQL Connector/C++ 8.3.0 en Visual Studio
Requisitos
Tener instalado MySQL Connector/C++ 8.3.0.

Visual Studio instalado en el sistema.

Proyecto C++ creado.

Pasos de Configuración
1. Descargar el Conector
Ir a la página de MySQL Community Downloads.

Seleccionar Connector/C++.

Descargar la versión 8.3.0 compatible con la arquitectura de tu sistema operativo (32 o 64 bits).

2. Copiar Carpetas Necesarias
Una vez descargado el conector, copiar las carpetas include y lib64.

Pegarlas en el directorio donde se encuentra tu proyecto, dentro de una carpeta llamada MySQL.

3. Copiar Librerías de OpenSSL
Copiar los archivos libcrypto-3-x64.dll y libssl-3-x64.dll.

Pegarlos en las carpetas x64/Release de tu proyecto (fuera de la carpeta MySQL).

4. Ajustar el Compilador en Visual Studio
Agregar un nuevo archivo .cpp al proyecto para que Visual Studio detecte el proyecto como C++.

Hacer clic derecho sobre el nombre del proyecto → Propiedades.

En C/C++:
Ir a General → Directorios de inclusión adicionales.

Agregar la ruta a MySQL/include/jdbc.

En Preprocesador:
Definir la constante STATIC_CONCPP.

5. Configurar el Vinculador
En General:
Agregar en Directorios de bibliotecas adicionales la ruta: MySQL/lib64/vs14.

En Entrada:

Agregar en Dependencias adicionales:
mysqlcppconn-static.lib

Importante: Asegúrate de que el proyecto esté en modo Release.
Si está en modo Debug, pueden aparecer errores de vinculación.
