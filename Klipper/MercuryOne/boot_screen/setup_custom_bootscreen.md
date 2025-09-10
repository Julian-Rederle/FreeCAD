# Install required packets
```bash
sudo apt install mpv
```

# Copy Video over
```bash
scp LogoToRedLab.mp4 beast@TheSmallBeast2:/home/beast/.
```

# Copy custom service + video
```bash
scp bootvideo.service beast@TheSmallBeast2:/home/beast/bootvideo.service

# on Pi
cp /home/beast/bootvideo.service /etc/systemd/system/bootvideo.service
```

# Enable service
```bash
sudo systemctl enable bootvideo.service
```

# Disable regular klipperscreen boot
```bash
systemctl disable KlipperScreen.service
```
