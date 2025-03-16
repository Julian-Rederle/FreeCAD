import serial
import time

# Set up serial communication with the ESP32
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(1)  # Allow time for the serial connection to establish

# Send the switch command
ser.write(b'switch\n')
ser.flush()

# Wait for a response from the ESP32
response = ser.readline().decode().strip()

if response:
    print(f"ESP32 says: {response}")
else:
    print("No response from ESP32")

ser.close()
