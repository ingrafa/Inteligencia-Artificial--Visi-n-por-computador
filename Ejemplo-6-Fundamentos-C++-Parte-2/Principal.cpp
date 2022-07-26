
#include "Cabecera.hpp"

int main(int argc, char *argv[]){
    Persona p1();
    Persona p2 = Persona("0302879852", "ingrafa", 25.7, true);

    p2.saludar();
    p2.Fibonacci();

    string x = "23.3";
    stringstream ss;
    ss << x;
    double num = 0;
    ss >> num;

    cout << "Número: " << num << endl;

    bool r = p2.validarCedula("0104898721");

    cout << "Cédula Correcta: " << (r==true?"TRUE":"FALSE") << endl;

    vector<string> lista = p2.listarDirectory();

    for(string archivo:lista){
        cout << "=> " << archivo << endl;
    }

    return 0;
}



