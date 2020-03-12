OBJECTS=main.o

all: $(OBJECTS) BUILD_LIB
		$(CC) $(OBJECTS) -o i2c.out -L./ -li2cdetect

BUILD_LIB: i2cdet.o 
		$(AR) crf libi2cdetect.a i2cdet.o

%.o: %.c
		$(CC) -c $(CFLAGS) $< -o $@

clean:
		rm -f *.o *.out