TDIR = c:\complang\turboc

iirc2.exe: ciirc2.obj dsputils.obj
  tlink $(TDIR)\c0m ciirc2 dsputils,iirc2,iirc2,$(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

ciirc2.obj: ciirc2.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) ciirc2.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


