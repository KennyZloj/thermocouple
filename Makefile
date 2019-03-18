all:
	gcc TypeK.c -o TypeK -lm
	gcc TypeKR.c -o TypeKR -lm
	gcc TypeL.c -o TypeL -lm
	gcc TypeLR.c -o TypeLR -lm
	gcc TypeS.c -o TypeS -lm
	gcc TypeSR.c -o TypeSR -lm
	gcc TypeT.c -o TypeT -lm
	gcc TypeTR.c -o TypeTR -lm
	gcc PTSV-5-080.c -o PTSV-5-080 -lm
	gcc TSPV-2-797.c -o TSPV-2-797 -lm
TypeK:
	gcc TypeK.c -o TypeK -lm
TypeKR:
	gcc TypeKR.c -o TypeKR -lm
TypeL:
	gcc TypeL.c -o TypeL -lm
TypeLR:
	gcc TypeLR.c -o TypeLR -lm
TypeS:
	gcc TypeS.c -o TypeS -lm
TypeSR:
	gcc TypeSR.c -o TypeSR -lm
TypeT:
	gcc TypeT.c -o TypeT -lm
TypeTR:
	gcc TypeTR.c -o TypeTR -lm
PTSV-5-080:
	gcc PTSV-5-080.c -o PTSV-5-080 -lm
TSPV-2-797:
	gcc TSPV-2-797.c -o TSPV-2-797 -lm
clean:
	rm -f TypeK TypeKR TypeL TypeLR TypeS TypeSR TypeT TypeTR PTSV-5-080 TSPV-2-797
