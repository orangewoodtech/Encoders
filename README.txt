EnoderX,Y,Z Are connected to Arduino Uno1,2,3.
Encoder data is then requested from all the 3 UNOs by Arduino Mega with help of I2C bus.

I2C Master: Arduino Mega
I2C Slaves: Arudino Uno 1
	    Arudino Uno 2
	    Arudino Uno 3	

Arduino Folder contains codes for all the 3 UNOs.
Mega floder contains code for Mega to request and collect the data from UNOs.
MegaControl contains code for Mega to validate the movements of CNC machine