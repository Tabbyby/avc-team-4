# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor(int motor , int dir, int speed );

int main (){

  inti(0);
  
  while(true){
    set_motor(1, 1, 60); //left wheel
    set_motor(2, 2, 120); //right wheel
    }
  return 0 ;}
