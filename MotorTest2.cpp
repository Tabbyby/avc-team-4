# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep( int sec , int usec );
extern "C" int set_motor(int motor , int dir, int speed );

int main (){

  init(0);
  
  
  set_motor(1, 60); //left wheel
  set_motor(2, 60); //right wheel
  
  Sleep(3, 0);
  
  set_motor(1, 0);
  set_motor(2, 0);
  
  return 0 ;
}
