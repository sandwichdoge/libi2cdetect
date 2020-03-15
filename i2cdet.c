#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


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

static __s32 i2c_smbus_read_byte(int file)
{
	union i2c_smbus_data data;
	int err;

	err = i2c_smbus_access(file, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data);
	if (err < 0)
		return err;

	return 0x0FF & data.byte;
}

int i2c_device_exists(int fd, int addr) 
{
    if (fd < 0) {
        return -1;
    }

    unsigned long funcs = 0;
    if (ioctl(fd, I2C_FUNCS, &funcs) < 0) {
        return -2;
    }

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        return -3;
    }

    int rc = 0;
    if (funcs & I2C_FUNC_SMBUS_QUICK) {
        rc = i2c_smbus_access(fd, I2C_SMBUS_WRITE, 0, I2C_SMBUS_QUICK, NULL);
    } else if (funcs & I2C_FUNC_SMBUS_READ_BYTE) {
        rc = i2c_smbus_read_byte(fd);
    } else {
        return -4;  // Bus does not support detection commands.
    }

    if (rc < 0) {
        return 0;
    } else {
        return 1;
    }
}