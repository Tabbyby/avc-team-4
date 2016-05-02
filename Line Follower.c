#include <stdio.h>
#include <time.h>

\\these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);
extern "C" int ReadAnalog(int ch_adc);
//getting the radings from the analog in the front
int front = ReadAnalog(0);
//network commands
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int main(){
      //This sets up the RPi hardware and ensures
      //everything is working correctly
    init(0);
    char c;
      //check initial and final positions of line
    for(i=0, i<320, i++){
        //get pixel "whiteness" from image (320x240)
        w = get_pixel(120,i,3);
        if(w<50){
          w=0;
        }
    sum = sum + i*w;}
    //keep going till line finished or no line
    while(true){
        
          
          
       //Take picture with camera
        take_picture()
        int leftsum = 0;
        int rightsum = 0;
        int sum = 0
        int i = 0;
        //sum for whiteness on left side of picture
        for(i=0, i<160, i++){
            //get pixel "whiteness" from image (320x240)
            w = get_pixel(120,i,3);
              //ranging black values
              if(w<50){
              w=0;
              }
            leftsum = leftsum + i*w;}
          //sum for whiteness on right side of picture
          for(i=160, i<320, i++){
              //get pixel "whiteness" from image (320x240)
              w = get_pixel(120,i,3);
              //ranging black values
              if(w<50){
              w=0;
              }
              rightsum = rightsum + i*w;}
          //sum difference of both sides of image
          sum = rightsum - leftsum
          //This would work for an ideal situation
          //if the left side sum is greater than the right
          //turn left
          if (sum < 0){
            turnleft();
          //if the right side sum is greater than the left
          //turn right
          }else if (sum > 0){
            turnRight();
          //if both sides are equal continue forward
        }else if (sum == 0){
            moveForward();
          }
          
            //breaks out if there is a wall and no line
          if (front>0 && leftsum==0 && rigthsum==0){
                break;
          }else if(front>0){ //if there is a wall and line open gate
                //connects to server at IP ADDRESS, PORT
                connect_to_server(130.195.6.196, 22);
                //sends MESSAGE to server
                send_to_server("Hello server");
                //recieves from server
                char message[24];
                message = recieve_from_server("my-password");
          }

       //Waits for 0.1 seconds (100000 microseconds)
       Sleep(0,100000);
       }
return 0;}
