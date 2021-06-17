# beagle-oled-ssd1306

## How to use OLED diplay based on SSD1306 as framebuffer on BeagleBone

Following steps has been made on BeagleBone Black and Gree but it should work on another BeagleBone board with a few changes. 

It was used Debian Console Image available on [here](https://beagleboard.org/latest-images).

It is assumed that SSD1407 device driver is already enabled. On Debian Console Image it is already included built-in.
You can use the following command to check. It should return ```CONFIG_FB_SSD1307=y```:
```
$ zcat /proc/config.gz | grep -i ssd1307
```


### The Circuit
This tutorial uses BeagleBone's I2C1, so the image below shows how to connect the OLED display on Beaglebone:  

<p align="center">
<kbd>
	<img src="https://raw.githubusercontent.com/thalestas/beagle-oled-ssd1306/main/fig/bb_circuit.png" width="500">
</kbd>
</p>

### The Setup
1. Download ADS1115 DTBO (Device Tree Blob Overlay) available [here](dts/) or you can build it through official overlays beagleboards repo [https://github.com/beagleboard/bb.org-overlays](https://github.com/beagleboard/bb.org-overlays);  
You can download through the command below as well:
```
$ wget https://github.com/thalestas/beagle-oled-ssd1306/raw/main/dts/BB-I2C1-SSD1306.dtbo 
```

2. Copy the ADS1115 DTBO to BeagleBone in ```/lib/interface```. For example:
```
$ sudo cp BB-I2C1-SSD1306.dtbo /media/username/rootfs/lib/firmware/
```
Note that ```username``` should be your user.

3. Add the DTBO as U-Boot overlay in uEnv, to do that, open the file below:
```
$ vim /media/username/rootfs/boot/uEnv.txt
```

And add the BB-I2C1-SSD1306.dtbo:
```
###Additional custom capes
uboot_overlay_addr4=/lib/firmware/BB-I2C1-SSD1306.dtbo
#uboot_overlay_addr5=/lib/firmware/<file5>.dtbo
#uboot_overlay_addr6=/lib/firmware/<file6>.dtbo
#uboot_overlay_addr7=/lib/firmware/<file7>.dtbo
```

Boot BeagleBone and you should see the U-Boot overlay loading:
```
uboot_overlays: loading /lib/firmware/BB-ADC-00A0.dtbo ...
867 bytes read in 66 ms (12.7 KiB/s)
```
4. After Kernel starts, OLED display should show terminal output.

### Set Console Font

Default font size is too big to 128x64 pixels resolution. So, to improve it, we can change the console font to fit better.
The steps below, describe how to set tom-thumb console font, which it is a 4x6 font.  
Reference: https://robey.lag.net/2010/01/23/tiny-monospace-font.html

Copy the file ```tom-thumb.psf.gz``` to sdcard:
```
$ cp tom-thumb.psf.gz /media/username/rootfs/home/debian/
```
To set the font, we are going to use ```setfont``` command, but it is unavailable by default on Debian Console Image. So, we are going to use busybox.  
Copy busybox to sdcard using the command below:
```
$ cp busybox /media/username/rootfs/home/debian/
```
Using OLED console on BeagleBone, set tom-thumb font:
```
debian@beaglebone:~$ ./busybox setfont tom-thumb.psf.gz
```

Image below shows the system version through OLED SSD1306 console display.
<p align="center">
<kbd>
	<img src="https://raw.githubusercontent.com/thalestas/beagle-oled-ssd1306/main/fig/oled_beagle.jpg" width="1000">
</kbd>
</p>

### References 
[Device Tree Overlay by Adafruit](https://learn.adafruit.com/introduction-to-the-beaglebone-black-device-tree/device-tree-overlays)  
[foldedtoad - raspberry-pi-oled](https://github.com/foldedtoad/raspberry-pi-oled)  
[elinux - U-boot Overlays](https://elinux.org/Beagleboard:BeagleBoneBlack_Debian#U-Boot_Overlays)  
