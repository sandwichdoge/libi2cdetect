#include <stdio.h>
#include <fcntl.h>
#include "i2cdet.h"
#include <unistd.h>


int main(int argc, char* argv[]) 
{
    if (argc != 3) {
        printf("Example usage: ./i2cdet.out /dev/i2c-0 0x5\n");
        return -1;
    }

    int addr = 0;
    sscanf(argv[2], "%X", &addr);

    const char* dev = argv[1];
    int fd = open(dev, O_RDWR);

    int rc = i2c_device_exists(fd, addr);
    switch (rc) {
    case 0:
        printf("Device with address 0x[%X] does not exist.\n", addr);
        break;
    case 1:
        printf("Device exists.\n");
        break;
    case -1:
        printf("Error opening %s.\n", dev);
        break;
    case -2:
        printf("Error in ioctl slave address.\n");
        break;
    }
    
    close(fd);
    return 0;
}
