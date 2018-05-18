/* 
 * File:   main.cpp
 * Author: JCT & Tobias Valbjørn
 * Created on 13 March 2018
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <string.h>
#include <string>
#include "TCPClient.h"

using namespace std;

int main(int argc, char** argv) {
    cout << "Temperature client for the BBB" << endl;
    if(argc != 3) {
        cout << "Please input a hostname and port" << endl;
        return EXIT_FAILURE;
    }
    
    char *servername = argv[1];
    int port = atof(argv[2]);
    
    TCPClient tcp;
    if(!tcp.setup(servername,port)) {
        cout << "Connecting failed" << endl;
        return EXIT_FAILURE;
    }
    
    string status = tcp.receive();
    cout << "Got! " << status << endl;
    
    int id = 1;
    string id_string=to_string(id);
    string json_set= "{\"jsonrpc\": \"2.0\", \"method\": \"setTemp\","
            " \"params\": \"17\" ,\"id\": \""+id_string+"\"}";
     cout << "Sending:" << json_set << endl;
        //Get temperature frequently.
        tcp.Send(json_set);
           
        //Receive the string containing the temperature
        string rec = tcp.receive();
        if( rec != "" )
        {
                cout << "Server Response: " << rec;
        }
   
    
    while(1)
    {
        id++;
        id_string=to_string(id);
        string json_get= "{\"jsonrpc\": \"2.0\", \"method\": \"getTemp\", "
                "\"id\": \""+id_string+"\"}";
        cout << "Sending:" << json_get << endl;
        //Get temperature frequently.
        tcp.Send(json_get);
           
        //Receive the string containing the temperature
        string rec = tcp.receive();
        if( rec != "" )
        {
                cout << "Server Response: " << rec;
        }
        sleep(5);
        
        
        
    }
    return 0;
}

