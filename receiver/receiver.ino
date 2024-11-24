#include <ESP8266WiFi.h>
#include <espnow.h>

#define LEFT_FORWARD 14
#define LEFT_BACKWARD 12
#define RIGHT_FORWARD 13 
#define RIGHT_BACKWARD 15 

typedef struct struct_message {
  char command[10];
} struct_message;

struct_message myData;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);

  if (esp_now_init() != ERR_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onDataRecv);
}

void onDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Command received: ");
  Serial.println(myData.command);

  if (strcmp(myData.command, "forward") == 0) 
    moveForward();
  else if (strcmp(myData.command, "backward") == 0) 
    moveBackward();
  else if (strcmp(myData.command, "left") == 0) 
    turnLeft();
  else if (strcmp(myData.command, "right") == 0) 
    turnRight();
  else
    stopMotors();
}

void moveForward() {
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
}

void moveBackward() {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH);
}

void turnLeft() {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
}

void turnRight() {
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH);
}

void stopMotors() {
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
}

void loop() {}
