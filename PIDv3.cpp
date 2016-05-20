#include <stdio.h>
#include <time.h>

//these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);
//extern "C" int ReadAnalog(int ch_adc);
extern "C" int set_motor(int motor , int speed);
//network commands
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

//Constants
int minSpeed = 50;
double Kp = 0.5;
double Ki = 0;
double Kd = 0;
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
//This sets up the RPi hardware and ensures everything is working properly
init(0);

connect_to_server("130.195.6.196", 1024);
//sends message
send_to_server("Please");
//receives message 
char message[24];
receive_from_server(message);
send_to_server(message);
Sleep(0,1000);
 //right wheel
 set_motor(1, minSpeed);
 // left wheel
 set_motor(2, minSpeed);

//infinite loop for testing purposes
while(true){
    //Take picture with camera
    take_picture();

    prevError = error; 
    error=0;
    errorR=0;   
    errorL=0;   
    sum=0;
    for (int i=0; i<160; i++){
        w = get_pixel(i, 120, 3);
        if(w > 100){
            errorL++;
        }
    }

    for (int i=0; i<320; i++){ 
     //this is calculating the sum for the whole width of pixels as opposed to just right, there is no range?
     // possibly the condition for the loop  should be
     //for (int i=0; i<320 && i>160; i++){
        w = get_pixel(i, 120, 3);
        if(w > 100){
            errorR++;
        }

    }

    error=errorR-errorL;
    

    //rests for 0.1 seconds
    Sleep(0,1000);
    sum=errorR+ErrorL;

    //when it reaches the secount quadrant
    if((sum)>300){
        First=0;
    }
    if((sum!=0)&&First==1){
        //Proportional Signal
        propSignal = (error)*Kp;
        propSignal=(propSignal/160)*200;
        //Integral Signal
        sumError += error;
        intSignal = (sumError*sleepTime)*Ki;

        //trial and error find an x value that works
        derSignal = ((error-preverror)/sleepTime)*Kd;

        //right wheel
        set_motor(1, minSpeed  - (propSignal + IntSignal + DerSignal));
        // left wheel
        set_motor(2, minSpeed + (propSignal + IntSignal + DerSignal));
    }else if(First==1){
        //turns until line is found.
        set_motor(1, -50);
        set_motor(2, 40);

        //when it reaches the intersections
    }else if((error>-20)&&(error<20)){
        //Proportional Signal
        propSignal = (error)*Kp;
        propSignal=(propSignal/160)*200;
        //Integral Signal
        sumError += error;
        intSignal = (sumError*sleepTime)*Ki;

        //trial and error find an x value that works
        derSignal = ((error-preverror)/sleepTime)*Kd;

        //right wheel
        set_motor(1, minSpeed  - (propSignal + IntSignal + DerSignal));
        // left wheel
        set_motor(2, minSpeed + (propSignal + IntSignal + DerSignal));
    }else if((errorL)>errorR+10){
        //turns90 left
        set_motor(2, (60);
        set_motor(1, (-40);
    }else if((errorL+10)<errorR){
        //turns90 right
        set_motor(2, (-40);
        set_motor(1, (60);
    }else{
        //finds the line again
        set_motor(1, 60);
        set_motor(2, -60);
    }

}
return 0;

}
