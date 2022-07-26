
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

#include <ctime>
#include <random>

// Librerías de OpenCV
#include <opencv2/core/core.hpp> // Librería que contiene las definiciones base (matrices para representar imágenes, operaciones con matríces, etc.)
#include <opencv2/highgui/highgui.hpp> // Librería que permite crear ventanas y manejar eventos de ratón, teclado, etc.
#include <opencv2/imgcodecs/imgcodecs.hpp> // Librería contiene los códecs para poder leer diferentes formatos de imágenes
#include <opencv2/imgproc/imgproc.hpp> // Funciones para realizar procesamiento de imágenes digitales
#include <opencv2/video/video.hpp> // Funciones para lectura de vídeo
#include <opencv2/videoio/videoio.hpp> // Funciones para procesamiento de vídeo


using namespace std;
using namespace cv; // Espacio de nombres de funciones de OpenCV

int k = 1;
int t = 1;
int ds = 13;

// Variables que se declaran para binarizacion por umbral de color
int hMin = 163, sMin = 108, vMin = 6;
int hMax = 180, sMax = 224, vMax = 212;


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


double huMomentsEstrella[7] = {
    0.20355, 0.000112557, 0.000897011, 0.000255594, -1.21691e-07, -1.23902e-06, 1.30084e-08
};


double distanciaEuclidea(double momentosHu[7]){
    double d = 0;
    for(int i=0;i<7;i++){
        d+=(momentosHu[i]-huMomentsEstrella[i])*(momentosHu[i]-huMomentsEstrella[i]);
    }

    return sqrt(d);
}



int main(int argc, char *argv[]){

   

    // Binarización por umbral de color

    VideoCapture video = VideoCapture("/dev/video33");
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

        double huMoments[7];
        Moments momentosRaw;
        double cx = 0, cy = 0;
        double dis = 0;

        while(3==3){
            video >> frame;

            if (frame.empty()){
                break;
            }
            resize(frame,frame, Size(), 0.7, 0.7);
            cvtColor(frame, frameHSV, COLOR_BGR2HSV);

            inRange(frameHSV, Scalar(hMin,sMin,vMin), Scalar(hMax,sMax,vMax), binaria);

            momentosRaw = moments(binaria, true);

            cx = momentosRaw.m10/momentosRaw.m00;
            cy = momentosRaw.m01/momentosRaw.m00;

            //cout << "Area: " << momentosRaw.m00 << endl;

            HuMoments(momentosRaw, huMoments);


            /*
            for (int i=0;i<7;i++){
                cout << "Hu[" << i << "] = " << huMoments[i] << endl;
            }
            */

            if (momentosRaw.m00 > 100){
                
                dis = distanciaEuclidea(huMoments);
                
                if (dis < 0.01){
                    circle(frame, Point(cx,cy), 3, Scalar(10,10,200), 3);
                    putText(frame, "Estrella", Point(cx, cy), FONT_HERSHEY_COMPLEX, 1, Scalar(200, 10, 10));
                }

            }



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
