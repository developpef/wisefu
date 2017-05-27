/* rawR&cv.ino Example sketch for IRLib2
    Illustrate how to capture raw timing values for an unknow protocol.
    You will capture a signal using this sketch. It will output data the
    serial monitor that you can cut and paste into the "rawSend.ino"
    sketch.
*/
// Recommend only use IRLibRecvPCI or IRLibRecvLoop for best results
#include <IRLibRecvPCI.h>

IRrecvPCI myReceiver(2);//pin number for the receiver

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    for (bufIndex_t i = 1; i < recvGlobal.recvLength; i++) {
      Serial.print(recvGlobal.recvBuffer[i], DEC);
      Serial.print(F(", "));
      if ( (i % 8) == 0) Serial.print(F("\n\t"));
    }
    myReceiver.enableIRIn();
  }
}
