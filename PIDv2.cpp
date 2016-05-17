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
int maxSpeed = 200;
int Kp = 50;
double maxP = 160;
int Ki = 0;
double maxI = 10;
int Kd = 0;
double maxD = 10;
int sleepTime = 0.1;	//seconds

//Variables
int w;			//measure of whiteness
int error;		//sum of white pixel locations
int counter;		//number of "white" pixels
int avError = 0;	//sum of white pixel locations/number of white pixels
double propSignal;	//the proportional signal somewhere between 0 - Kp

int sumError;		//the sum of all previous errors
double integral;

int preError;		//error from previous iteration of loop
double deltaError;	//rate of change of error
double derSignal;	//the derivitive signal 

int main(){
	//This sets up the RPi hardware and ensures everything is working properly
	init(0);

	//infinite loop for testing purposes
	while(true){
		//Take picture with camera
		take_picture();
		
		preError = avError;
		counter = 0;
		error = 0;
		for (int i=0; i<320; i++){
			w = get_pixel(i, 120, 3);
			if(w > 200){
				error += (i-160);
				counter++;
				
			}

		}
		//rests for 0.1 seconds
		Sleep(0,(1000000*sleepTime));
		
		
		//Proportional Signal
		if(couter!=0){
		avError = error/counter;
		propSignal = (avError/maxP)*Kp;
		
		if(propSignal>Kp){	//ensures the propSignal between 0 - Kp
			propSignal = Kp;
			
		}
		
		//Integral Signal
		sumError += avError;
		integral = sumError*sleepTime;
		intSignal = (integral/maxI)*Ki;
		
		if(intSignal>Ki){	//ensures the intSignal between 0 - Ki
			printf("intSignal: %d", intSignal);
			intSignal = Ki;
			
		}
		
		//Derivative Signal
		deltaError = (avError - preError)/(sleepTime);
		//x should be the maximum value of deltaError
		//trial and error find an x value that works
		derSignal = (deltaError/maxD)*Kd;
		
		if(derSignal>Kd){	//ensures the derSignal between 0 - Kd
			printf("derSignal: %d", derSignal);
			derSignal = Kd;
			
		}
		
		//not sure which wheel is which
		//assumes positive is forwards
		//should be right wheel
		set_motor(1, ((maxSpeed - (Kp + Ki + Kd)) - (propSignal + IntSignal + DerSignal));
		//should be left wheel
		set_motor(2, ((maxSpeed - (Kp + Ki + Kd)) + (propSignal + IntSignal + DerSignal));
		}else{
		//turns until line is found.
		set_motor(1, -40);
		set_motor(2, 40);
		}
		}

	}
	return 0;

}
