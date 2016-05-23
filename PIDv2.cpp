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
int speed = 40;		//base speed
double Kp = 0.25;
double Kd = 0.05;
double sleepTime = 0.05;	//seconds
int whiteThresh = 100	//the lowest whiteness value that is considered a white pixel

//Variables
int w;			//measure of whiteness
int error;		//sum of white pixel locations
int counter;		//number of "white" pixels
int avError = 0;	//sum of white pixel locations/number of white pixels

int propSignal;
int preError;
derSignal;


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
			propSignal = avError*Kp;
			
			//Derivitive Signal
			if(preError == 0){
				//if there is not previous error, set derSignal to 0
				preError = avError;
			}
			//derivitive is change in error/change in time
			derSignal = ((avError - preError)/sleepTime)*Kd;
			
			//sets motors
			set_motor(1, speed + (propSignal + derSignal));
			set_motor(2, speed - (propSignal + derSignal));
		}else{
			//goes backwards
			set_motor(1, -40);
			set_motor(2, -40);
			printf("FAIL");
		}
	
	return 0;
}

//int turnAround(){
//	while((avError <= 10) && (avError >= -10)){
//		
//	}
//}
