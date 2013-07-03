CC=gcc
CFLAGS=-std=gnu99 -c -D__LINUX__ `pkg-config --cflags glib-2.0`
LDFLAGS=-lm -ll `pkg-config --libs glib-2.0`
SOURCES=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))

Confaid:$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

-include $(SOURCES:.c=.d)

%.d:%.c
	$(CC) -MM $(CFLAGS) $< >$@.$$$$;\
	sed 's,\($*\).o[ :]*,\1.o $@:,g' < $@.$$$$ >$@;\
	rm -f $@.$$$$

.PHONY:clean
clean:
	rm -f *.o *.d *.dic *.cdf Confaid
