
CROSS_COMPILE=
SRCS = aesdsocket.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Wall -Werror

.PHONY: all
all: aesdsocket

.PHONY: clean
clean:
	rm -f aesdsocket *.o valgrind-out.txt

$(OBJS): %.o: %.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $<

aesdsocket: $(OBJS)
	$(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $?
