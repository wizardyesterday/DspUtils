TDIR = c:\complang\turboc

aplat.exe: caplat.obj dsputils.obj
  tlink $(TDIR)\c0m caplat dsputils,aplat,aplat,$(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

caplat.obj: caplat.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) caplat.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


