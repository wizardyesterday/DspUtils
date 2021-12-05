TDIR = c:\complang\turboc

iir.exe: ciir.obj dsputils.obj
  tlink $(TDIR)\c0m ciir dsputils, iir,iir, $(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

ciir.obj: ciir.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) ciir.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


