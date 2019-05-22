LIBS = -pthread
amaze : amaze.o queue.o main.o libmxml/libmxml.a
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

main.o : main.c filenames.h

amaze.o : amaze.c amaze.h

queue.o : queue.c queue.h

.PHONY clean :
	-rm -f *.o amaze tags cscope*
