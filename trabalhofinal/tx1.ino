#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
uint8_t text[3];
#define END 1


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.openReadingPipe(0, address);
  radio.startListening();
  radio.setPALevel(RF24_PA_MIN);
  text[0] = 0;
  text[1] = 0;
  text[2] = 0;
}


void loop() {
    if (text[0] <= 3) {
    radio.stopListening();
    radio.write(&text, sizeof(text));
    radio.startListening();
    text[0] = text[0] + 1;}
    else{text[0] = 1;}
    if (text[0] == 1){
      text[2] = 11;
      text[1] = 8;}
    if (text[0] == 2){
      text[2] = 12;
      text[1] = 8;}
    if (text[0] == 3){
      text[2] = 13;
      text[1] = 8;}
    delay(500);
    
        

  if (radio.available()) {
    uint8_t text[3];
    radio.read(&text, sizeof(text));
       
    if (text[0] == END) {
      int dado = text[2];
      Serial.println("______________________________________Recepção");
      Serial.println(text[0]);
      Serial.print("TTL: ");
      Serial.println(text[1]);
      Serial.print("DADOS: ");
      Serial.println(dado);
    } else if (text[1] > 0 && text[0] != END) {      
      text[1] = text[1] - 1;
      Serial.println("______________________________________Tramissão");
      Serial.println(text[0]);
      Serial.print("TTL: ");
      Serial.println(text[1]);
      Serial.println(text[2]);
      radio.stopListening();
      radio.write(&text, sizeof(text));
      radio.startListening();
    } else if(text[1] < 1) {
      Serial.println ("ttl expirado");
    }
    radio.startListening();
  }
}
