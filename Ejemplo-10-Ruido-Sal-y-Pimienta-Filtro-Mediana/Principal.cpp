
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

#include <ctime>
#include <random>

// Librerías de OpenCV
#include <opencv2/core.hpp> // Librería que contiene las definiciones base (matrices para representar imágenes, operaciones con matríces, etc.)
#include <opencv2/highgui.hpp> // Librería que permite crear ventanas y manejar eventos de ratón, teclado, etc.
#include <opencv2/imgcodecs.hpp> // Librería contiene los códecs para poder leer diferentes formatos de imágenes
#include <opencv2/imgproc.hpp> // Funciones para realizar procesamiento de imágenes digitales
#include <opencv2/video.hpp> // Funciones para lectura de vídeo
#include <opencv2/videoio.hpp> // Funciones para procesamiento de vídeo


using namespace std;
using namespace cv; // Espacio de nombres de funciones de OpenCV

int main(int argc, char *argv[]){

    // Matriz de m filas y n columnas que representa una imagen ya sea a color o en escala de grises
    Mat imagen = imread("Catedral-San-Basilio.jpg", IMREAD_GRAYSCALE);
    resize(imagen, imagen, Size(), 0.5, 0.5);

    float porcentaje = 0.15;

    int total = (int) (porcentaje*(float)(imagen.cols*imagen.rows));

    cout << "Se alterarán " << total << " de pixeles con ruido de sal" << endl;

    int cont = 0;
    srand((int) time(0));

    int fila = 0;
    int columna = 0;

    Mat imagenRuido = imagen.clone(); // Permite obtener una copia de la imagen original

    while(cont<total){
        fila = rand() % imagen.rows;
        columna = rand() % imagen.cols;

        imagenRuido.at<uchar>(fila,columna) = 255;
        cont++;
    }

    Mat imagenMediana;
    medianBlur(imagenRuido, imagenMediana, 3);

    namedWindow("Imagen", WINDOW_AUTOSIZE);
    namedWindow("Imagen Ruido Sal", WINDOW_AUTOSIZE);
    namedWindow("Imagen Mediana", WINDOW_AUTOSIZE);

    imshow("Imagen", imagen);
    imshow("Imagen Ruido Sal", imagenRuido);
    imshow("Imagen Mediana", imagenMediana);

    waitKey(0);

    // Liberamos recursos de memoria
    destroyAllWindows();

    return 0;
}

