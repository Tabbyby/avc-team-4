#include <stdio.h>
#include <time.h>
double ki=1;
double kp=1.2;
double kd =1.1;
double error=0;
double errorSum=0;
double prevError;
double currentError=0;
double propErrorSignal=0;
double difErrorSignal=0;
double inteErrorSignal=0;
long time;
long currentTime;
double speedPecent=100/255;
int SPEED;

int main(){
	//geting the time diference each time throght the loop
	double timeDif = currentTime-time;
	//resets the time
	time=currentTime;
	//sets the prev error (before the loop)
	preverror=error;
	//sets error(after the loop)
	error=sum;
	//sets current error
	currentErro+=error;
	//gets proportional erros signal
	propErrorSignal = error*kp;
	//gets diferential error signal
	difErrorSignal=((error-prevError)/timeDif)*kd;
	//gets the integral error signal
	inteErrorSignal=((currentError)*ki);
	//updated the total error
	errorSum+=currentError;
	//checks what error is bigeer to set the speed
	if(difErrorSignal>propErrorSignal||inteErrorSignal>propErrorSignal){
		if(difErrorSignal>inteErrorSignal){
			SPEED=difErrorsignal*speedPercentage;
		}else{
			SPEED=inteErrorsignal*speedPercentage;
		}else{
			SPEED=255;
		}
	}
}
