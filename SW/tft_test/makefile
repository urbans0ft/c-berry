all: tft_test

tft_test: tft_test.o tft.o RAIO8870.o bmp.o
	gcc tft_test.o tft.o RAIO8870.o bmp.o -lbcm2835 -lrt -o tft_test

tft.o: tft.c tft.h
	gcc -Os -c tft.c

tft_test.o: tft_test.c 
	gcc -Os -c tft_test.c
	
RAIO8870.o: RAIO8870.c RAIO8870.h
	gcc -Os -c RAIO8870.c

bmp.o: bmp.c bmp.h RAIO8870.h
	gcc -Os -c bmp.c

clean:
	rm -rf *o test_tft

