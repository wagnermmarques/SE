    #include <SPI.h>
    #include <nRF24L01.h>
    #include <RF24.h>
    RF24 radio(7, 8); // CE, CSN
    const byte address[6] = "00001";
    void setup() {
      Serial.begin(9600);
      radio.begin();
      radio.openWritingPipe(address);
      radio.openReadingPipe(0, address);
      radio.startListening(); 
      radio.setPALevel(RF24_PA_MIN);
      }
    void loop() {
      radio.stopListening();
      const char text[] = "Hello World";
      radio.write(&text, sizeof(text));
      radio.startListening();
      delay(100);
      
      
      if (radio.available()) {
        char text[32] = "";
        radio.read(&text, sizeof(text));
        Serial.println(text);
      }   
    }
