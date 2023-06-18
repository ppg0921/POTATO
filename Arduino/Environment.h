#include <dht.h>

#ifndef Environment_H
#define Environment_H

class Environment
{
    private:
        dht* DHT= NULL;
        int _dhtPin = 8;
        int _TEMTPin = A0;
        float Temperature;
        float Humidity;
        float Lux;
    public:
        Environment() {};
        ~Environment() {};

        /**
         * @fn Environment
         * @brief create a DHT object and set PinNumber
         * @return none
         * @param dhtPin Pin number of dht data pin
         * @param TEMTPin Pin number of TEMT6000 data pin
        */
        Environment(const int dhtPin, const int TEMTPin);

        /**
         * @fn measureAll
         * @brief measure humidity, temperature and lux and store them in the class
         * @return void
        */
        void measureAll(void);
        float readHumidity(void);
        float readTemperature(void);
        float readLux(void);
        float getHumidity() {return Humidity;}
        float getTemperature() {return Temperature;}
        float getLux() {return Lux;}
};


Environment::Environment(const int dhtPin, const int TEMTPin)
{
    _dhtPin = dhtPin;
    _TEMTPin = TEMTPin;
    DHT = new dht;
    DHT.read22(_dhtPin);
    pinMode(_TEMTPin, INPUT)
}

void Environment::measureAll(void)
{
    DHT.read22(_dhtPin);
    Temperature = DHT.temperature;
    Humidity = DHT.humidity;
    int light_value = analogRead(_TEMTPin);
    float volts = analogRead(A0) * 5.0 / 1024.0;   // divide 5 volts into 1024 equal parts
    float amps = volts / 10000.0;      // resistance = 10K ohm
    float microamps = amps * 1000000;
    float lux = microamps * 2.0;       // 
    Lux = lux;
    return;
}

float Environment::readTemperature(void)
{
    DHT.read22(_dhtPin);
    Temperature = DHT.temperature;
    return Temperature;
}

float Environment::readHumidity(void)
{
    DHT.read22(_dhtPin);
    Humidity = DHT.humidity;
    return Humidity;
}

float Environment::readLux(void)
{
    int light_value = analogRead(_TEMTPin);
    float volts = analogRead(A0) * 5.0 / 1024.0;   // divide 5 volts into 1024 equal parts
    float amps = volts / 10000.0;      // resistance = 10K ohm
    float microamps = amps * 1000000;
    float lux = microamps * 2.0;       // 
    Lux = lux;
    return Lux;
}

