#include <stdio.h>
#include <time.h>

//bob
//these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);
//extern "C" int ReadAnalog(int ch_adc);
extern "C" int set_motor(int motor , int dir, int speed ); 
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

int main(){
      //This sets up the RPi hardware and ensures
      //everything is working correctly
    init(0);
    char c;
      //check initial and final positions of line
   /* for(i=0; i<320; i++){
        //get pixel "whiteness" from image (320x240)
        w = get_pixel(120,i,3);

        if(w<50){
         w=0;

        }else{
        w=1;
        }

    sum = sum +w;}*/

    //keep going till line finished or no line
    while(true){
	//printf("LOOP \n");



       //Take picture with camera
        take_picture();

        //sum for whiteness on left side of picture
        for(i=0;i<160; i++){
            //get pixel "whiteness" from image (320x240)
            w = get_pixel(i,120,3);
              //ranging black values
              if(w<50){
	printf("RIGHT \n");
              w=0;
              }else{
              w=1;
              }
            leftsum = leftsum +w;}
          //sum for whiteness on right side of picture
          for(i=160; i<320; i++){
              //get pixel "whiteness" from image (320x240)
              w = get_pixel(i,120,3);
              //ranging black values
              if(w<50){
	printf("LEFT 2\n");
              w=0;
              }else{
              w=1;
              }
              rightsum = rightsum +w;}
          //sum difference of both sides of image
          sum = rightsum - leftsum;
          //This would work for an ideal situation
          //if the left side sum is greater than the right
          //turn left
          if (sum < 0){
	printf("TURNLRFT 3\n");
            set_motor(1, 1, 60); //left wheel
            set_motor(2, 2, 120); //right wheel
            Sleep (0 ,500000);
          //if the right side sum is greater than the left
          //turn right
          }else if (sum > 0){
	printf("TURNRIGHT 4\n");
            set_motor(1, 1, 120);
            set_motor(2, 2, 60);
            Sleep (0 ,500000);
          //if both sides are equal continue forward
        }else if (sum == 0){
	printf("STRAIGHT \n");
            set_motor(1, 1, 120);
            set_motor(2, 2, 120) ;//turn both wheels at the same speed to move it forward
            Sleep (0 ,500000);
          }

            //breaks out if there is a wall and no line
        /*  if (front>0 && leftsum==0 && rightsum==0){
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
          }*/

       //Waits for 0.1 seconds (100000 microseconds)
       Sleep(0,100000);
       }
return 0;}
