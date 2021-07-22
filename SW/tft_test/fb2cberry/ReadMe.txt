#########################################
#                                       #
#      Introduction to fb2cberry        #
#                                       #
#########################################


This software clones the data from monitor (/dev/fb0) to the C-Berry. 
The BCM scales the resolution of the monitor down to the resolution 
from the C-Berry (320x240) by the gpu, not by cpu. 
If the software is running, the main screen can be seen on the C-Berry. 


Adjustment resolution
---------------------------------
The resolution can be changed in two ways:

	1. choose the resolution via HDMI mode
		a) open file /boot/config.txt
		
	   	b) change the following 
		   enable	disable_overscan = 1
		   disable	#hdmi_force_hotplug = 1
		   disable	#config_hdmi_boost = 4
		   disable 	#overscan_left = 24
		   disable 	#overscan_right = 24
		   disable 	#overscan_top = 16
		   disable 	#overscan_bottom = 16
		   disable 	#disable_overscan = 0
	   	   enable       hdmi_group = 2
	   	   enable	hdmi_mode = x

		The values for hdmi_modes are defined on the following link:
		http://elinux.org/RPiconfig#Video_mode_options

		c) save and exit file

		d) reboot the Raspberry Pi


	2. choose the resolution via definition of the display width and height (e.g. 320x240)
 		a) open file /boot/config.txt
		
	   	b) change the following 
		   enable	disable_overscan = 1
		   disable	#hdmi_force_hotplug = 1
		   disable	#config_hdmi_boost = 4
		   disable 	#overscan_left = 24
		   disable 	#overscan_right = 24
		   disable 	#overscan_top = 16
		   disable 	#overscan_bottom = 16
		   disable 	#disable_overscan = 0
	   	   enable       frambuffer_width= 320
	   	   enable	frambuffer_height= 240

		c) save and exit file

		d) reboot the Raspberry Pi



Start the software
---------------------------------
Compile the software:     sudo make -C /path/to/file/fb2cberry/

Start the software by:    sudo /path/to/file/fb2cberry	   

Start the software in the background by:    sudo /path/to/file/fb2cberry &
