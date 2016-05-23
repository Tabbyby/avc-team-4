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
int minSpeed = 60;
double Kp = 0.237;
double Ki = 0.00;
double Kd = 0.072;
int First=1;
double sleepTime = 0.1; 

//Variables
int w;  
int r;
int red;
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

//connect_to_server("130.195.6.196", 1024);
//sends message
//send_to_server("Please");
//receives message 
//char message[24];
//receive_from_server(message);
//send_to_server(message);
//Sleep(0,1000);
 //right wheel
 set_motor(1, minSpeed);
 // left wheel
 set_motor(2, minSpeed);

//infinite loop for testing purposes
while(true){
    //Take picture with camera
    take_picture();
    int display_picture(int 1,int 1);//displays pictures
    prevError = error; 
    error=0;
    errorR=0;   
    errorL=0;   
    sum=0;
    r=0;
    red=0;
    for (int i=0; i<160; i++){
        w = get_pixel(i, 120, 3);
        r = get_pixel(i, 120, 255,0,0);
        if(w > 120){
            errorL++;
        }else if(r>250){
        	red++;	
        }
        }
    }

    for (int i=160; i<320; i++){ 
     //this is calculating the sum for the whole width of pixels as opposed to just right, there is no range?
     // possibly the condition for the loop  should be
     //for (int i=0; i<320 && i>160; i++){
        w = get_pixel(i, 120, 3);
        r = get_pixel(i, 120, 255,0,0);
        if(w > 120){
            errorR++;
        }else if(r>250){
        	red++;	
        }

    }

    error=errorR-errorL;
    

    //rests for 0.1 seconds
    Sleep(0,1000);
    sum=errorR+errorL;

    //when it reaches the secount quadrant
    if((sum)>310){ //this could be made true when doing the first set of curves, causing it to break into the 
       First=0;   //intersection code
	minSpeed=80;
    }
    if (red>310){
    	First=2;
    }
    }
    if((sum>10)&&First==1){
        //Proportional Signal
        propSignal = (error)*Kp;
        propSignal=(propSignal/160)*200;
        //Integral Signal
        sumError += error;
        intSignal = (sumError)*Ki;

        //trial and error find an x value that works
        derSignal = ((error-prevError)/sleepTime)*Kd;

        //right wheel
        set_motor(1, minSpeed  + (propSignal + intSignal + derSignal));
        // left wheel
        set_motor(2, minSpeed - (propSignal + intSignal + derSignal));
    }else if(First==1){ //Do we need this, this could be causing the initial spin
        //turns until line is found.
        set_motor(1, -50);
        set_motor(2, -60);

        //when it reaches the intersections
    }else if((error>-20)&&(error<20)&&First==0&&sum>10){
        //Proportional Signal
        propSignal = (error)*Kp;
        propSignal=(propSignal/160)*200;
        //Integral Signal
        sumError += error;
        intSignal = (sumError)*Ki;

        //trial and error find an x value that works
        derSignal = ((error-prevError)/sleepTime)*Kd;

        //right wheel
        set_motor(1, minSpeed  - (propSignal + intSignal + derSignal));
        // left wheel
        set_motor(2, minSpeed + (propSignal + intSignal + derSignal));
    }else if(((errorL)>errorR+1)&&First==0){
        //turns90 left
        set_motor(2, 70);
        set_motor(1, -40);
    }else if(((errorL+1)<errorR)&&First==0){
        //turns90 right
        set_motor(2, -40);
        set_motor(1, 70);
    }else{
        //finds the line again
        set_motor(1,-60);
        set_motor(2, 60);
    }

}
return 0;

}
