/* 
 * File:   main.cpp
 * Author: JCT & Tobias Valbjørn
 * Created on 06 March 2018, 11:41
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <string.h>
#include <string>
#include "TCPClient.h"
#include "jsonrpc.h"
#include "ArduinoJson/ArduinoJson.h"
using namespace std;

TCPClient tcp;

void sig_exit(int s)
{
    tcp.Send("HEAT OFF\n");
    tcp.exit();
    exit(0);
}

int main(int argc, char** argv) {
    cout << "Temperature client for the BBB" << endl;
    
    //string json= "{\"jsonrcp\": \"2.0\", \"method\": \"getTemp\", \"id\": \"1\"}\n";
    string json= "{\"jsonrpc\": \"2.0\", \"method\": \"getTemp\", \"id\": \"1\"}";
    
    if(argc != 4) {
        cout << "Please input a hostname, port and requested temperature" << endl;
        return EXIT_FAILURE;
    }
    
    char *servername = argv[1];
    int port = atof(argv[2]);
    float settemperature = atof(argv[3]);
    
    cout << "Set temperature: " << settemperature << endl;
    
    if(!tcp.setup(servername,port)) {
        cout << "Connecting failed" << endl;
        return EXIT_FAILURE;
    }
    signal(SIGINT, sig_exit);
    string status = tcp.receive();
    cout << "Got! " << status << endl;
    
    while(1)
    {
        cout << "Sending:" << json << endl;
        //Get temperature frequently.
        tcp.Send(json);
           
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

