TDIR = c:\complang\turboc

lfir.exe: clfir.obj dsputils.obj
  tlink $(TDIR)\c0m clfir dsputils,lfir,lfir,$(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

clfir.obj: clfir.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) clfir.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


