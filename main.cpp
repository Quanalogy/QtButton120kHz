#include <QtWidgets/QApplication>
#include "Send120kHz.h"
/*
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
*/

//void sendSignal();
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    printf ("Raspberry Pi wiringPi test program\n") ;
/*    if (wiringPiSetupGpio() == -1){
        exit (1) ;
    }
    pinMode(18,PWM_OUTPUT);
    pwmSetClock(80);
    pwmSetRange (10);*/

    Send120kHz mainLayout;

    //pwmWrite(18,5);

    mainLayout.show();

    return app.exec();
}
/*

void sendSignal(){
    printf("\nsendSignal\n");
    mainLayout.SendSignal();
}*/
