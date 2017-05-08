// a tester https://github.com/brainhub/SHA3IUF

#include <Crypto.h>
#include <SHA3.h>
#include <string.h>

#define DATA_SIZE 20
#define HASH_SIZE 64
#define BLOCK_SIZE 136
#define SALT "wisefu_2017!@gfi+M2DL"

uint8_t value[HASH_SIZE];
SHA3_256 sha3_256;

char command;
char serialBuffer;
boolean isAuthenticating;
uint8_t challenge[DATA_SIZE];

void generateHash()
{
  size_t posn, len;

  sha3_256.reset();
  sha3_256.update(SALT, sizeof(SALT));
  sha3_256.update(challenge, sizeof(challenge));
  sha3_256.finalize(value, sizeof(value));

  // comparaison
  /*if (memcmp(value, test->hash, sizeof(value)) != 0)
      return false;

    return true;*/
}

void createChallenge() {
  char nextchar1;
  char nextchar2;
  for (int count = 0; count < DATA_SIZE; count++) {
    nextchar1 = random(65, 90);
    nextchar2 = random(97, 122);
    if (random(2) == 1) {
      challenge[count] = nextchar1;
    } else {
      challenge[count] = nextchar2;
    }
  }
}

void startAuth()
{
  createChallenge();
  generateHash();
  isAuthenticating = true;
  Serial.println("Challenge sent: ");
  for (int count = 0; count < DATA_SIZE; count++) {
    Serial.print((char)challenge[count]);
  }
  Serial.println("");
  Serial.println("Hash: ");
  //Serial.println(value);
  for (int count = 0; count < HASH_SIZE; count++) {
    Serial.print(value[count],BIN);
    Serial.print(" ");
  }
  
}

void readCommand() {
  // start authentication process
  if (command == 'A') {
    startAuth();
  }
}

void setup() {
  Serial.begin(9600);

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
