#define PIN_LED          5
#define PIN_RELAY_RED    14
#define PIN_RELAY_YELLOW 12
#define PIN_RELAY_WHITE  13
#define PIN_BUTTON       4

#include <Bounce2.h> 
Bounce2::Button button = Bounce2::Button();

/*
 * 
 * when power startup:
 * RED on: NC2 port
 * YELLOW off: NO3
 * WHITE off: NO4
 * 
 * skip port 1 - it flops around when MCU boots up
 * 
 * 
 * State diagram:
 * 
 * R / Y / W
 * 1   0   1
 * 1   1   0
 * 0   0   0
 * 
 */

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_RELAY_RED, OUTPUT);
  pinMode(PIN_RELAY_YELLOW, OUTPUT);
  pinMode(PIN_RELAY_WHITE, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  button.attach ( PIN_BUTTON, INPUT_PULLUP);
  button.interval( 5 );
  button.setPressedState( LOW ); 
}

void wait(int seconds) {
  for (int i = 0; i <= seconds; i++) {  
    digitalWrite(PIN_LED, LOW);
    delay(500);
    digitalWrite(PIN_LED, HIGH);
    delay(500);
  }
}

void loop() {
  Serial.println("WAIT");
  // UPDATE THE BUTTON BY CALLING .update() AT THE BEGINNING OF THE LOOP:
  button.update();
  
  if (button.pressed()) {
    Serial.println("RUN");
    runLights();
  }
}

void runLights() {   
  Serial.println("GO");
  digitalWrite(PIN_RELAY_RED, HIGH);
  digitalWrite(PIN_RELAY_YELLOW, LOW);
  digitalWrite(PIN_RELAY_WHITE, HIGH);
  wait(8);
  
  Serial.println("YELLOW");
  digitalWrite(PIN_RELAY_WHITE, LOW);
  digitalWrite(PIN_RELAY_YELLOW, HIGH);
  wait(4);
  
  Serial.println("STOP... and wait");
  digitalWrite(PIN_RELAY_YELLOW, LOW);
  digitalWrite(PIN_RELAY_RED, LOW);
  wait(4);

  Serial.println("DONE");
}
