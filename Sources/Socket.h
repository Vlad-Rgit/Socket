#pragma once

#include <string>

#ifdef __linux__
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netinet/ip.h> 
	#include <arpa/inet.h>
#endif


#ifdef _WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
    #include <WinSock2.h> 
#endif

namespace my_socket {


	class Socket {

		private:
			sockaddr_in _addr;
			sockaddr_in _client_addr;
			int _size_of_addr;
			unsigned int _socket_id;
			bool _isBinded = false;
			int _type;

		private:
			Socket(unsigned int socket_id);

	    #ifdef _WIN32
			/* Important to call one of these functions if you use Windows to init WinSock library
				before using Sockets! */
			public:
				static WSAData InitWsa(int major, int minor);
				static WSAData InitWsa();

		#endif

     	public:
			Socket(int type);
			Socket(int type, int protocol);

			void Bind(const char* ip, int port);
			int Connect(const char* ip, int port);
			void StartListen(int maxClients = SOMAXCONN);
			Socket WaitForClient();
			void SendChars(const char* buf, int length, int flags = 0);
			void SendChar(char c, int flags = 0);
			void SendString(std::string msg, int flags = 0);
			void SendInt(int i, int flags = 0);
			char* ReceiveChars(size_t buff_size, int flags = 0);

			#ifdef  _HAS_STD_BYTE
				std::byte ReceiveByte(int flags = 0);
			#endif   
		
			std::string ReceiveString(int length, int flags = 0);
			char ReceiveChar(int flags = 0);
			int ReceiveInt(int flags = 0);

			inline bool IsBinded() const { return _isBinded; }


		
	};


}