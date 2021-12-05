TDIR = c:\complang\turboc

iirp.exe: ciirp.obj dsputils.obj
  tlink $(TDIR)\c0m ciirp dsputils, iirp,iirp, $(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

ciirp.obj: ciirp.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) ciirp.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


