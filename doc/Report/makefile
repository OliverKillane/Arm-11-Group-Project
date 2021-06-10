EXTRA_SRC =
TEX = pdflatex

all: Report.pdf

.phony: all clean

Report.pdf: Report.tex
	while( $(TEX) $< ; grep -q "Rerun to get cross" $(<:.tex=.log)) ; \
	  do true ; \
	 done
	mv Report.pdf ..


clean:
	rm -f *.aux
	rm -f *.log
	rm -f ../Report.pdf
