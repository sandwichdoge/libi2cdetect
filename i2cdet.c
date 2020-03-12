#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>


static __s32 i2c_smbus_access(int file, char read_write, __u8 command, 
                                    int size, union i2c_smbus_data *data)
{
    struct i2c_smbus_ioctl_data args;

    args.read_write = read_write;
    args.command = command;
    args.size = size;
    args.data = data;
    return ioctl(file, I2C_SMBUS, &args);
}

int i2c_device_exists(const char* dev, int addr) 
{
    int fd = open(dev, O_RDWR);
    if (fd < 0) {
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        return -2;
    }

    int rc = i2c_smbus_access(fd, I2C_SMBUS_WRITE, 0, I2C_SMBUS_QUICK, NULL);

    if (rc < 0) {
        return 0;
    } else {
        return 1;
    }
}