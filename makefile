CFLAGS = -std=gnu99

all: P11 P12 P21 P22 

P11: P11.o helpers.o
	gcc $(CFLAGS) P11.o helpers.o -o P11 -lm

P12: P12.o helpers.o
	gcc $(CFLAGS) P12.o helpers.o -o P12 -lm

P21: P21.o helpers.o
	gcc $(CFLAGS) P21.o helpers.o -o P21 -lm

P22: P22.o helpers.o
	gcc $(CFLAGS) P22.o helpers.o -o P22 -lm

P11.o: P1.1.c
	gcc $(CFLAGS) -c P1.1.c -o P11.o

P12.o: P1.2.c
	gcc $(CFLAGS) -c P1.2.c -o P12.o

P21.o: P2.1.c
	gcc $(CFLAGS) -c P2.1.c -o P21.o

P22.o: P2.2.c
	gcc $(CFLAGS) -c P2.2.c -o P22.o

helpers.o: helpers.c
	gcc $(CFLAGS) -c helpers.c -o helpers.o

clean:
	rm *o P11 P12 P21 P22
