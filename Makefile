CC=gcc
CFLAGS=-c
LIBS=-lm

all: TypeK.o TypeKR.o TypeL.o TypeLR.o TypeS.o TypeSR.o TypeT.o TypeTR.o PTSV-5-080.o TSPV-2-797.o
	$(CC) TypeK.o $(LIBS) -o TypeK
	$(CC) TypeKR.o $(LIBS) -o TypeKR
	$(CC) TypeL.o $(LIBS) -o TypeL
	$(CC) TypeLR.o $(LIBS) -o TypeLR
	$(CC) TypeS.o $(LIBS) -o TypeS
	$(CC) TypeSR.o $(LIBS) -o TypeSR
	$(CC) TypeT.o $(LIBS) -o TypeT
	$(CC) TypeTR.o $(LIBS) -o TypeTR
	$(CC) PTSV-5-080.o $(LIBS) -o PTSV-5-080
	$(CC) TSPV-2-797.o $(LIBS) -o TSPV-2-797

TypeK.o: TypeK.c
	$(CC) $(CFLAGS) TypeK.c
TypeKR.o: TypeKR.c
	$(CC) $(CFLAGS) TypeKR.c
TypeL.o: TypeL.c
	$(CC) $(CFLAGS) TypeL.c
TypeLR.o: TypeLR.c
	$(CC) $(CFLAGS) TypeLR.c
TypeS.o: TypeS.c
	$(CC) $(CFLAGS) TypeS.c
TypeSR.o: TypeSR.c
	$(CC) $(CFLAGS) TypeSR.c
TypeT.o: TypeT.c
	$(CC) $(CFLAGS) TypeT.c
TypeTR.o: TypeTR.c
	$(CC) $(CFLAGS) TypeTR.c
PTSV-5-080.o: PTSV-5-080.c
	$(CC) $(CFLAGS) PTSV-5-080.c
TSPV-2-797.o: TSPV-2-797.c
	$(CC) $(CFLAGS) TSPV-2-797.c
clean:
	rm -f *.o TypeK TypeKR TypeL TypeLR TypeS TypeSR TypeT TypeTR PTSV-5-080 TSPV-2-797
