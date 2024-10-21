.PHONY:all
all: consumer producer 

consumer:consumer.c
	gcc -o consumer consumer.c semaphore.c  -std=c99
producer:producer.c
	gcc -o producer producer.c semaphore.c -std=c99 


.PHONY:clean
clean:
	rm -f consumer producer
