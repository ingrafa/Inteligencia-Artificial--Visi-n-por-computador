
// Archivo de Cabecera:
// Contiene la declaración de una o más clases

// Con la palabra reservada "include" se cargan las cabeceras con funciones del sistema
// se usa los símbolos de mayor y menor que cuando son cabeceras del sistema
// Las cabeceras propias van entre comillas
#include <iostream>  // Funciones para leer del teclado y escribir en consola
#include <cstdio> // Funciones para manejo de memoria, conversiones de tipos de datos

#include <cstring> // Librería para usar cadenas de textos

#include <vector> // Librería que permite crear arreglos que pueden agregar/eliminar elementos de forma dinámica

#include <cmath> // Librería que contiene las funciones matemáticas

#include <sstream> // Librería que permite convertir entre tipos de datos y representa un flujo de cadenas de texto

#include <experimental/filesystem>

// Cargamos el espacio de nombres para usarlos directamente en la clase
using namespace std; // Espacio de nombres con funciones estándar

namespace fs = std::experimental::filesystem;

class Persona{
    private:
        string cedula;
    
    public:
        string nombres;
        double edad;
        bool activo;
        Persona();
        Persona(string = "vacio", string = "vacio", double = 0.0, bool = false);
        void saludar();
        void Fibonacci(int = 500);
        bool validarCedula(string);
        vector<string> listarDirectory(string = "./");

}; // Se pone punto y coma, ya que en este archivo puede ir la declaración de varias clases