
all: sof


clean:
	rm sof

.PHONY: all clean

sof: sof.c sof.h
	$(CC) $(CFLAGS) -o $@ $< 