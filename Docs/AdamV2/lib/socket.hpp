/**
    @file   socket.hpp
    @brief  gestion des sockets BSD

    @version   1.0
    @author    profs BTS SNIR
    @date      20/12/2021
    @remark
*/

// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#ifdef WIN32
    #include <winsock2.h>

    typedef int socklen_t;
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #define INVALID_SOCKET  -1
    #define SOCKET_ERROR    -1
    #define closesocket(s)  close(s)

    typedef int SOCKET;
    typedef struct sockaddr_in  SOCKADDR_IN;
    typedef struct sockaddr     SOCKADDR;
#endif

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
//----------------------------------------------------------------------
class Socket {
    class Error : public std::exception {
        private:
            std::string     description;    //Description de l'erreur
            unsigned int    line;           //Numéro de ligne
            std::string     function;       //Fonction
        public:
            Error(const std::string& d, const unsigned int l=0, const std::string& f="") throw()
                : description(d), line(l), function(f) {}
            virtual ~Error(void) throw() {}
            virtual const char* what(void) const throw() { return this->description.data(); }
            unsigned int at(void) const throw() { return this->line; }
            std::string where(void) const throw() { return this->function; }
        };

    protected:
        unsigned int    domain    = AF_INET;
        unsigned int    type      = 0;
        SOCKET          sockfd    = INVALID_SOCKET;
        std::string     host      = "";
        unsigned int    port      = 0;
        unsigned int    lasterror = 0;
        SOCKADDR_IN     peer;
    public:
        Socket(const std::string& host, const unsigned int port, const unsigned int type);
        ~Socket(void);

        SOCKET get_socket(void) const { return this->sockfd; }
        std::string get_hosts(void) const { return this->host; }
        unsigned int get_port(void) const { return this->port; }
        unsigned int get_lasterror(void) const { return this->lasterror; }
        std::string get_peer_address(void) const { return std::string(inet_ntoa(this->peer.sin_addr)); }
        unsigned int get_peer_port(void) const { return ntohs(this->peer.sin_port); }
        bool is_valid(void) const { return this->sockfd != INVALID_SOCKET; }
        int write_datagram(const std::vector<unsigned char>& frame) const;
        int read_datagram(std::vector<unsigned char>& frame) const;
    protected:
        bool bind(void) const;
        int sendto(const SOCKET socket, const std::vector<unsigned char>& frame, const SOCKADDR_IN& peer) const;
        int rcvfrom(const SOCKET socket, std::vector<unsigned char>& frame, const SOCKADDR_IN& peer) const;
    };
//----------------------------------------------------------------------
class UdpSocket : public Socket {
    public:
        UdpSocket(const std::string& host, const unsigned int port):
            Socket(host, port, SOCK_DGRAM) {};
    };

class UdpServerSocket : public UdpSocket {
    public:
        UdpServerSocket(const std::string& host, const unsigned int port):
            UdpSocket(host, port)
        {
            if ( !this->bind() ) {
                this->lasterror = SOCKET_ERROR;
                std::cerr << "bind error: " << errno << " -> " << strerror(errno) << std::endl;
                }
        }
    };

class UdpClientSocket : public UdpSocket {
    public:
        UdpClientSocket(const std::string& host, const unsigned int port):
            UdpSocket(host, port) { this->set_sockaddress(); };
        void set_sockaddress(void)
        {
            this->peer.sin_family      = this->domain;
            this->peer.sin_addr.s_addr = inet_addr(this->host.data());
            this->peer.sin_port        = htons(this->port);
        }
    };
//----------------------------------------------------------------------
class TcpSocket : public Socket {
    public:
        TcpSocket(const std::string& host, const unsigned int port):
            Socket(host, port, SOCK_STREAM) {};
    };

class TcpServerSocket : public TcpSocket {
    private:
        enum class      shut { SHUT_RD, SHUT_WR, SHUT_RDWR };
        SOCKET          csockfd   = INVALID_SOCKET;
        SOCKADDR_IN     client;
        bool            listening = false;
        unsigned int    backlog   = 5;	// maximum length to which the queue of pending connections may grow
    public:
        TcpServerSocket(const std::string& host = "*", const unsigned int port = 0):
            TcpSocket(host, port)
        {
            if ( !this->bind() )
                this->lasterror = SOCKET_ERROR;
            else
                this->listening = this->listen() != SOCKET_ERROR ;
        }
        SOCKET client_socket(void) const { return this->csockfd; }
        std::string client_address(void) const { return inet_ntoa(this->client.sin_addr); }
        unsigned int client_port(void) const { return ntohs(this->client.sin_port); }
        bool is_listening(void) const { return this->listening; }
        bool accept(void)
        {
			/** accept a connection on a socket
			@return	true if socket accepted, false on error
			*/
            memset((char*) &this->client, 0, sizeof(SOCKADDR_IN));
            socklen_t   recsize = sizeof(SOCKADDR_IN);

            return (this->csockfd = ::accept(this->sockfd, (SOCKADDR*)&client, &recsize)) != INVALID_SOCKET ;
        }
        bool shutdown(const shut& how = shut::SHUT_RDWR)
        {
			/** shut down part of a full-duplex connection
			@param	how -- shut down mode (default: SHUT_RDWR)
			@return	true on success, false on error
			*/
            return this->csockfd != INVALID_SOCKET
                ? ::shutdown(this->csockfd, static_cast<int>(how)) != SOCKET_ERROR
                : false ;
        }
        int write_datagram(const std::vector<unsigned char>& frame) const
        {
			/** send a message on a socket
			@param	frame -- buffer containing the message to be sent

			@retval	the number of bytes sent if successful
			@retval	SOCKET_ERROR if error
			*/
            return this->sendto(this->csockfd, frame, this->client);
        }
    private:
        int listen(void) const
        {
			/**listen for connections on a socket */
            return this->is_valid()
                ? ::listen(this->sockfd, this->backlog)
                : SOCKET_ERROR ;
        }
   };

class TcpClientSocket : public TcpSocket {
    private:
        bool connected = false;
    public:
        TcpClientSocket(const std::string& host, const unsigned int port):
            TcpSocket(host, port)
        {
            this->set_sockaddress();
            this->connected = this->connect() != SOCKET_ERROR ;
        };
        bool is_connected(void) const { return this->connected; }
    private:
        void set_sockaddress(void)
        {
            this->peer.sin_family      = this->domain;
            this->peer.sin_addr.s_addr = inet_addr(this->host.data());
            this->peer.sin_port        = htons(this->port);
        }
        int connect(void) const
        {
            /** initiate a connection on a socket */
			return this->is_valid()
                ? ::connect(this->sockfd, (SOCKADDR*) &this->peer, sizeof(SOCKADDR))
                : SOCKET_ERROR ;
        }
   };
//----------------------------------------------------------------------
