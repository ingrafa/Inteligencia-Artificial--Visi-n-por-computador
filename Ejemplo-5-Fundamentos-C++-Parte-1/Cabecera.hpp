
// Archivo de Cabecera:
// Contiene la declaración de una o más clases

// Con la palabra reservada "include" se cargan las cabeceras con funciones del sistema
// se usa los símbolos de mayor y menor que cuando son cabeceras del sistema
// Las cabeceras propias van entre comillas
#include <iostream>  // Funciones para leer del teclado y escribir en consola
#include <cstdio> // Funciones para manejo de memoria, conversiones de tipos de datos

#include <cstring> // Librería para usar cadenas de textos

// Cargamos el espacio de nombres para usarlos directamente en la clase
using namespace std; // Espacio de nombres con funciones estándar

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

}; // Se pone punto y coma, ya que en este archivo puede ir la declaración de varias clases