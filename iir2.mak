TDIR = c:\complang\turboc

iir2.exe: ciir2.obj dsputils.obj
  tlink $(TDIR)\c0m ciir2 dsputils, iir2,iir2, $(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

ciir2.obj: ciir2.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) ciir2.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


