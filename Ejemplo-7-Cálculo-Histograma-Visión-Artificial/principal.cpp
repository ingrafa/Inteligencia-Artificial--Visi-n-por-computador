
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

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
    Mat imagen = imread("Catedral-San-Basilio.jpg");

    // Leer la imagen en escala de grises
    Mat gris = imread("Catedral-San-Basilio.jpg", IMREAD_GRAYSCALE);

    // Cómo escalar una imagen
    resize(imagen, imagen, Size(), 0.5, 0.5);
    resize(gris, gris, Size(), 0.5, 0.5);

    // Creamos una ventana donde se mostrará la imagen que se ha leído desde el disco
    namedWindow("VentanaI", WINDOW_AUTOSIZE);
    namedWindow("Gris", WINDOW_AUTOSIZE);
    namedWindow("Gris Manual", WINDOW_AUTOSIZE);
    namedWindow("Gris Formula", WINDOW_AUTOSIZE);
    namedWindow("Gris Funcion", WINDOW_AUTOSIZE);

    // Obtener características de la imagen
    cout << "Columnas: " << imagen.cols << " Filas: " << imagen.rows << " Canales: " << imagen.channels() << endl;

    // Manipulación de pixeles
    // Leer el pixel central de la imagen a color
    Vec3b pixelColor = imagen.at<Vec3b>(imagen.rows/2, imagen.cols/2);
    cout << "Azul: " << (int) pixelColor[0] << "| Verde: " << (int) pixelColor[1] << "| Rojo: " << (int) pixelColor[2] << endl;

    // Conversión Manual de una imagen a color en escala de grises
    Mat grisManual = Mat::zeros(Size(imagen.cols, imagen.rows), CV_8UC1);
    Mat grisFormula = Mat::zeros(Size(imagen.cols, imagen.rows), CV_8UC1);

    for(int i=0;i<imagen.rows;i++){
        for(int j=0;j<imagen.cols;j++){
            pixelColor = imagen.at<Vec3b>(i,j);

            grisManual.at<uchar>(i,j) = (pixelColor[0]+pixelColor[1]+pixelColor[2])/3;
            // Formula que considera la percepción relativa de personas con respecto a los colores
            // rojo, verde y azul:
            // Gris = 0.299*Rojo+0.587*Verde+0.114*Azul
            grisFormula.at<uchar>(i,j) = 0.299*pixelColor[2]+0.587*pixelColor[1]+0.114*pixelColor[0];
        }
    }

    // Función propia de OpenCV para convertir entre espacios de color
    Mat grisFuncion;
    cvtColor(imagen, grisFuncion, COLOR_BGR2GRAY);


    // Ejemplo de cómo graficar primitivas en OpenCV
    line(grisManual, Point(10,10), Point(100,100), Scalar(255), 7);


    // Visualizamos la imagen en la ventana
    imshow("VentanaI", imagen);
    imshow("Gris", gris);
    imshow("Gris Manual", grisManual);
    imshow("Gris Formula", grisFormula);
    imshow("Gris Funcion", grisFuncion);

    // Cómo guardar una imagen en el disco
    imwrite("Gris.png", grisFuncion);

    // Ejemplo de Cálculo del Histograma de la Imagen
    int histograma[256];
    for(int i=0;i<256;i++){
        histograma[i] = 0;
    }

    int pixelGris = 0;

    for(int i=0;i<grisFuncion.rows;i++){
        for(int j=0;j<grisFuncion.cols;j++){
            pixelGris = grisFuncion.at<uchar>(i,j);
            histograma[pixelGris]++;
        }
    }

    int maximo = 0;
    for(int i=0;i<256;i++){
        cout << histograma[i] << ";";
        if(maximo<histograma[i])
            maximo = histograma[i];
    }
    cout << endl;

    // Representación gráfica del histograma
    int ancho = 768;
    int alto = 640;
    Mat lienzo = Mat(Size(ancho, alto), CV_8UC3, Scalar(1,200,200));
    double escalaY = ((double)alto)/((double)maximo);
    double escalaX = ((double)ancho)/((double)256);

    for(int i=0;i<256;i++){
        line(lienzo, Point(i*escalaX,lienzo.rows),Point(i*escalaX,lienzo.rows-escalaY*histograma[i]), Scalar(100,1,1),1);
    }

    namedWindow("Lienzo", WINDOW_AUTOSIZE);
    imshow("Lienzo", lienzo);

    imwrite("Histograma.png", lienzo);

    // Pedimos al programa que espere hasta que el usuario presione cualquier tecla
    waitKey(0);

    // Liberamos recursos de memoria
    destroyAllWindows();

    return 0;
}

