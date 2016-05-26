//
// Created by Munke on 21-05-2016.
//

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include "Send120kHz.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <wiringPi.h>

void x10Interrupt();
/*
void SendSignal();*/
Send120kHz::Send120kHz(QWidget *parent) : QWidget(parent){

    //wiringPiISR (24, INT_EDGE_BOTH, &SendSignal);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPushButton *sendSignal = new QPushButton("120 kHz", this);
    brightness = new QLineEdit(this);
    brightness->setPlaceholderText("Skriv lysstyrke her - default 70%");
    QPushButton *stopSignal = new QPushButton("Off", this);
    QPushButton *getInt = new QPushButton("hent int", this);
    mainLayout->addWidget(brightness);
    mainLayout->addWidget(sendSignal);
    mainLayout->addWidget(stopSignal);
    mainLayout->addWidget(getInt);
    connect(sendSignal, &QPushButton::clicked, this, &Send120kHz::restartSignal);
    connect(stopSignal, &QPushButton::clicked, this, &Send120kHz::StopSignal);
    connect(getInt, &QPushButton::clicked, this, &Send120kHz::handleInputInt);
    setLayout(mainLayout);
   // int wiringPiISR(17,INT_EDGE_RISING,(x10Interrupt()));
}

/*void SendSignal() {
    printf("\nSendingSignal\n");

    if (!stopSending){
        if(x10CommunacationArray[x10Index] == 1){
            pwmWrite(18,5);
        } else{
            pwmWrite(18,0);
        }
        x10Index++;
    }

    if(x10Index == 29){
        stopSending = 1;
    }

    //
    //zeroCross();


}*/
int x10CommunacationArray[30] = {0};
void Send120kHz::StopSignal(){
    //pwmWrite(18,0);
    stopSending = 1;
}

void Send120kHz::restartSignal() {
    x10Index = 0;
    stopSending = 0;
}

int binaryIndex =0;
void Send120kHz::convertLightToX10(int lightLevel_) {
    if (lightLevel_ > 127) {
        return;
    }

    int dividedBy2 = 0;
    int level = lightLevel_;

    while (level > 0) {
        level = (int) level / 2;
        dividedBy2++;
    }
    int k =0;
    if(dividedBy2 < 7){
        for (; k < 6-dividedBy2; ++k) {
            binaryLightArray[k] = 0;
        }
    }
    level = lightLevel_;        // sørg for den ikke er nul mere
    while (level > 0) {
        binaryLightArray[k] = (level % 2);
        k++;
        level = (level/2);
    }
    printf("Dette er vores binaer light output: \n");
    for (int j = 0; j < 7; ++j) {
        printf("%d", binaryLightArray[j]);
    }

    printf("\n");

    int t = 0;
    for (int i = 0; i < 7; ++i, t+=2) {
        printf("i: %d\n", i);
        printf("t: %d\n", t);
        if(binaryLightArray[6-i] == 1){
            x10LightArray[13-t] = 0;
            x10LightArray[13-(t+1)] = 1;
        } else {
            x10LightArray[13-t] = 1;
            x10LightArray[13-(t+1)] = 0;
        }
    }
}



/*    binaryLightArray[6-binaryIndex] = (int) floor(lightLevel_%2);
    printf("\nLightLevel mod 2: %d\n", (int) floor(lightLevel_%2));
    ++binaryIndex;

    if(lightLevel_ > 0){
        printf("\nCalling convertLightToX10 with value: %d\n",(int)floor(lightLevel_/2) );
        convertLightToX10((int)floor(lightLevel_/2));
    }  else {
        int k = 0;
        printf("BinaryIndex: %d\n", binaryIndex);
        for (int i = 0; i <= binaryIndex; ++i, k+=2) {
            printf("i: %d\n", i);
            printf("k: %d\n", k);
            if(binaryLightArray[6-i] == 1){
                x10LightArray[13-k] = 0;
                x10LightArray[13-(k+1)] = 1;
            } else {
                x10LightArray[13-k] = 1;
                x10LightArray[13-(k+1)] = 0;
            }
        }

        binaryIndex = 0;
    }*/


void Send120kHz::handleInputInt() {
    input = brightness->text().toInt();

    getx10Communication(20,0,input);
    printf("\n");
    printf("Dette er x10signalet:");
    for (int i = 0; i <30 ; ++i) {
        x10Interrupt();
    }
    printf("\n");


/*
    printf("Værdier tilbage:\n");
    for (int i = 0; i <30 ; ++i) {
        printf("%d", x10CommunacationArray[i]);
    }
*/

/*    for (int j = 0; j <7 ; ++j) {
        binaryLightArray[j] = 0;
    }
    convertLightToX10(input);
    printf("\ninput: %d\n", input);
    printf("Binary coming out:\n");
    for (int i = 0; i <7 ; ++i) {
        printf("%d", binaryLightArray[i]);
    }
    printf("\n");

    printf("x10 coming out:\n");
    for (int i = 0; i <14 ; ++i) {
        printf("%d", x10LightArray[i]);
    }
    printf("\n");
*/

}

//int binaryUnitIndex = 0;
void Send120kHz::convertUnitToX10(int unitNumber) {
    if(unitNumber > 32){ // can't handle too big unitnumbers
        return;
    }

    int dividedBy2 = 0;
    int number = unitNumber;
    while (number > 0){             // How many steps into the array do we need to go to
        // get a correct binary 5 bit number ?
        number = (int) number/2;
        ++dividedBy2;
    }

    int j =0;
    if(dividedBy2 < 5){
        for (; j < 4-dividedBy2; ++j) {
            binaryUnitArray[j] = 0;
        }
    }

    number = unitNumber;
    while (number > 0){
        binaryUnitArray[dividedBy2-1] = number%2;
        ++dividedBy2;
        number = (number/2);
    }
    printf("Dette er vores binaer unit output: \n");
    for (int j = 0; j <5 ; ++j) {
        printf("%d", binaryUnitArray[j]);
    }
    printf("\n");

    int k = 0;
    for (int i = 0; i < 5; ++i, k+=2) {
        printf("i: %d\n", i);
        printf("k: %d\n", k);
        if(binaryUnitArray[4-i] == 1){
            x10UnitArray[9-k] = 0;
            x10UnitArray[9-(k+1)] = 1;
        } else {
            x10UnitArray[9-k] = 1;
            x10UnitArray[9-(k+1)] = 0;
        }
    }
}

void Send120kHz::getx10Communication(int unit, bool pir, int lightLevel) {
    for (int i = 0; i <3 ; ++i) { // place 111, for the start communation 1110
        x10CommunacationArray[i] = 1;
    }
    x10CommunacationArray[3] = 0;

    convertUnitToX10(unit);

    //Print the values

    printf("\nVaerdier for convertUnitToX10:\n");

    for (int m = 0; m < 10; ++m) {
        printf("%d", x10UnitArray[m]);
    }

    convertLightToX10(lightLevel);
    printf("\nVaerdier for convertLightToX10:\n");
    for (int n = 0; n < 14; ++n) {
        printf("%d", x10LightArray[n]);
    }
    printf("\n");

    int k = 0;
    for (int j = 4; j < 14; ++j, ++k) { // indsæt enhed
        x10CommunacationArray[j] = x10UnitArray[k];
    }

    // insert pir
    if(pir == 1){
        x10CommunacationArray[14] = 1;
        x10CommunacationArray[15] = 0;
    } else {
        x10CommunacationArray[14] = 0;
        x10CommunacationArray[15] = 1;
    }
    // insert lightlevel
    k = 0;
    for (int l = 16; l < 30; ++l, ++k) {
        x10CommunacationArray[l] = x10LightArray[k];
    }
printf("dette er x10 arrayet:");
    for (int q = 0; q <30 ; ++q) {
        printf("%d",x10CommunacationArray[q]);
    }
}
int x10interruptCount=0;

void x10Interrupt(){
    if(x10interruptCount>29){
        x10interruptCount=0;
    }
        if(x10CommunacationArray[x10interruptCount]==0){
            //digitalWrite(22,LOW);
            printf("0");
        }
        else if(x10CommunacationArray[x10interruptCount]==1){
            //digitalWrite(22,HIGH);
            printf("1");
        }
        x10interruptCount++;
    }