#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP32Servo.h>

RF24 radio(4, 5);

const byte address[6] = "00001";

struct DataPacket {
  uint16_t ch1;
  uint16_t ch2;
  uint16_t ch3;
  uint16_t ch4;
  uint16_t ch5;
  uint16_t ch6;
  uint8_t ch7;
  uint8_t ch8;
};

DataPacket data;

// 8 channels
Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;
Servo ch7;
Servo ch8;

void setup() {

  Serial.begin(115200);

  // Output pins
  ch1.attach(13);
  ch2.attach(12);
  ch3.attach(14);
  ch4.attach(27);
  ch5.attach(26);
  ch6.attach(25);
  ch7.attach(33);
  ch8.attach(32);

  if (!radio.begin()) {
    Serial.println("NRF24 NOT FOUND");
    while (1);
  }

  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(76);

  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("Universal RX Ready");
}

void loop() {

  if (radio.available()) {

    radio.read(&data, sizeof(data));

    ch1.write(map(data.ch1, 0, 4095, 0, 180));
    ch2.write(map(data.ch2, 0, 4095, 0, 180));
    ch3.write(map(data.ch3, 0, 4095, 0, 180));
    ch4.write(map(data.ch4, 0, 4095, 0, 180));
    ch5.write(map(data.ch5, 0, 4095, 0, 180));
    ch6.write(map(data.ch6, 0, 4095, 0, 180));

    ch7.write(data.ch7 ? 180 : 0);
    ch8.write(data.ch8 ? 180 : 0);

    Serial.print("CH1=");
    Serial.print(data.ch1);
    Serial.print(" CH2=");
    Serial.print(data.ch2);
    Serial.print(" CH3=");
    Serial.print(data.ch3);
    Serial.print(" CH4=");
    Serial.print(data.ch4);
    Serial.print(" CH5=");
    Serial.print(data.ch5);
    Serial.print(" CH6=");
    Serial.print(data.ch6);
    Serial.print(" CH7=");
    Serial.print(data.ch7);
    Serial.print(" CH8=");
    Serial.println(data.ch8);
  }
}