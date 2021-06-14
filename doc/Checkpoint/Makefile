EXTRA_SRC =
TEX = pdflatex

all: Checkpoint.pdf

.phony: all clean

Checkpoint.pdf: Checkpoint.tex
	while( $(TEX) $< ; grep -q "Rerun to get cross" $(<:.tex=.log)) ; \
	  do true ; \
	 done
	mv Checkpoint.pdf ..


clean:
	rm -f *.aux
	rm -f *.log
	rm -f ../Checkpoint.pdf
