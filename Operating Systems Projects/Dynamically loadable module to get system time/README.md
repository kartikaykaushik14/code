C program in Linux for a dynamically loadable module that allows us to get the current date and time when the module if read from a user-mode application.

System_Time

Command to insert module in Kernel: 	sudo ./insmod System_Time.ko
Command to remove module from Kernel: 	sudo rmmod System_Time
Command to view messages: 		dmesg
Command to read from device: 		cat /dev/st
