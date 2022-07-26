
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

// Librerías de OpenCV
#include <opencv2/core/core.hpp> // Librería que contiene las definiciones base (matrices para representar imágenes, operaciones con matríces, etc.)
#include <opencv2/highgui.hpp> // Librería que permite crear ventanas y manejar eventos de ratón, teclado, etc.
#include <opencv2/imgcodecs.hpp> // Librería contiene los códecs para poder leer diferentes formatos de imágenes
#include <opencv2/imgproc.hpp> // Funciones para realizar procesamiento de imágenes digitales
#include <opencv2/video.hpp> // Funciones para lectura de vídeo
#include <opencv2/videoio.hpp> // Funciones para procesamiento de vídeo


using namespace std;
using namespace cv; // Espacio de nombres de funciones de OpenCV


Mat generarHistograma(Mat img){
    // Ejemplo de Cálculo del Histograma de la Imagen
    int histograma[256];
    for(int i=0;i<256;i++){
        histograma[i] = 0;
    }

    int pixelGris = 0;

    for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){
            pixelGris = img.at<uchar>(i,j);
            histograma[pixelGris]++;
        }
    }

    int maximo = 0;
    for(int i=0;i<256;i++){
        if(maximo<histograma[i])
            maximo = histograma[i];
    }    

    // Representación gráfica del histograma
    int ancho = 768;
    int alto = 640;
    Mat lienzo = Mat(Size(ancho, alto), CV_8UC3, Scalar(1,200,200));
    double escalaY = ((double)alto)/((double)maximo);
    double escalaX = ((double)ancho)/((double)256);

    for(int i=0;i<256;i++){
        line(lienzo, Point(i*escalaX,lienzo.rows),Point(i*escalaX,lienzo.rows-escalaY*histograma[i]), Scalar(100,1,1),1);
    }

    return lienzo;

}


int main(int argc, char *argv[]){

    // Matriz de m filas y n columnas que representa una imagen ya sea a color o en escala de grises
    Mat imagenOscura2 = imread("imagenes/Imagen-Oscura-2.png", IMREAD_GRAYSCALE);

    Mat imagenEcualizada2;
    Mat imagenEcualizadaCLAHE2;

    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(4);
    clahe->apply(imagenOscura2, imagenEcualizadaCLAHE2);

    // Ecualización de histograma de la imagen
    equalizeHist(imagenOscura2, imagenEcualizada2);


    Mat histoOriginal = generarHistograma(imagenOscura2);
    Mat histoEcualizada = generarHistograma(imagenEcualizada2);
    Mat histoCLAHE2 = generarHistograma(imagenEcualizadaCLAHE2);

    
    // Creamos una ventana donde se mostrará la imagen que se ha leído desde el disco
    namedWindow("Imagen Oscura 2", WINDOW_AUTOSIZE);
    namedWindow("Imagen Ecualizada 2", WINDOW_AUTOSIZE);
    namedWindow("Imagen Ecualizada CLAHE 2", WINDOW_AUTOSIZE);
    namedWindow("Histograma Original", WINDOW_AUTOSIZE);
    namedWindow("Histograma Ecualizado", WINDOW_AUTOSIZE);
    namedWindow("Histograma CLAHE", WINDOW_AUTOSIZE);

    imshow("Imagen Oscura 2", imagenOscura2);
    imshow("Imagen Ecualizada 2", imagenEcualizada2);
    imshow("Imagen Ecualizada CLAHE 2", imagenEcualizadaCLAHE2);
    imshow("Histograma Original", histoOriginal);
    imshow("Histograma Ecualizado", histoEcualizada);
    imshow("Histograma CLAHE", histoCLAHE2);

    // Pedimos al programa que espere hasta que el usuario presione cualquier tecla
    waitKey(0);

    // Liberamos recursos de memoria
    destroyAllWindows();

    return 0;
}
