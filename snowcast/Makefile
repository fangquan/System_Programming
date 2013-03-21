CC = gcc
CFLAGS = -Wall -Wextra -Wunused
CFLAGS += -std=c99 -g 
OBJS = snowcast.c

client: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o snowcast_client

clean:
	rm -rvf *.o client snowcast_client
