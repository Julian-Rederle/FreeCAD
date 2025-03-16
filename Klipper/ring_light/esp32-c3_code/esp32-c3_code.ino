#include <Adafruit_NeoPixel.h>

#define LED_PIN    5   // GPIO Pin for the NeoPixel Ring
#define LED_COUNT  12  // Number of LEDs in the NeoPixel Ring

// Define the built-in LED pin for ESP32 (usually GPIO2)
#define LED_BUILTIN 2

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
bool isOn = false;  // LED state

void setup() {
  Serial.begin(115200);  // Start serial communication
  strip.begin();         // Initialize the NeoPixel strip
  strip.show();          // Ensure the LEDs are off initially
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read incoming command
    command.trim();  // Remove any unnecessary spaces or newlines

    if (command == "switch") {
      isOn = !isOn;  // Toggle LED state

      if (isOn) {
        setRingWhite();  // Set LEDs to white
        Serial.println("LED ON");
      } else {
        turnOffRing();  // Turn off the LEDs
        Serial.println("LED OFF");
      }
    }
  }
}

// Set all NeoPixel LEDs to white
void setRingWhite() {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));  // White color
  }
  strip.show();  // Update the LEDs
}

// Turn off all NeoPixel LEDs
void turnOffRing() {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));  // Turn off LEDs
  }
  strip.show();  // Update the LEDs
}
