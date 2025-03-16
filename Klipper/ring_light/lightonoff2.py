import time
import board
import neopixel
import pigpio

# Configure GPIO pin
pixel_pin = board.D18  # Use GPIO18 (PWM required)
num_pixels = 12        # Number of LEDs
ORDER = neopixel.GRB   # LED color order

# Initialize pigpio (no sudo needed)
pi = pigpio.pi()

if not pi.connected:
    print("Failed to connect to pigpio daemon. Make sure it's running.")
    exit(1)

pixels = neopixel.NeoPixel(
    pixel_pin, num_pixels, brightness=0.2, auto_write=False, pixel_order=ORDER
)

# Function to Set Colors
def set_color(r, g, b):
    pixels.fill((r, g, b))
    pixels.show()

# Example Usage
set_color(255, 0, 0)  # Red
time.sleep(1)
set_color(0, 255, 0)  # Green
time.sleep(1)
set_color(0, 0, 255)  # Blue
time.sleep(1)
set_color(0, 0, 0)    # Turn off LEDs

# Stop pigpio when done
pi.stop()
