




	//geting the time diference each time throght the loop
	//double timeDif = currentTime-time;
	//resets the time
	//time=currentTime;
	
	
	



#include <stdio.h>
#include <time.h>

//these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);
//extern "C" int ReadAnalog(int ch_adc);
extern "C" int set_motor(int motor , int speed );
//network commands
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);


//int front = ReadAnalog(0);	//gets data from front sensor
int i=0;
int sum=0;
int leftsum=0;
int rightsum=0;
int w=0;

double ki=0;
double kp=0.5;
double kd =0.008;
double error=0;
double errorSum=0;
double prevError=0;
double actionSetter=0;
double currentError=0;
double propErrorSignal=0;
double difErrorSignal=0;
double inteErrorSignal=0;
double Time=0.1;
//long currentTime;
double minSpeed=50;
int LeftSPEED=0;
int RightSPEED=0;

int main(){
	//This sets up the RPi hardware and ensures
	//everything is working correctly
	init(0);
	
	//keep going till line finished or no line
	while(true){
		sum = 0;
		leftsum = 0;
		rightsum = 0;
		//sets the prev error (before the loop)
		double preverror=error;
		//Take picture with camera
		take_picture();

		//sum for whiteness on left side of picture
		for(i=0;i<160; i++){
			//get pixel "whiteness" from image (320x240)
			w = get_pixel(i,120,3);
			//ranging black values
			if(w>200){
				leftsum++;

			}

		}
		//sum for whiteness on right side of picture
		for(i=160; i<320; i++){
			//get pixel "whiteness" from image (320x240)
			w = get_pixel(i,120,3);
			if(w>200){
				rightsum++;

			}

		}
		//sum difference of both sides of image
		sum = rightsum - leftsum;
		//sets error(after the loop)
		error=sum;
		//sets current error
		currentError+=error;
			//gets proportional erros signal
		propErrorSignal = sum*kp;
		//gets diferential error signal
		difErrorSignal=((error-prevError)/Time)*kd;
		//gets the integral error signal
		inteErrorSignal=((currentError)*ki);
		//updated the total error
		errorSum+=currentError;
		//checks what error is bigeer to set the speed
		actionSetter=difErrorSignal+propErrorSignal+inteErrorSignal;
		LeftSPEED=minSpeed+actionSetter;
	        RightSPEED=minSpeed-actionSetter;
		//This would work for an ideal situation
		//if the left side sum is greater than the right
		//turn left
		//if (sum < -1){
			//printf("TURNLRFT 3\n");
			//sets the motor to the PID speed
			//set_motor(1,- 30); //left wheel
			//set_motor(2,- 100); //right wheel
			//Sleep(0,2000);
			set_motor(1,LeftSPEED);
			set_motor(2,RightSPEED);
			Sleep(0,1000);
			
			//if the right side sum is greater than the left
			//turn right
		//}else if (sum > 1){
			//printf("TURNRIGHT 4\n");
			//set_motor(1, -100);
			//set_motor(2,-30);
			//Sleep (0 ,2000);
			//if both sides are equal continue forward
		//}else if (sum > -1 && sum < 1){
			//printf("STRAIGHT \n");
			//set_motor(1, -60);
			//set_motor(2, -60) ;//turn both wheels at the same speed to move it forward
			//Sleep (0 ,1000);

		//}
		//breaks out if there is a wall and no line
		/*
		if (front>0 && leftsum==0 && rightsum==0){
			break;

		}else if(front>0){ //if there is a wall and line open gate
			//connects to server at IP ADDRESS, PORT
			connect_to_server(130.195.6.196, 1024);
			//sends MESSAGE to server
			send_to_server("Please");
			//recieves from server
			char message[24];
			recieve_from_server(message);
			//sends password back to server
			send_to_server(message);

		}
		*/

		//Waits for 0.1 seconds (100000 microseconds)
		Sleep(0,100000);

	}
	return 0;

}

