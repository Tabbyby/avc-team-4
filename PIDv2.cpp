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
int maxSpeed = 90;	//maximum speed of any one wheel
int Kp = 40;
double maxP = 160;	//maximum value of the proportional signal
int Ki = 0;
double maxI = 10;	//maximum value of the integral signal
int Kd = 0;
double maxD = 50;	//maximum derivitive signal
int sleepTime = 0.1;	//seconds
int whiteThresh = 100	//the lowest whiteness value that is considered a white pixel

//Variables
int w;			//measure of whiteness
int error;		//sum of white pixel locations
int counter;		//number of "white" pixels
int avError = 0;	//sum of white pixel locations/number of white pixels
double propSignal;	//the proportional signal somewhere between 0 - Kp

int sumError;		//the sum of all previous errors
double integral;	//the integral of the current sum of errors

int preError;		//error from previous iteration of loop
double deltaError;	//rate of change of error
double derSignal;	//the derivitive signal 

int main(){
	//This sets up the RPi hardware and ensures everything is working properly
	init(0);
	
	//connects to server
	connect_to_server("192.168.1.2", 1024);
	//sends message
   	send_to_server("Please");
   	//receives password
   	char message[24];
   	receive_from_server(message);
   	//sends password back to server
   	send_to_server(message);
   	//wait for door to open
   	Sleep(0,3000);

	//infinite loop for testing purposes
	while(true){
		//Take picture with camera
		take_picture();
		
		preError = avError;
		counter = 0;
		error = 0;
		for (int i=0; i<320; i++){
			w = get_pixel(i, 120, 3);
			if(w > whiteThresh){
				error += (i-160);
				counter++;
				
			}

		}
		//rests for 0.1 seconds
		Sleep(0,(1000000*sleepTime));
		
		
		if(counter!=0){
			//Proportional Signal
			avError = error/counter;
			propSignal = (avError/maxP)*Kp;
			if(propSignal>Kp){	//ensures the propSignal between -Kp and Kp
				propSignal = Kp;
				
			}else if(propSignal < (-1*Kp)){
				propSignal = -1*Kp;
				
			}
			
			//Integral Signal
			sumError += avError;
			integral = sumError*sleepTime;
			intSignal = (integral/maxI)*Ki;
			if(intSignal>Ki){	//ensures the intSignal between -Ki and Ki
				printf("intSignal: %d", intSignal);
				intSignal = Ki;
				
			}else if(intSignal < (-1*Ki)){
				intSignal = -1*Ki;
				
			}
			
			//Derivative Signal
			deltaError = (avError - preError)/(sleepTime);
			derSignal = (deltaError/maxD)*Kd;
			if(derSignal>Kd){	//ensures the derSignal between -Kd and Kd
				printf("derSignal: %d", derSignal);
				derSignal = Kd;
				
			}else if(derSignal<(-1*Kd)){
				derSignal = -1*Kd;
				
			}
	
			//Right wheel
			set_motor(2, ((maxSpeed - (Kp + Ki + Kd)) - (propSignal + IntSignal + DerSignal));
			//Left wheel
			set_motor(1, ((maxSpeed - (Kp + Ki + Kd)) + (propSignal + IntSignal + DerSignal));
		}else{
			//reverses until line is found.
			set_motor(1, -(maxSpeed - (Kp + Ki + Kd)));
			set_motor(2, -(maxSpeed - (Kp + Ki + Kd)));
		}

	}
	return 0;

}

int turnAround(){
	bool found = false;
	int whiteCount = 0;
	
	while(!found){
		set_motor(1, 20);
		set_motor(2, -20);
		take_picture();
		for (int i=0; i<320; i++){
			w = get_pixel(i, 120, 3);
			if(w > whiteThresh){
				whiteCount++;
			}
			if(whiteCount>5){
				found = true;
				set_motor(1, 0);
				set_motor(2, 0);
				break;
			}

		}
		
	}
	
	return 0;
}
