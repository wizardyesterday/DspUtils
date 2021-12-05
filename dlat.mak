TDIR = c:\complang\turboc

dlat.exe: cdlat.obj dsputils.obj
  tlink $(TDIR)\c0m cdlat dsputils, dlat,dlat, $(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

cdlat.obj: cdlat.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) cdlat.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


