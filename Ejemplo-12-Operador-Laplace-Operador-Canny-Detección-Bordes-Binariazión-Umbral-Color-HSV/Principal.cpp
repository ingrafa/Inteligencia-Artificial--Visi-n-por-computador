
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

int k = 1;
int t = 1;
int ds = 13;

// Variables que se declaran para binarizacion por umbral de color
int hMin = 0, sMin = 99, vMin = 94;
int hMax = 12, sMax = 255, vMax = 255;


// Función que se activará cada vez que se cambia el valor de la barra (trackbar)
void funcionTrackbar(int v, void *data){
    cout << "Valor: " << v << endl;
    if (t%2==1){
        k = t;
    }
}

void functionDS(int v, void *data){

}

void functionTrackHSV(int v, void *data){

}

int main(int argc, char *argv[]){

    // Detección de Bordes con el Operador de Sobel
    VideoCapture video("/dev/video33");
    if(video.isOpened()){
        Mat frame;
        Mat frameGris;
        Mat gaussiano;
        Mat laplaciano;
        Mat lapacianoPositivo;
        Mat canny;

        int minTreshold = 100;
        int ratio = 3;

        namedWindow("Video Original", WINDOW_AUTOSIZE);
        namedWindow("Gaussiano", WINDOW_AUTOSIZE);
        namedWindow("Gris", WINDOW_AUTOSIZE);
        namedWindow("Laplaciano", WINDOW_AUTOSIZE);
        namedWindow("Canny", WINDOW_AUTOSIZE);

        createTrackbar("Tamaño Kernel", "Video Original", &t, 50, funcionTrackbar, NULL);
        createTrackbar("Desviación Estándar", "Video Original", &ds, 100, functionDS, NULL);

        while(3==3){
            video >> frame;

            if (frame.empty()){
                break;
            }
            resize(frame,frame, Size(), 0.7, 0.7);
            cvtColor(frame, frameGris, COLOR_BGR2GRAY);

            equalizeHist(frameGris, frameGris);

            GaussianBlur(frameGris, gaussiano, Size(k,k), ds/10.0, ds/10.0);

            Laplacian(gaussiano, laplaciano, CV_16S, 3, 1);
            convertScaleAbs(laplaciano, lapacianoPositivo);

            Canny(gaussiano, canny, minTreshold, minTreshold*ratio, 3);

            imshow("Video Original", frame);
            imshow("Gaussiano", gaussiano);
            imshow("Gris", frameGris);
            imshow("Canny", canny);
            imshow("Laplaciano", lapacianoPositivo);

            if(waitKey(23)==27){
                break;
            }
        }
        video.release();
        destroyAllWindows();
    }


    // Binarización por umbral de color

    video = VideoCapture("/dev/video33");
    if(video.isOpened()){
        Mat frame;
        Mat frameHSV;
        Mat operacionAND;

        namedWindow("Video Original", WINDOW_AUTOSIZE);
        namedWindow("HSV", WINDOW_AUTOSIZE);
        namedWindow("Binaria", WINDOW_AUTOSIZE);
        namedWindow("AND", WINDOW_AUTOSIZE);

        createTrackbar("hMin", "Video Original", &hMin, 180, functionTrackHSV, NULL);
        createTrackbar("sMin", "Video Original", &sMin, 255, functionTrackHSV, NULL);
        createTrackbar("vMin", "Video Original", &vMin, 255, functionTrackHSV, NULL);

        createTrackbar("hMax", "Video Original", &hMax, 180, functionTrackHSV, NULL);
        createTrackbar("sMax", "Video Original", &sMax, 255, functionTrackHSV, NULL);
        createTrackbar("vMax", "Video Original", &vMax, 255, functionTrackHSV, NULL);

        Mat binaria;

        while(3==3){
            video >> frame;

            if (frame.empty()){
                break;
            }
            resize(frame,frame, Size(), 0.7, 0.7);
            cvtColor(frame, frameHSV, COLOR_BGR2HSV);

            inRange(frameHSV, Scalar(hMin,sMin,vMin), Scalar(hMax,sMax,vMax), binaria);

            operacionAND = Mat::zeros(frame.size(), CV_8UC3);

            bitwise_and(frame, frame, operacionAND, binaria);

            imshow("Video Original", frame);
            imshow("HSV", frameHSV);
            imshow("Binaria", binaria);
            imshow("AND", operacionAND);

            if(waitKey(23)==27){
                break;
            }
        }
        video.release();
        destroyAllWindows();
    }    

    return 0;
}
