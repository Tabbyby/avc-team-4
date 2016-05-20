//
// Created by Ishaq Idris on 20/05/16.
//

#include <stdio.h>
#include <time.h>

//these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int read_digital(int chan, int direct);
extern "C" int select_IO(int chan, int direct);
extern "C" int Sleep(int sec, int usec);

int minSpeed = 60;
double Kp = 0.237;
double Ki = 0.00;
double Kd = 0.072;
int First=1;
double sleepTime = 0.1;

//Variables
int w;
int sum;        //measure of whiteness
int errorR;     //error Rigth
int errorL;     //error left
int error;        //tot error

int prevError=0;
double propSignal;

int sumError;       //the sum of all previous errors

double derSignal;   //the derivitive signal
double intSignal;


int main(){
    //This sets up the RPi hardware and ensures
    //everything is working correctly
    init(0);
    //sets digital pin 0 as an input pin
    int select_IO(0, 0);
    int select_IO(2, 2);
    int select_IO(4, 4);
    //We declare an integer variable to store the digital sensor data
    //Reads from digital pin 0 (D0)
    int front = read_digital(0);
    int right = read_digital(1);
    int left = read_digital(2);
//    //Prints read digital value
//    printf("%d\n",digital_sensor_reading);
    //Waits for 0.5 seconds (500000 microseconds)
    int error = right -  left;
    if (error)
    Sleep(0,500000);
    return 0;}