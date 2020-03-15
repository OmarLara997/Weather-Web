#include <SoftwareSerial.h>
#include "Seeed_BME280.h"
#include <Wire.h>

// instanciamos un puerto serie en el modulo HC-12, llamado Serial2
SoftwareSerial Serial2(9, 8); // HC-12 TX Pin, HC-12 RX Pin

// configuramos el sensor como un bme280
BME280 bme280;

// configuramos los pines del sensor de lluvia y humedad del suelo
const int lluvia_pin = 7; // este es un pin analogico
const int suelo_pin = 3; // este es un pin digital

// array de los datos a enviar
float data[6];

void setup(){
    // configuramos el Serial2 en 9600 baudios
    Serial2.begin(9600);
    // iniciamos el sensor bme280
    bme280.init();
    // declaramos el pin como entrada
    pinMode(lluvia_pin,INPUT);
}

void loop(){
    // realizamos las lecturas de datos y los asignamos
    float pres = bme280.getPressure();
    data[0] = bme280.getTemperature();
    data[1] = bme280.getHumidity();
    data[2] = pres;
    data[3] = bme280.calcAltitude(pres);
    data[4] = analogRead(suelo_pin);
    data[5] = digitalRead(lluvia_pin);

    // imprimimos todos los datos en el puerto Serial2
    Serial2.print(data[0]);
    Serial2.print(',');
    Serial2.print(data[1]);
    Serial2.print(',');
    Serial2.print(data[2]);
    Serial2.print(',');
    Serial2.print(data[3]);
    Serial2.print(',');
    Serial2.print(data[4]);
    Serial2.print(',');
    Serial2.print(data[5]);
    Serial2.print(',');
    Serial2.println("00");

    // esperamos 5 segundos
    delay(5000);   
}
// las transmiciones de datos seran cada 5 segundos
// estos datos van hacia la Raspberry Pi
