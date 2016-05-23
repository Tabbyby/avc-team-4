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
int speed = 50;		//base speed
double Kp = 0.3;
double Kd = 0.008;
double sleepTime = 0.01;	//seconds
int whiteThresh = 100;	//the lowest whiteness value that is considered a white pixel

//Variables
int w;			//measure of whiteness
int error;		//sum of white pixel locations
int counter;		//number of "white" pixels
int avError = 0;	//sum of white pixel locations/number of white pixels

int propSignal;		//Proportional signal
int preError;		//previous error signal
int derSignal;		//derivitive signal


int main(){
	//This sets up the RPi hardware and ensures everything is working properly
	init(0);
	
	//connects to server
	//connect_to_server("192.168.1.2", 1024);
	//sends message
   	//send_to_server("Please");
   	//receives password
   	//char message[24];
   	//receive_from_server(message);
   	//sends password back to server
   	//send_to_server(message);
   	//wait for door to open
   	//Sleep(0,3000);

	//infinite loop for testing purposes
	while(true){
		//Take picture with camera
		take_picture();

		preError = avError;	//sets previous error as the previous error for this iteration of loop
		counter = 0;		//resets counter
		error = 0;		//resets error
		for (int i=0; i<320; i++){
			w = get_pixel(i, 120, 3);
			if(w > whiteThresh){
				//sums up the error from the center
				error += (i-160);
				counter++;
			}
		}
		//rests for 0.1 seconds
		Sleep(0,(100000*sleepTime));


		if(counter!=0){
			//Proportional Signal
			//mean is sum of values divided by number of values
			avError = error/counter;
			propSignal = avError*Kp;

			//Derivitive Signal
			//derivitive is change in error/change in time
			derSignal = ((avError - preError)/sleepTime)*Kd;
			
			//sets motors
			set_motor(1, speed + (propSignal + derSignal));
			set_motor(2, speed - (propSignal + derSignal));
			printf("\npropSignal %d", propSignal);
			printf("\nderSignal %d", derSignal);
		}else{
			//goes backwards
			set_motor(1, -40);
			set_motor(2, -40);
			printf("FAIL");
		}
	
	return 0;
	}
}

void turnAround(){
	int avError;
	int w;
	int counter = 0;
	int error;
	while((avError <= 10) && (avError >= -10)){
		set_motor(1, -30);
		set_motor(2, 30);
		error = 0;
		for (int i=0; i<320; i++){
			w = get_pixel(i, 120, 3);
			if(w > whiteThresh){
				//sums up the error from the center
				error += (i-160);
				counter++;
			}
		}
		avError = error/counter;
	}
	set_motor(1, 0);
	set_motor(2, 0);
}
