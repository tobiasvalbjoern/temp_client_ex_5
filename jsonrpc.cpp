#include "ArduinoJson/ArduinoJson.h"
#include <iostream>

using namespace std;

string jsonrpc_handler(string jsonrpc) {
    cout << "Dump: ##" << jsonrpc << "##" << endl;
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(jsonrpc);

    string jsonrpc_version = root["jsonrpc"];
    string method = root["method"];
    
    long id = root["id"];

    if (!root.success()) {
        cout << "Not a valid JSON object" << endl;
        return "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32700, \"message\": \"Parse error\"}, \"id\": null}\n";
    }
    
    if (jsonrpc_version != "2.0" || !method.length() ) {
        cout << "Not a valid JSONRPC object" << endl;
        return "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32600, \"message\": \"Invalid request\"}, \"id\": null}\n";
    }
    
    string output;
    root.printTo<string>(output);
    output.append("\n");
    return output;
}