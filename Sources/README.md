```
//Server example
#include <Socket.h>

int main(int argc, char* argv[]) {

	my_socket::Socket listener(SOCK_STREAM);
	
	listener.Bind("192.168.100.229", 20011);
	
	listener.StartListen();
	
	while(true){
		my_socket::Socket client = listener.WaitForClient();
		
		client.SendString("Hello Cleint!");
	}	
}
```
