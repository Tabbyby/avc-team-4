#include <stdio.h>
#include <time.h>

//bob
//these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);
//extern "C" int InitHardware();
//extern "C" int ReadAnalog(int ch_adc);
//getting the readings from the analog in the front
extern "C" int set_motor(int motor , int dir, int speed ); //
//int front = ReadAnalog(0); 
int i=0;
int sum=0;
int leftsum=0;
int rightsum=0;
int w=0;

int main(){
	//initializes
      //This sets up the RPi hardware and ensures
      //everything is working correctly
	//InitHardware();
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
          //if the right side sum is greater than the left
          //turn right
          }else if (sum > 0){
	printf("TURNRIGHT 4\n");
            set_motor(1, 1, 120);
            set_motor(2, 2, 60);
          //if both sides are equal continue forward
        }else if (sum == 0){
	printf("STRAIGHT \n");
            set_motor(1, 1, 120);
            set_motor(2, 2, 120) ;//turn both wheels at the same speed to move it forward
          }

            //breaks out if there is a wall and no line
        /*  if (front>0 && leftsum==0 && rightsum==0){
                break;
          }else if(front>0){ //if there is a wall and line open gate
               // openGate();
          }*/

       //Waits for 0.1 seconds (100000 microseconds)
       Sleep(0,100000);
       }
return 0;}