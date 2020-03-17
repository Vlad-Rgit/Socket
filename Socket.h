#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <cstddef>
#include <string>

namespace my_socket {


	class Socket {

		private:
			SOCKADDR_IN _addr;
			SOCKADDR_IN _client_addr;
			int _size_of_addr;
			unsigned int _socket_id;
			bool _isBinded = false;
			int _af;
			int _type;

		private:
			Socket(int socket_id, sockaddr_in client_addr);

		public:
			static WSAData InitWsa(int major, int minor);
			static WSAData InitWsa();

     	public:
			Socket(int type);
			Socket(int af, int type, int protocol = NULL);

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