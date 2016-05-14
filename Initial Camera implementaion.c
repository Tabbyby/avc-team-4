#include <stdio.h>
#include <time.h>

\\these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);

int main(){
    //This sets up the RPi hardware and ensures
    //everything is working correctly
    init(0);
    char c;
    int sum = 0;
    for(i=0, i<320, i++){
        //get pixel "whiteness" from image (320x240)
        w = get_pixel(120,i,3);
        if(w<50){
          w=0;
        }
    sum = sum + i*w;}
    while(sum != 0){
        //Take picture with camera
        take_picture()
        int leftsum = 0;
        int rightsum = 0;
        int sumDiff = 0
        int i = 0;
        //sum for whiteness on left side of picture
        for(i=0, i<160, i++){
            //get pixel "whiteness" from image (320x240)
            w = get_pixel(120,i,3);
            if(w<50){
              w=0;
            }
            leftsum = leftsum + i*w;}
          //sum for whiteness on right side of picture
          for(i=160, i<320, i++){
              //get pixel "whiteness" from image (320x240)
              w = get_pixel(120,i,3);
              if(w<50){
                w=0;
              }
              rightsum = rightsum + i*w;}
          //sum difference of both sides of image
          sumDiff = rightsum - leftsum
          //This would work for an ideal situation
          //if the left side sum is greater than the right
          //turn left
          if (sumDiff < 0){
            turnleft();
          //if the right side sum is greater than the left
          //turn right
        }else if (sumDiff > 0){
            turnRight();
          //if both sides are equal continue forward
        }else if (sumDiff == 0){
            moveForward();
          }

       //Waits for 0.1 seconds (100000 microseconds)
       Sleep(0,100000);
       }
return 0;}

for(i=0;i<160; i++){
    //get pixel "whiteness" from image (320x240)
    w = get_pixel(i,120,3);
    //ranging black values
    if(w<200){
        //printf("RIGHT \n");
        w=0;
        
    }else{
        w=1;
        
    }
    leftsum = leftsum +w;
    
}
