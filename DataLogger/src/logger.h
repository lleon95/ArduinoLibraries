/*
	Library implemented for Arduino
	GNU Licence (2016)
	Coder: Luis Leon
	Klooid Innovations (2016)
*/

#ifndef LOGGER_h
#define LOGGER_h

class Logger_
{
public:
	Logger_(void);
	bool reset(void);
	bool connect(String SSID, String PASSWORD);
	bool Logger_::send(String params[], int values[], String host_name, String path);
};
extern Logger_ Logger;