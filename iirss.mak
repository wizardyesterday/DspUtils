TDIR = c:\complang\turboc

iirss.exe: ciirss.obj dsputils.obj
  tlink $(TDIR)\c0m ciirss dsputils,iirss,iirss,$(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

ciirss.obj: ciirss.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) ciirss.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


