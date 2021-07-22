XINCDIR +=-I$(ROOTDIR)/opt/vc/include
XINCDIR +=-I$(ROOTDIR)/opt/vc/include/interface/vmcs_host/linux
XINCDIR +=-I$(ROOTDIR)/opt/vc/include/interface/vcos/pthreads -DRPI=1
XLIBS +=-L/opt/vc/lib -lbcm_host

all: fb2cberry

fb2cberry: tft.o RAIO8870.o fb2cberry.o
	gcc $(XLIBS) $(XINCDIR) $(LIBS) fb2cberry.o tft.o RAIO8870.o -lbcm2835 -lrt -lm -o fb2cberry
 
fb2cberry.o: fb2cberry.c 
	gcc $(XLIBS) $(XINCDIR) $(LIBS) -Os -c fb2cberry.c

tft.o: tft.c tft.h
	gcc $(XLIBS) $(XINCDIR) $(LIBS) -Os -c tft.c

RAIO8870.o: RAIO8870.c RAIO8870.h
	gcc $(XLIBS) $(XINCDIR) $(LIBS) -Os -c RAIO8870.c

clean:
	rm -rf *o fb2cberry

