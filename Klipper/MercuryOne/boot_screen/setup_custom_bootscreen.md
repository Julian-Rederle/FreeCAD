# Install required packets
```bash
sudo apt install mpv -y
```

# Copy Video over
```bash
scp LogoToRedLab_red.mp4 freddie@mercuryone:/home/freddie/LogoToRedLab.mp4
```

# Copy custom service + video
```bash
scp bootvideo.service freddie@mercuryone:/home/freddie/bootvideo.service

# on Pi
sudo cp /home/freddie/bootvideo.service /etc/systemd/system/bootvideo.service
```

# Enable service
```bash
sudo systemctl enable bootvideo.service
```

# Disable regular klipperscreen boot
```bash
sudo systemctl disable KlipperScreen.service
```
