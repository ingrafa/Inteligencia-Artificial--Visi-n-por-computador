
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
    Mat imagenGaussiana;

    medianBlur(imagenRuido, imagenMediana, 3);
    GaussianBlur(imagenRuido, imagenGaussiana, Size(3, 3), 2.3, 2.3);

    namedWindow("Imagen", WINDOW_AUTOSIZE);
    namedWindow("Imagen Ruido Sal", WINDOW_AUTOSIZE);
    namedWindow("Imagen Mediana", WINDOW_AUTOSIZE);
    namedWindow("Imagen Gaussiana", WINDOW_AUTOSIZE);

    imshow("Imagen", imagen);
    imshow("Imagen Ruido Sal", imagenRuido);
    imshow("Imagen Mediana", imagenMediana);
    imshow("Imagen Gaussiana", imagenGaussiana);

    waitKey(0);

    // Liberamos recursos de memoria
    destroyAllWindows();

    // Detección de Bordes con el Operador de Sobel
    VideoCapture video("/dev/video33");
    if(video.isOpened()){
        Mat frame;
        Mat frameGris;

        Mat gx, gy, gxy;

        namedWindow("Video Original", WINDOW_AUTOSIZE);
        namedWindow("Gradiente X",WINDOW_AUTOSIZE);
        namedWindow("Gradiente Y", WINDOW_AUTOSIZE);
        namedWindow("Gradiente XY", WINDOW_AUTOSIZE);

        while(3==3){
            video >> frame;

            if (frame.empty()){
                break;
            }
            resize(frame,frame, Size(), 0.7, 0.7);
            cvtColor(frame, frameGris, COLOR_BGR2GRAY);

            Sobel(frameGris, gx, CV_64F, 1, 0, 5);
            Sobel(frameGris, gy, CV_64F, 0, 1, 5);
            Sobel(frameGris, gxy, CV_64F, 1, 1, 5);

            imshow("Video Original", frame);
            imshow("Gradiente X", gx);
            imshow("Gradiente Y", gy);
            imshow("Gradiente XY", gxy);

            if(waitKey(23)==27){
                break;
            }
        }
        video.release();
        destroyAllWindows();
    }

    return 0;
}
