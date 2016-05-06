#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
//network commands
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

Network_Gate(){
	//initialises hardware
	init(0);
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
