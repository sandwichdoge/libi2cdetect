#include <stdio.h>
#include <fcntl.h>
#include "i2cdet.h"
#include <unistd.h>

#define bool_str(d) d ? "Yes" : "No"

int main(int argc, char* argv[]) 
{
    if (argc != 3) {
        printf("Example usage: ./i2c.out /dev/i2c-0 0x5");
        return -1;
    }

    int addr = 0;
    sscanf(argv[2], "%X", &addr);

    const char* dev = argv[1];
    int fd = open(dev, O_RDWR);

    printf("Device exists:[%s]\n", i2c_device_exists(fd, addr) == 1 ? "Yes" : "No");
    
    close(fd);
    return 0;
}
