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

int rightSum;		//how many white pixels are on the right
int leftSum;		//how many white pixels are on the left

bool left = false;	//whether or not there is a path on the left
bool right = false;	//whether or not there is a path on the right
bool forward = false;	//whether or not there is a path ahead

//Prevents spazzing upon termination of program
void signal_callback_handler(int signum){
	set_motor(1, 0);
	set_motor(2,0);
	exit(signum);
}

//Opens the network gate
void networkGate(){
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
}

//turns to the left until it finds a line
void turnLeft(){

	printf("Turning Left");

	int avError = 1;
	int w;
	int counter = 0;
	int error;

	set_motor(1, -50);
	set_motor(2, 50);
	Sleep(1,0);
	while(avError != 0){
		set_motor(1, -50);
		set_motor(2, 50);
		error = 0;

		Sleep(0, 100000);
		take_picture();
		for (int i=0; i<320; i++){
			w = get_pixel(i, 120, 3);
			if(w > whiteThresh){
				//sums up the error from the center
				error += (i-160);
				counter++;
			}
		}
		avError = error/counter;
		printf("\n avError: %d", avError);
	}
	set_motor(1, 0);
	set_motor(2, 0);
}

//turns to the right until it finds a line
void turnRight(){
	
	printf("\n Turning Right");
	
	int avError = 1;
	int w;
	int counter = 0;
	int error;

	set_motor(1, 50);
	set_motor(2, -50);
	Sleep(1,0);
	while(avError != 0){
		set_motor(1, 50);
		set_motor(2, -50);
		error = 0;

		Sleep(0,100000);
		take_picture();
		for (int i=0; i<320; i++){
			w = get_pixel(i, 120, 3);
			if(w > whiteThresh){
				//sums up the error from the center
				error += (i-160);
				counter++;
			}
		}
		avError = error/counter;
		printf("\n avError: %d", avError);
	}
	set_motor(1, 0);
	set_motor(2, 0);
}

int main(){
	//This sets up the RPi hardware and ensures everything is working properly
	init(0);

	signal_callback_handler(2, signal_callback_handler);

	//opens the network gate
	//networkGate();

	//infinite loop for testing purposes
	while(true){
		//Take picture with camera
		take_picture();

		preError = avError;	//sets previous error as the previous error for this iteration of loop
		counter = 0;		//resets counter
		error = 0;		//resets error
		rightSum = 0;		//resets rightSum
		leftSum = 0;		//resets leftSum
		for (int i=0; i<320; i++){
			w = get_pixel(i, 120, 3);
			if(w > whiteThresh){
				//sums up the error from the center
				error += (i-160);
				counter++;
				if(i > 280){
					rightSum++;
				}else if(i < 40){
					leftSum++;
				}
			}
		}
		//rests for 0.1 seconds
		Sleep(0,(100000*sleepTime));

		//stores whether there is a white line ahead
		if(counter > 0){
			forward = true;
		}else{
			forward = false;
		}

		if(forward){
			printf("\n forward path");
		}
		if(left){
			printf("\n left path");
		}
		if(right){
			printf("\n right path");
		}

		if(forward && !left){
			//goes forward following the line
			printf("\n Continue Forward");

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
		}else if(left){
			//}else if(left || (!left && !right && !forward)){
			//Turns to the left until it centers on a line
			turnLeft();
		}else if(!left && right && !forward){
			//Turns to the right until it centers on a line
			turnRight();
		}else{
			//stops
			//for now should stop if it hits a dead end or reads no white pixels
			set_motor(1, 0);
			set_motor(2, 0);
			printf("\n ABORT ABORT ABORT ABORT")
			return 0;
		}


		//initialise leftSum and rightSum at end of loop so that if it reads black
		//it can use leftSum and rightSum from when it still saw the white line
		if(leftSum > 3){
			left = true;
		}else{
			left = false;
		}

		if(rightSum > 3){
			right = true;
		}else{
			right = false;
		}
	}
	return 0;
}
