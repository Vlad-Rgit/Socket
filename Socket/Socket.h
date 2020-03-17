#pragma once


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
			Socket(int type, int protocol = 0);

			void Bind(const char* ip, int port);
			int Connect(const char* ip, int port);
			void StartListen(int maxClients = SOMAXCONN);
			void SendChars(const char* buf, int length, int flags = 0);
			void SendChar(char c, int flags = 0);
			void SendString(std::string msg, int flags = 0);
			char* RecieveChars(size_t buff_size, int flags = 0);
			std::byte RecieveByte(int flags = 0);
			std::string RecieveString(int length, int flags = 0);
			char RecieveChar(int flags = 0);
			Socket WaitForClient();

			inline bool IsBinded() const { return _isBinded; }


		
	};


}