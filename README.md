# beagle-oled-ssd1306

## How to use OLED diplay based on SSD1306 as framebuffer on BeagleBone

Following steps has been made on BeagleBone Black and Gree but it should work on another BeagleBone board with a few changes. 

It was used Debian Console Image available on [here](https://beagleboard.org/latest-images).

### The Circuit
This tutorial uses BeagleBone's I2C1, so the image below shows how to connect the OLED display on Beaglebone:  

<img src="https://raw.githubusercontent.com/thalestas/beagle-oled-ssd1306/main/img/bb_circuit.png" width="100">

### The Setup
1. Download ADS1115 DTBO (Device Tree Blob Overlay) available [here](dts/) or you can build it through official overlays beagleboards repo [https://github.com/beagleboard/bb.org-overlays](https://github.com/beagleboard/bb.org-overlays);  
You can download through the command below as well:
```
wget https://github.com/thalestas/beagle-oled-ssd1306/raw/main/dts/BB-I2C1-SSD1306.dtbo 
```

2. Copy the ADS1115 DTBO to BeagleBone in ```/lib/interface```. For example:
```
cp BB-I2C1-SSD1306.dtbo /media/username/rootfs/lib/firmware/
```
Note that ```username``` should be your user.

3. Add the DTBO as U-Boot overlay in uEnv, to do that, open the file below:
```
vim /media/username/rootfs/boot/uEnv.txt
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
4. After Start Kernel, OLED display should start show terminal.
