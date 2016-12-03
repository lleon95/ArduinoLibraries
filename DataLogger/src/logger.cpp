/*
	Library implemented for Arduino
	GNU Licence (2016)
	Coder: Luis Leon
	Klooid Innovations (2016)
*/

#include "logger.h"
#include <String.h>

#define PING_RESPONSE 500

// Establish class
Logger_::Logger_(void);

// Reset ESP8288
bool Logger_::reset(void)
{
	// Restart
	Serial.println("AT+RST");
	// Checking restarting
	ms = Serial.readline();
    bool reset = false;
    if(ms.lastIndexOf("OK") != 0)
    	reset = true;
    return reset;
}

// Connect to network
bool Logger_::connect(String SSID, String PASSWORD)
{
	// Connecting command string
    String ms = "AT+CWJAP=";
    ms += char(34);
    ms += SSID;
    ms += char(34);
    ms += ",";
    ms += char(34);
    ms += PASSWORD;
    ms += char(34);
    // Delay
    delay(PING_RESPONSE);
    // Read console
    ms = Serial.readline();
    bool connected = false;
    // Checking connection sucessful
    if(ms.lastIndexOf("OK") != 0)
    	connected = true;
    return connected;
}

bool Logger_::send(String params[], int values[], String host_name, String path)
{
	// Verify if params and values have the same lenght
	if(params.size() != values.size())
		return false;
	// Build message

	  // Establish target host
	  String msg = "AT+CIPSTART=";
	  String msg2 = "";
	  String msg3 = "";
	  msg += char(34);
	  msg += "TCP";
	  msg += char(34);
	  msg += ",";
	  msg += char(34);;
	  msg += host_name;
	  msg += char(34);
	  msg += ",";
	  msg += "80";
	  msg += "\r\n";
	  Serial.print(msg);
	  delay(PING_RESPONSE);

	  // Count characters
	  int number_characters = 10; // Including GET && carry
	  number_characters += path.lenght();
	  for(int i = 0; i < params.size(); i++)
	  	number_characters == number_characters + params[i].lenght() + 1;
	  for(int i = 0; i < values.size(); i++)
	  {
	  		String temp = values[i].toString();
	  		number_characters == number_characters + temp.lenght() + 1;
	  }

	  // Send number of characters
	  msg  = "AT+CIPSEND=";
	  msg += number_characters;
	  Serial.println(msg);
	  delay(PING_RESPONSE);

	  // Send params and values
	  msg2 += path;
	  msg2 += "?";
	  for(int i = 0; i < params.size(); i++)
	  {
	  	msg2 += params[i];
	  	msg2 += "=";
	  	msg2 += value[i];
	  	if(i != params.size() - 1)
	  		msg2 += "&";
	  }
	  msg2 += "\r\n";
	  Serial.print(msg2);
	  delay(PING_RESPONSE);

	  // Send footer
	  Serial.print("HTTP/1.1\r\n");
	  delay(PING_RESPONSE);
	  msg3 = "host=";
	  msg3 += host_name;
	  msg3 += "\r\n";
	  Serial.print(msg3);
	  delay(PING_RESPONSE);

	  return true;
}

