CC = gcc
CFLAGS = -Wall -g  
CLIBS = -L../lib/ -lwiringPi -lpthread

INCLUDES = $(wildcard ./*.h ./driver/*.h ./common/*.h ) 
SOURCES = $(wildcard ./*.c ./driver/*.c ./common/*.c )
INCLUDE_DIRS = -I. -I./driver/ -I./common/

TARGET = ledButton
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)
$(OBJECTS) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

.PHONY : clean
clean:
	rm -rf $(TARGET) $(OBJECTS)
