TDIR = c:\complang\turboc

azlat.exe: cazlat.obj dsputils.obj
  tlink $(TDIR)\c0m cazlat dsputils,azlat,azlat,$(TDIR)\fp87 \
  $(TDIR)\mathm $(TDIR)\cm

cazlat.obj: cazlat.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) cazlat.c

dsputils.obj: dsputils.c
  tcc -c -mm -f87 -I$(TDIR) -L$(TDIR) dsputils.c


