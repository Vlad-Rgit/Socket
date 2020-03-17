#pragma once
#include "Socket.h"
#include <iostream>
#include <exception>



WSAData my_socket::Socket::InitWsa(int major, int minor)
{
    WORD ver = MAKEWORD(major, minor);
    WSAData data;

    WSAStartup(ver, &data);
    return data;
}

WSAData my_socket::Socket::InitWsa()
{
    WORD ver = MAKEWORD(2, 1);
    WSAData data;

    WSAStartup(ver, &data);
    return data;
}


my_socket::Socket::Socket(int type)
    : _af(AF_INET), _type(type)
{
    _socket_id = socket(_af, _type, NULL);
}

my_socket::Socket::Socket(int af, int type, int protocol)
    : _af(af), _type(type)
{
    _socket_id = socket(_af, _type, protocol);
}

my_socket::Socket::Socket(int socket_id, sockaddr_in addr)
    :_socket_id(socket_id), _client_addr(addr) { }


void my_socket::Socket::Bind(const char* ip, int port) {

    _addr.sin_addr.S_un.S_addr = inet_addr(ip);
    _addr.sin_port = htons(port);
    _addr.sin_family = _af;
    _size_of_addr = sizeof(_addr);
  
    bind(_socket_id, (sockaddr*)&_addr, _size_of_addr);
    _isBinded = true;
}

int my_socket::Socket::Connect(const char* ip, int port)
{
    sockaddr_in addr;
    addr.sin_addr.S_un.S_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr.sin_family = _af;

    return connect(_socket_id, (sockaddr*)&addr, sizeof(addr));
}


void my_socket::Socket::StartListen(int maxClients) {

    if (_isBinded == false)
    {
        throw new std::exception("Socket is not binded");
    }

    listen(_socket_id, maxClients);
}

void my_socket::Socket::SendChars(const char* buf, int length,int flags)
{
    send(_socket_id, buf, length, flags);
}

void my_socket::Socket::SendChar(char c, int flags)
{
    send(_socket_id, &c, 1, flags);
}

void my_socket::Socket::SendString(std::string msg, int flags)
{
    send(_socket_id, msg.c_str(), msg.length(), flags);
}

char* my_socket::Socket::RecieveChars(size_t buff_size, int flags)
{
    char* msg = new char[buff_size];
    recv(_socket_id, msg, buff_size, NULL);
    return msg;
}

char my_socket::Socket::RecieveChar(int flags)
{
    char c;
    recv(_socket_id, &c, 1, flags);
    return c;
}


std::byte my_socket::Socket::RecieveByte(int flags)
{
    char c;
    recv(_socket_id, &c, 1, flags);
    return (std::byte)c;
}

std::string my_socket::Socket::RecieveString(int length, int flags)
{
    char* buffer = new char[length];
    recv(_socket_id, buffer, length, flags);
    std::string str(buffer);
    return str;
}



my_socket::Socket my_socket::Socket::WaitForClient() {

    sockaddr_in newAddr;
    int size_of_newAddr = sizeof(newAddr);

    unsigned int new_socket_id = accept(_socket_id, (sockaddr*)&newAddr, &size_of_newAddr);
    Socket socket(new_socket_id, newAddr);
    return socket;
}
