#include "logger.cpp"

// Creating an object with the class of logger
Logger logger;

void setup()
{
	Serial.begin(115200); // Required for this library
	// Reset ESP8288
	logger.reset();
	// Connect to network
	logger.connect("SSID","PASS");
}

int count = 0;
String param[] = {"Counter"};
int values[] = {0}

void loop()
{
	// Refresh values
	values[0] = count;
	// Send values
	logger.send(param, values, "192.168.0.1", "/index.php");
	// Update
	count++;
	// Wait until data is sent
	delay(15000);
}