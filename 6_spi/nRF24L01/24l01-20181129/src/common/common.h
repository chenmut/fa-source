#ifndef _COMMON_H_
#define _COMMON_H_
	#include <string.h>
	#include <unistd.h> 
	#include <stdlib.h> 
	#include <sys/types.h> 
	#include <sys/stat.h> 
	#include <sys/ioctl.h> 
	#include <asm/ioctl.h>
	#include <fcntl.h>
	#include <linux/fs.h> 
	#include <errno.h> 
	#include <stdarg.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <pthread.h>
    #include <linux/types.h>
	#include <linux/spi/spidev.h>
	#include <wiringPi.h>
    #include <wiringPiSPI.h>
	#define BOARD_NANOPI_M1            (68330)  //'H3'
	
#endif		//_COMMON_H_
