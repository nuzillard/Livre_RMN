SOURCES=livre.tex preambule.tex intro.tex bloch.tex ft.tex diagram.tex densite.tex densite2.tex rmn1d1.tex rmn1d2.tex rmn2d1.tex anxrefer.tex anxfourier.tex anxhamilt.tex anxmaths.tex
FIGS=ContSurf/cont1.eps ContSurf/cont2.eps ContSurf/cont3.eps ContSurf/cont4.eps ContSurf/surf1.eps ContSurf/surf2.eps ContSurf/surf3.eps ContSurf/surf4.eps
FIGSFROMPS = absorp.eps alias.eps apodC.eps apodH.eps cpmgcalib0.eps cpmgcalib1.eps dispers.eps gradecho.eps invcomp0.eps invcomp1.eps isochrom.eps ix-isl.eps ix-is.eps ixsz-isl.eps ixsz-is.eps ixszlz-isl.eps iy-is.eps iysz-is.eps larmor.eps off0.eps off1.eps off2.eps relaxlong.eps relaxtrans.eps retour.eps sinc.eps trunc.eps zerofill.eps
DATAPOINTS=sqr90zx sqr90zy sqr90zz sqr180zx sqr180zy sqr180zz
PSFROMBIN=cpmgcalib0.ps cpmgcalib1.ps gradecho.ps invcomp0.ps invcomp1.ps larmor.ps off0.ps off1.ps off2.ps retour.ps
BINSFROMC=cpmgcalib gradecho invcomp larmor offset0 offset1 offset2 retour
INSTALLDIR=~/winjmn/Desktop

livre.dvi : $(SOURCES) $(FIGS) $(FIGSFROMPS) $(DATAPOINTS)
	latex livre && latex livre && latex livre

livre.ps : livre.dvi
	dvips livre -o livre.ps

%.eps : %.ps
	ps2eps -f $<
	

cpmgcalib0.ps : cpmgcalib
	./cpmgcalib 0 > cpmgcalib0.ps
cpmgcalib1.ps : cpmgcalib
	./cpmgcalib 1 > cpmgcalib1.ps
gradecho.ps : gradecho
	./gradecho > gradecho.ps
invcomp0.ps : invcomp
	./invcomp 0 > invcomp0.ps
invcomp1.ps : invcomp
	./invcomp 1 > invcomp1.ps
larmor.ps : larmor
	./larmor > larmor.ps
off0.ps : offset0
	./offset0 > off0.ps
off1.ps : offset1
	./offset1 > off1.ps
off2.ps : offset2
	./offset2 > off2.ps
retour.ps : retour
	./retour > retour.ps

cpmgcalib : cpmgcalib.c libgfp.o libgfp.h libsimu1.o libsimu1.h
	gcc cpmgcalib.c libgfp.o libsimu1.o -o cpmgcalib -lm
gradecho : gradecho.c libgfp.o libgfp.h
	gcc gradecho.c libgfp.o -o gradecho -lm
invcomp : invcomp.c libgfp.o libgfp.h libsimu1.o libsimu1.h
	gcc invcomp.c libgfp.o libsimu1.o -o invcomp -lm
larmor : larmor.c libgfp.o libgfp.h
	gcc larmor.c libgfp.o -o larmor -lm
offset0 : offset0.c libgfp.o libgfp.h
	gcc offset0.c libgfp.o -o offset0 -lm
offset1 : offset1.c libgfp.o libgfp.h
	gcc offset1.c libgfp.o -o offset1 -lm
offset2 : offset2.c libgfp.o libgfp.h
	gcc offset2.c libgfp.o -o offset2 -lm
retour : retour.c libgfp.o libgfp.h
	gcc retour.c libgfp.o -o retour -lm
libgfp.o : libgfp.c
	gcc -c libgfp.c
libsimu1.o : libsimu1.c
	gcc -c libsimu1.c

sqr90zx : selpul.pl
	./selpul.pl 90 x > sqr90zx
sqr90zy : selpul.pl
	./selpul.pl 90 y > sqr90zy
sqr90zz : selpul.pl
	./selpul.pl 90 z > sqr90zz
sqr180zx : selpul.pl
	./selpul.pl 180 x > sqr180zx
sqr180zy : selpul.pl
	./selpul.pl 180 y > sqr180zy
sqr180zz : selpul.pl
	./selpul.pl 180 z > sqr180zz

ps :
	make livre.ps

clean :
	rm -f *.aux *.log *.toc *.lot *.lof *.dvi *.bak *.o *~ $(FIGSFROMPS) $(PSFROMBIN) $(BINSFROMC) $(DATAPOINTS)
livre.pdf : livre.dvi
	dvipdf -sPAPERSIZE=a4 livre.dvi livre.pdf

pdf :
	make livre.pdf

install :
	mv livre.pdf $(INSTALLDIR)
	make clean
	(cd .. ; tar czf livre.tar.gz Livre ; mv livre.tar.gz $(INSTALLDIR) )

