/* rawR&cv.ino Example sketch for IRLib2
    Illustrate how to capture raw timing values for an unknow protocol.
    You will capture a signal using this sketch. It will output data the
    serial monitor that you can cut and paste into the "rawSend.ino"
    sketch.
*/
// Recommend only use IRLibRecvPCI or IRLibRecvLoop for best results
//#include <IRLibRecvPCI.h>
#include <IRremote.h>

IRrecv myReceiver(13);//pin number for the receiver
decode_results results;
//IRsend            irsend;
//int data[] = {9000, 4500, 560, 560, 560, 560, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 560, 560, 560, 560, 1690, 560, 1690, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 39416, 9000, 2210, 560}; //AnalysIR Batch Export (IRremote) - RAW

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
  if (myReceiver.decode(&results)) {
    Serial.println(results.value, HEX);
    myReceiver.resume(); // Receive the next value
  }
  /*delay(2000);
  irsend.sendRaw(data, sizeof(data) / sizeof(data[0]), 38);
    myReceiver.resume(); // Receive the next value
  myReceiver.enableIRIn(); // Start the receiver*/
}
