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

//This sets up the RPi hardware and ensures everything is working properly
	init(0);

  connect_to_server("192.168.1.2", 1024);
  //sends message
   send_to_server("Please");
   //receives message 
   char message[24];
   receive_from_server(message); //this may be buggy!
   Sleep(0,3000);


//Constants
int minSpeed = 50;
int Kp = 0.5;
int Ki = 0;
int Kd = 0;
int First=1;
int sleepTime = 0.1;	

//Variables
int w;			//measure of whiteness
int errorR;		//error Rigth
int errorR;		//error Rigth
error;        //tot error
int prevError=0;
double propSignal;

int sumError;		//the sum of all previous errors

double derSignal;	//the derivitive signal 

int main(){
	

	//infinite loop for testing purposes
	while(true){
		//Take picture with camera
		take_picture();
		
		preError = error;
		error=0;
		errorR=0;
		errorL=0;
		for (int i=0; i<160; i++){
			w = get_pixel(i, 120, 3);
			if(w > 100){
				errorL--;
				
			}
			}
			
			for (int i=0; i<320; i++){
			  w = get_pixel(i, 120, 3);
			  if(w > 100){
				errorR++;
				
			}
			
		}
		
		error=errorR-errorL;
	
		//rests for 0.1 seconds
		Sleep(0,1000);
		
		
		//when it reaches the secount quadrant
		if(error>310){
		First=0;
		}
		if(error!=0&&First==1){
		//Proportional Signal
		propSignal = (error)*Kp;
		
		
		//Integral Signal
		sumError += error;
		intSignal = (sumError*sleepTime)*Ki;
		
		//trial and error find an x value that works
		derSignal = ((error-preverror)/sleepTime)*Kd;
		
		
		//right wheel
		set_motor(1, ((minSpeed  - (propSignal + IntSignal + DerSignal));
		// left wheel
		set_motor(2, ((minSpeed + (propSignal + IntSignal + DerSignal));
		}else if(first==1){
		//turns until line is found.
		set_motor(1, -50);
		set_motor(2, 40);
		
		//when it reaches the intersections
		}else if(erroR>=((-error)-20)||erroR<=((-errorL)+20)){
				//Proportional Signal
		propSignal = (error)*Kp;
		
		
		//Integral Signal
		sumError += error;
		intSignal = (sumError*sleepTime)*Ki;
		
		//trial and error find an x value that works
		derSignal = ((error-preverror)/sleepTime)*Kd;
		
		
		//right wheel
		set_motor(1, ((minSpeed  - (propSignal + IntSignal + DerSignal));
		// left wheel
		set_motor(2, ((minSpeed + (propSignal + IntSignal + DerSignal));
		}else if((-errorL)>errorR){
		Sleep(0,1000);
		set_motor(2, (50);
		set_motor(1, (-50);
		}else if(((-errorL)<errorR)){
		  Sleep(0,1000);
			set_motor(2, (50);
		  set_motor(1, (-50);
		}
		set_motor(1, -60);
		set_motor(2, 60);
		}
		}

	}
	return 0;

}
