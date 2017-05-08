#include <Crypto.h>
#include <BLAKE2s.h>
#include <string.h>
#include <avr/pgmspace.h>

#define HASH_SIZE 32
#define DATA_SIZE 20
#define SALT "wisefu2017GFI" // size = 13
char challenge[DATA_SIZE + sizeof(SALT)] = SALT;
BLAKE2s blake2s;
uint8_t auth_hash[HASH_SIZE];
bool isAuthenticated, isAuthenticating;


char command;
char serialBuffer;
uint8_t serialContent[128];
char challengeResponse[32];


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
  blake2s.finalize(auth_hash, sizeof(auth_hash));
}

void startAuthent()
{
  createChallenge();
  generateHash();
  Serial.println("Challenge sent: ");
  for (int count = sizeof(SALT) - 1; count < sizeof(challenge) - 1; count++) {
    Serial.print((char)challenge[count]);
  }
  Serial.println("");
  Serial.println("Hash: ");
  for (char k = 0; k < HASH_SIZE; k++) {
    Serial.print(auth_hash[k], HEX);
  }

}

void readCommand() {
  // start authentication process
  if (command == 'A') {
    startAuthent();
  }
}

void checkAuthent() {
  /*char pos = 0;
    char respIndex = 0;
    serialContent = '\0';
    Serial.println("reading...");
    while (Serial.available()) {
    serialBuffer = Serial.read();
    if (serialBuffer != '-') {
      serialContent += serialBuffer;
    } else {
      Serial.println("read:");
      Serial.println(serialContent);
      challengeResponse[respIndex] = atoi(serialContent);
      Serial.println(challengeResponse[respIndex]);
      serialContent = '\0';
      respIndex++;
    }
    pos++;
    }
    Serial.println("done");
    for (char i = 0; i < 32; i++) {
    Serial.println(challengeResponse[i]);
    }*/

  char numb[3];
  char respIndex = 0, pos = 0;
  Serial.println("_received:");
  for (uint8_t i = 0; i < 32; i++) {
    Serial.print(serialContent[i]);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.println("_done");
  
  if (memcmp(auth_hash, serialContent, sizeof(auth_hash)) != 0) {
    Serial.println("auth KO...");
  } else {
    Serial.println("auth OK!");
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
    char command = Serial.read();
    char pos = 0;
    while (Serial.available()) {
      serialContent[pos] = Serial.read();
      pos++;
    }
    if (command == 'A') {
      startAuthent();
    } else if (command == 'R') {
      checkAuthent();
    }
  }
}
