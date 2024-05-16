#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIGGER_PIN D7
#define ECHO_PIN D6
#define GREEN_LED D5
#define YELLOW_LED D4
#define RED_LED D3
#define BUZZER D0

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound is 0.034 cm/us

  display.clearDisplay();
  display.setTextSize(2); // Increase text size
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Distance: ");
  display.print(distance);
  display.print(" cm");
  display.display();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance > 20) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    analogWrite(BUZZER, 0); // Turn off the buzzer
  }
  else if(distance <= 20 && distance > 10) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    tone(BUZZER, 1000); // Low frequency buzzer tone
    delay(500); // Adjust the delay between each beep for the yellow function
    noTone(BUZZER); // Stop the buzzer
  }
  else {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    tone(BUZZER, 2000); // High frequency buzzer tone
  }

  delay(1000); // Adjust for your application
}
