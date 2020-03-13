# libi2cdetect

Detect whether i2c device exists on bus.

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
if (i2c_device_exists(fd, addr)) {
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
./i2c.out /dev/i2c-0 0x05
```
