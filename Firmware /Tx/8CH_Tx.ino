#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5);   // CE, CSN

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

void setup() {
  Serial.begin(115200);

  pinMode(25, INPUT_PULLUP);   // Toggle 1
  pinMode(26, INPUT_PULLUP);   // Toggle 2

  if (!radio.begin()) {
    Serial.println("NRF24 NOT FOUND");
    while (1);
  }

  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(76);

  radio.openWritingPipe(address);
  radio.stopListening();

  Serial.println("TX Ready");
}

void loop() {

  data.ch1 = analogRead(34);   // Joy1 X
  data.ch2 = analogRead(35);   // Joy1 Y
  data.ch3 = analogRead(32);   // Joy2 X
  data.ch4 = analogRead(33);   // Joy2 Y
  data.ch5 = analogRead(36);   // Pot1
  data.ch6 = analogRead(39);   // Pot2

  data.ch7 = digitalRead(25);  // Toggle1
  data.ch8 = digitalRead(26);  // Toggle2

  radio.write(&data, sizeof(data));

  Serial.print("J1X:");
  Serial.print(data.ch1);

  Serial.print(" J1Y:");
  Serial.print(data.ch2);

  Serial.print(" J2X:");
  Serial.print(data.ch3);

  Serial.print(" J2Y:");
  Serial.print(data.ch4);

  Serial.print(" P1:");
  Serial.print(data.ch5);

  Serial.print(" P2:");
  Serial.print(data.ch6);

  Serial.print(" SW1:");
  Serial.print(data.ch7);

  Serial.print(" SW2:");
  Serial.println(data.ch8);

  delay(20);   // 50Hz
}