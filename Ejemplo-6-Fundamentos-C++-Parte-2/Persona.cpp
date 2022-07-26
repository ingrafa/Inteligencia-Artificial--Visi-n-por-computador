
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

bool Persona::validarCedula(string cedula){
    int digito = 0;
    int suma = 0;
    for(int i=0;i<cedula.length()-1;i++){
        digito = ((int) cedula.at(i))-48;
        if(i%2==0)
            digito = (digito*2>9)?digito*2-9:digito*2;

        suma+=digito;
    }

    int residuo = suma%10!=0?10-suma%10:suma%10;

    digito = ((int) cedula.at(cedula.size()-1))-48;
    
    return residuo==digito;
}

vector<string> Persona::listarDirectory(string ruta){
    vector<string> listado;

    for(auto &entrada:fs::directory_iterator(ruta)){
        //cout << entrada.path() << endl;
        listado.push_back(entrada.path());
    }

    return listado;
}