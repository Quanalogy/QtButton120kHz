//
// Created by Munke on 21-05-2016.
//

#ifndef QTBUTTON120KHZ_SEND120KHZ_H
#define QTBUTTON120KHZ_SEND120KHZ_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>

class Send120kHz : public QWidget{
    Q_OBJECT
public:
    Send120kHz(QWidget *parent =0);

private:
    void convertLightToX10(int lightLevel_);
    void convertUnitToX10(int unitNumber);
    QLineEdit *brightness;
    int binaryLightArray[7] = {0};   // a temp array for holding binary light level
    int binaryUnitArray[5] = {0};     // a temp array for holding binary unit number
    int input;
    int x10LightArray[14] = {0};
    int x10UnitArray[10] = {0};
    void getx10Communication(int unit, bool pir, int lightLevel);
    //void SendSignal();
    int x10CommunacationArray[30] = {0};
    int x10Index = 0;
    int stopSending = 1;
    //int *totalX10Communication;

public slots:
    void StopSignal();
    void restartSignal();
    void handleInputInt();

};


#endif //QTBUTTON120KHZ_SEND120KHZ_H
