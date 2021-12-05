TDIR = c:\complang\turboc

latlad.exe: clatlad.obj dsputils.obj
  tlink $(TDIR)\c0m clatlad dsputils,latlad,latlad,$(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

clatlad.obj: clatlad.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) clatlad.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


