CFLAGS=-Wall -Werror -g

test-subseq:test-subseq.o maxSeq.o
	gcc -o test-subseq test-subseq.o maxSeq.o

test-subseq.o:test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c

maxSeq.o:maxSeq.c
	gcc $(CFLAGS) -c maxSeq.c 
