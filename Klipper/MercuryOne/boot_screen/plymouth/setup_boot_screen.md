# Install plymouth
```bash
# On the Pi
sudo apt install plymouth plymouth-themes
```

# Convert boot video from mp4
Plymouth doesn’t play MP4 directly. To show a video, you generally need to convert it to an image sequence (PNG frames) or an animated GIF converted to a Plymouth animation:
```bash
# On the machine with the video
mkdir bootvideo_frames
ffmpeg -i LogoToRedLab.mp4 -vf "scale=480:800:force_original_aspect_ratio=decrease,fps=30" bootvideo_frames/frame%04d.png
```

# Setup folders
we need the following structure
```
redlabs/
 ├─ redlabs.plymouth
 ├─ bootvideo.script
 └─ bootvideo
    ├─ image_1.png
    ├─ image_2.png
    └─ ...
```

Thus run:
```bash
sudo mkdir -p /usr/share/plymouth/themes/redlabs/bootvideo
mkdir -p ~/plymouth/themes/redlabs/bootvideo

# On the machine with the video
scp -r redlabs.plymouth beast@thesmallbeast2:~/plymouth/themes/redlabs/redlabs.plymouth
scp -r bootvideo_frames/* beast@thesmallbeast2:~/plymouth/themes/redlabs/bootvideo
scp -r bootvideo.script beast@thesmallbeast2:~/plymouth/themes/redlabs/bootvideo/bootvideo.script

sudo cp ~/plymouth/themes/redlabs/redlabs.plymouth /usr/share/plymouth/themes/redlabs/redlabs.plymouth
sudo cp ~/plymouth/themes/redlabs/bootvideo/* /usr/share/plymouth/themes/redlabs/bootvideo
```

# Set Plymouth Theme
```bash
sudo plymouth-set-default-theme redlabs -R
```

# Test setup
```bash
sudo plymouthd
sudo plymouth --show-splash
sudo plymouth quit

```

# Other important settings

## Edit boot command
Add
```
quiet splash
```

to `sudo nano /boot/firmware/cmdline.txt`
