
#include "Cabecera.hpp"

Persona::Persona(){
    cout << "Usando el constructor vacío" << endl;
}

Persona::Persona(string cedula, string nombres, double edad, bool activo){
    this->cedula = cedula;
    this->nombres = nombres;
    this->edad = edad;
    this->activo = activo;
}

void Persona::saludar(){
    cout << "Hola " << nombres << " edad: " << edad << " activo: " << activo << endl;
}

// 0 1 1 2 3 5 8 ...
void Persona::Fibonacci(int maximo){
    int a = 0;
    int b = 1;
    cout << a << " " << b << " ";
    int c = a+b;

    while (c<maximo){
        a = b;
        b = c;
        cout << c << " ";
        c = a + b;
    }

    cout << endl;
}


