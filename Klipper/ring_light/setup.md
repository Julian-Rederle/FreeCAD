# Wiring
Wiring to the Pi can be found in the documentation pdf of the ring light.

# Install requirements
In this case we need a python env for the required packets
```bash
# If not yet done
sudo apt-get install python3-venv -y

# Make extra dir for our stuff in the home dir
mkdir ~/ring_light
cd ring_light

# Create and enter venv
python3 -m venv pyringlight
source pyringlight/bin/activate

# Install packets
pip install rpi_ws281x adafruit-circuitpython-neopixel
pip install adafruit-blinka

```

# The script
Next we copy the `lightonoff.py` to our `ring_light` folder

Due to the fact that some pins are only accessable with root rights, we need the [trick](https://stackoverflow.com/questions/59638319/how-to-run-neopixel-without-sudo-permissions-for-use-in-an-alexa-app) of using SPI pins. Thus run:
```bash
raspi-config
```
and activate the SPI interface.

# Klipper macro
In our clipper `macro.cfg` file we add:

```
[gcode_shell_command light_script]
command: /home/ender/ring_light/pyringlight/bin/python /home/ender/ring_light/lightonoff.py
timeout: 30.
verbose: True

[gcode_macro TOGGLE_LIGHT]
gcode:
  RUN_SHELL_COMMAND CMD=light_script PARAMS=
```

For this to work we need to downlaod an "addon" for klipper as described [here](https://www.reddit.com/r/klippers/comments/16bc5lm/section_gcode_shell_command_backup_cfg_is_not_a/)

```bash
wget -O ~/klipper/klippy/extras/gcode_shell_command.py https://raw.githubusercontent.com/th33xitus/kiauh/master/resources/gcode_shell_command.py
```

afterwards we need to restart klipper
