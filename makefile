OBJS= PA1.o

PA1.o: PA1.c
	gcc PA1.c -o PA1.o
clean:
	rm $(OBJS)
