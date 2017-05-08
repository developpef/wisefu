#include <Crypto.h>
#include <BLAKE2s.h>
#include <string.h>
#include <avr/pgmspace.h>

#define HASH_SIZE 32
#define DATA_SIZE 20
#define SALT "wisefu2017GFI" // size = 13

char command;
char serialBuffer;
char challenge[DATA_SIZE + sizeof(SALT)] = SALT;

BLAKE2s blake2s;

uint8_t value[HASH_SIZE];

void createChallenge() {
  char nextchar1;
  char nextchar2;
  for (int count = 13; count < sizeof(challenge); count++) {
    nextchar1 = random(65, 90);
    nextchar2 = random(97, 122);
    if (random(2) == 1) {
      challenge[count] = nextchar1;
    } else {
      challenge[count] = nextchar2;
    }
  }
}

void generateHash() {
  blake2s.reset();//SALT, sizeof(SALT), HASH_SIZE);
  for (size_t posn = 0; posn < DATA_SIZE + 13; posn ++) {
    blake2s.update(challenge + posn, 1);
  }
  blake2s.finalize(value, sizeof(value));
}

void startAuthent()
{
  createChallenge();
  generateHash();
  Serial.println("Challenge sent: ");
  for (int count = sizeof(SALT)-1; count < sizeof(challenge)-1; count++) {
    Serial.print((char)challenge[count]);
  }
  Serial.println("");
  Serial.println("Hash: ");
  for (char k = 0; k < HASH_SIZE; k++) {
    Serial.print(value[k],HEX);
  }

}

void readCommand() {
  // start authentication process
  if (command == 'A') {
    startAuthent();
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


}

void loop() {
  if (Serial.available()) {
    serialBuffer = Serial.read();
    if (serialBuffer != '#') {
      command = serialBuffer;
    } else {
      readCommand();
    }
  }
}
