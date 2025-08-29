# Step 1: Pi
Install Mainsail via Raspi Imager ()

# Step 2: Flash Mainboard
The mainboard of atlas is a [Creality Mainboard V4.2.7](https://github.com/bigtreetech/BIGTREETECH-SKR-V1.3/tree/master/BTT%20SKR%20V1.4).

```bash
cd klipper
make menuconfig
```


Select:
- Microcontroller: STM32
- Model: STM32F103
- Bootloader offset: 28KiB
- Comunication interface: USART1 PA10/PA9

```bash
make
```

In `~/klipper/out/klipper.bin` you can find the firmware you need to copy to a SD card. Don't forget to rename it from `klipper.bin` to `firmware.bin`!

**IMPORTANT:** The board is shitty and for some reason the Bootloader only flashes a file named `firmware.bin` only once, thus best keep the name `klipper.bin`.
There is also a good [blog post](https://www.drklipper.de/doku.php?id=klipper_faq:flash_guide:stm32f103:creality_4.2.7) talking about this.

After copying the firmware to a SD card, plugging it in and power cycling the mainboard, you can run:
```bash
ls /dev/serial/by-id/*
```

If you find something like `/dev/serial/by-id/usb-Klipper_\<controller name\>` you are done with this part!


# Step 3: Find klipper config
Here we have to combine two configs. The one for the MercuryOne can be found [here](https://minimal3dp.com/projects/3d-printers/mercury-one/mercury-one-klipper-config/), while the one for the pinout of the creality board can be initially copied via:
```bash
cd ~/
cp klipper/config/printer-creality-ender5pro-2020.cfg printer_data/config/printer.cfg
```


# Step 4: Few config setup steps
In the printer.cfg fill, scroll to \[mcu\] and fill in the result of
```bash
ls /dev/serial/by-id/*
```
such that you get something like
```
[mcu]
serial: /dev/serial/by-id/usb-1a86_USB_Serial-if00-port0
```

# Step 5: Setup Bigtreetech U2C
Atlas has a [Bigtreetech U2C V2.1](https://github.com/bigtreetech/U2C) equiped. For a better guide than the one klipper provides read [here](https://docs.meteyou.wtf/).

First we have to install the candlelight firmware on the U2C board:
```bash
# install requirements
sudo apt-get install cmake gcc-arm-none-eabi

cd ~/
# clone git repo
git clone --depth=1 -b stm32g0_support https://github.com/bigtreetech/candleLight_fw
cd ~/candleLight_fw

# create cmake toolchain
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/gcc-arm-none-eabi-8-2019-q3-update.cmake

# compile firmware
make budgetcan_fw
```

Next we need to put the board into DFU mode, by unplugging all the power and USB connection and pressing down the BOOT button while plugging the USB back in.
There should now be an extra blue light on. With
```bash
dfu-util -l
```
We can check if DFU mode worked. It should llok like this
```bash
dfu-util 0.9

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2016 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

Found DFU: [0483:df11] ver=0200, devnum=5, cfg=1, intf=0, path="1-1.3", alt=2, name="@Internal Flash   /0x08000000/64*02Kg", serial="207637974130"
Found DFU: [0483:df11] ver=0200, devnum=5, cfg=1, intf=0, path="1-1.3", alt=1, name="@Internal Flash   /0x08000000/64*02Kg", serial="207637974130"
Found DFU: [0483:df11] ver=0200, devnum=5, cfg=1, intf=0, path="1-1.3", alt=0, name="@Internal Flash   /0x08000000/64*02Kg", serial="207637974130"
```

**NOTE:** If this provides you with an error, it is due to insufficient right. If it works using `sudo` do **TODO**


Next we flash the firmware by with
```bash
cd ~/candleLight_fw/build
make flash-budgetcan_fw
```

Now power cicle the board.

Now we need to add the can interface in our pi by running
```bash
sudo vim /etc/network/interfaces.d/can0
```

and add

```
allow-hotplug can0
iface can0 can static
    bitrate 500000
    up ifconfig $IFACE txqueuelen 128
```

to the file. (Maybe increase bitrate to 1 Mio).
Next reboot the pi. Then run:
```bash
~/klippy-env/bin/python ~/klipper/scripts/canbus_query.py can0
```
which should result in
```
Total 0 uuids found
```
due to can bus being setup, but no one being connected to it


# Step 6: Setup Bigtreetech EBB V1.2
Atlas has a [Bigtreetech EBB36 V1.2](https://github.com/bigtreetech/EBB/tree/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB36%20CAN%20V1.1%20and%20V1.2) equiped.

First we want to install a bootloader on the EBB. For that run:
```bash
cd ~/
git clone https://github.com/Arksine/CanBoot

cd ~/CanBoot
make menuconfig
```

Select:
- Microcontroller: STM
- Model: STM32G0B1
- Build: 8KiB bootloader
- Clock: 8 MHz crystal
- Communication: CAN bus (on PB0/PB1)
- Application start offset: 8KiB offset
- CAN bus speed: 1000000 (1 Mio)
- Support bootloader entry on rapid double click of reset button: check
- Enable Status LED: check (Pin PA13)

Now run
```bash
make clean
make
```

Now we want to flash the bootloader. FIRST UNPLUG THE HEATER CARTRIDGE!!! Next pullout the CAN cable, put a jumper onto vbus to allow for power via USB, press and hold while pluging in USB and you now should be in DFU mode. Check again with:
```bash
dfu-util -l
```

And flash:
```bash
dfu-util -a 0 -D ~/CanBoot/out/canboot.bin -s 0x08000000:mass-erase:force:leave
```

Next we unplug the USB and pull out the jumper again as well as replugging everything CAN related. The next step is now to install klipper on the board.
```bash
cd ~/klipper
make menuconfig
```
Select:
- Enable extra low-level configuration options: check
- Microcontroller: STM
- Model: STM32G0B1
- Build: 8KiB bootloader (of CanBoot)
- Clock: 8 MHz crystal
- Communication: CAN bus (on PB0/PB1)
- CAN bus speed: 1000000 (1 Mio)

```bash
make clean
make
```

Next make sure everything CAN related is connected and run. IMPORTANT: You need to add a jumper on the EBB board such that CAN works. **TODO: Add picture**
```bash
python3 ~/CanBoot/scripts/flash_can.py -i can0 -q
```
To find the UUID, in our case _ba291efa1702_.

Now we flash klipper by running (with your UUID):
```bash
python3 ~/CanBoot/scripts/flash_can.py -f ~/klipper/out/klipper.bin -i can0 -u ba291efa1702
```

Later we can add CanBoot to our moonraker config by adding:
```bash
[update_manager canboot]
type: git_repo
origin: https://github.com/Arksine/CanBoot.git
path: ~/CanBoot
is_system_service: False
```
WARNING: There appears to be an issue with some earlier EBB board where updating passed trough power to the heater cartridge. Someone on amazon actually had his printer catch on fire because of it. SO USE WITH CARE AND MAYBE DON'T ALLOW FOR AUTOMATIC UPDATES!!!
