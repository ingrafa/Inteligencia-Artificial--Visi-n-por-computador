
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

    Mat imagen = imread("Catedral-San-Basilio.jpg");
    resize(imagen, imagen, Size(), 0.7, 0.7);

    Mat gris;
    cvtColor(imagen, gris, COLOR_BGR2GRAY);

    Mat negativoImagen;
    Mat negativoGris;

    //negativoGris = 255-gris;
    bitwise_not(gris, negativoGris);
    bitwise_not(imagen, negativoImagen);
    
    // Creamos una ventana donde se mostrará la imagen que se ha leído desde el disco
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Gris", WINDOW_AUTOSIZE);
    namedWindow("Gris Negado", WINDOW_AUTOSIZE);
    namedWindow("Color Negado", WINDOW_AUTOSIZE);

    imshow("Original", imagen);
    imshow("Gris", gris);
    imshow("Gris Negado", negativoGris);
    imshow("Color Negado", negativoImagen);

    // Pedimos al programa que espere hasta que el usuario presione cualquier tecla
    waitKey(0);

    // Liberamos recursos de memoria
    destroyAllWindows();

    // Ejemplo sobre cómo acceder a la cámara
    //VideoCapture video(33);

    // Ejemplo sobre cómo abrir un vídeo en lugar de la cámara
    VideoCapture video("dogs.webm");

    Mat resta;
    Mat anterior;

    if(video.isOpened()){
        Mat frame;
        namedWindow("Video", WINDOW_AUTOSIZE);
        namedWindow("Resta", WINDOW_AUTOSIZE);

        while(3==3){
            video >> frame;

            if (frame.empty()){
                break;
            }

            flip(frame, frame, 1);

            cvtColor(frame, gris, COLOR_BGR2GRAY);

            if(anterior.empty()){
                anterior = gris.clone();
            }

            //resta = anterior - gris;
            cv::absdiff(anterior, gris, resta);

            imshow("Video", frame);
            imshow("Resta", resta);

            anterior = gris.clone();

            if(waitKey(23)==27){
                break;
            }
        }

        video.release();
        destroyAllWindows();
    }

    return 0;
}
