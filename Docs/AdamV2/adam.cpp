/**
    @file   adam.cpp
    @brief  commande module ADAM

    @version   1.0
    @author    profs BTS SNIR
    @date      20/12/2021
    @remark
*/

// SPDX-License-Identifier: GPL-3.0-or-later

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cerrno>
#include <cstring>

#include "socket.hpp"

using namespace std;
//-----------------------------------------------
bool write_port(const TcpClientSocket& sock, unsigned char port, unsigned char state)
{
    // envoi d'une commande
    const vector<unsigned char> head = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06 };

    vector<unsigned char> cmde = head;
    cmde.push_back(0x01);
    cmde.push_back(0x05);
    cmde.push_back(0x00);
    cmde.push_back(port);
    cmde.push_back(state);
    cmde.push_back(0x00);

    if ( sock.write_datagram(cmde) == SOCKET_ERROR )
        return false;

    vector<unsigned char> buffer;
    return sock.read_datagram(buffer) == cmde.size();
}
//-----------------------------------------------
int main(void)
{
    const char* HOST        = "172.20.233.17";
    const unsigned int PORT = 502;

    // Création de la socket
    TcpClientSocket   sock(HOST, PORT);
    if ( !sock.is_valid() ) {
        cerr << "socket error: " << errno << " -> " << strerror(errno) << endl;
        return EXIT_FAILURE;
        }

    if ( !sock.is_connected() ) {
        cerr << "connection error: " << errno << " -> " << strerror(errno) << endl;
        if ( errno == 0 )
             cerr << "server is not running" << endl;
        return EXIT_FAILURE;
        }

    cout << "Connected to " << sock.get_peer_address() << " on port " << sock.get_peer_port() << endl;

    // l'adresse IP du client doit être autorisée à la connexion
    const vector<unsigned char> states = { 0x00, 0xff };
    const vector<unsigned char> ports  = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15 };

    for (const auto& port : ports)
        for (const auto& state : states) {
            if ( !write_port(sock, port, state) )
                cerr << "Write error" << endl;
            else
                cout << "OK" << endl;

            this_thread::sleep_for(1000ms);
            }

    return EXIT_SUCCESS;
}
