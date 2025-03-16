#include <Adafruit_NeoPixel.h>

#define LED_PIN 6    // GPIO pin for NeoPixel ring (use the correct pin for your setup)
#define LED_COUNT 12 // Number of LEDs in the ring

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

bool isOn = false; // LED state

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); // Built-in LED (onboard LED) as output
    Serial.begin(115200);         // Start serial communication
    strip.begin();                // Initialize the NeoPixel strip
    strip.show();                 // Ensure all LEDs are off at startup

    // Indicate the system is starting (onboard LED will blink)
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    // Check if there's data on the serial port
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n'); // Read incoming serial data
        command.trim(); // Remove any whitespace

        // If the command is "switch", toggle the state of the NeoPixel ring
        if (command == "switch") {
            isOn = !isOn; // Toggle the state

            if (isOn) {
                setRingWhite();
                Serial.println("LED ON");  // Send response to serial
            } else {
                turnOffRing();
                Serial.println("LED OFF"); // Send response to serial
            }
        }
    }
}

void setRingWhite() {
    for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255)); // Set all LEDs to white
    }
    strip.show();
}

void turnOffRing() {
    for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0)); // Turn off all LEDs
    }
    strip.show();
}
