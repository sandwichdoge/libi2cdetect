# libi2cdetect

Lock-free library to detect whether an i2c slave device exists on bus based on its address.

## Cross-compile example for ARMv7

Assuming build machine has the required toolchain installed.

```
export CC=arm-linux-gnueabihf-gcc
export AR=arm-linux-gnueabihf-ar
make
```

## C library usage example

```
#include "i2cdet.h"
...
int fd = open("/dev/i2c-0", O_RDWR);
int rc = i2c_device_exists(fd, addr);
if (rc < 0) {
    // Handle i2c dev error.
} else if (rc) {
    // Handle device exists.
} else {
    // Handle device does not exist.
}
close(fd);
```

Linking
```
-Llib2icdetect/ -li2cdet
```

## Cmdline example

```
./i2cdet.out /dev/i2c-0 0x05
```
