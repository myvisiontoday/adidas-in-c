PN=encode

CFLAGS=-Wall -Werror -Iproduct -I../Unity -Itest

#add your own other c files here
SHARED=helper.c

all: 
	gcc $(CFLAGS) $(PN).c $(SHARED) -o $(PN) 
	gcc $(CFLAGS) channel.c $(SHARED) -o channel 
	gcc $(CFLAGS) decode.c $(SHARED) -o decode 
 
clean:
	rm -rf administrationTest $(PN) 

valgrind: 
	valgrind ./$(PN)

.PHONY: clean test valgrind
