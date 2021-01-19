CLAGS=-Wall -g -ansi -pg -02 -std=c99
OBJS=main.o denoise.o read.o write.o timing.o
all = denoise

denoise: $(OBJS)
	$(CC) -o $@ $?

clean:
	rm -rf $(OBJS) $(all) *~

