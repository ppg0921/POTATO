#include <dht.h>
#define dataPin 8 // Defines pin number to which the sensor is connected
dht DHT; // Creats a DHT object

void setup() 
{
	Serial.begin(9600);
}
void loop() 
{
	int readData = DHT.read22(dataPin); // DHT22/AM2302
	// int readData = DHT.read11(dataPin); // DHT11

	float t = DHT.temperature; // Gets the values of the temperature
	float h = DHT.humidity; // Gets the values of the humidity

	// Printing the results on the serial monitor
	Serial.print("Temperature = ");
	Serial.print(t);
	Serial.print(" ");
	Serial.print("°");//shows degrees character
	Serial.print("C | ");
	Serial.print("Humidity = ");
	Serial.print(h);
	Serial.println(" % ");
	Serial.println("");

	delay(1500); // Delays 2 secods
}