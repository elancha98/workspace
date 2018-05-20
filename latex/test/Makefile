all: temp.pdf main.pdf formatted.pdf t.pdf musta.pdf

temp.pdf: temp.tex
	pdflatex temp.tex

main.pdf: main.tex
	pdflatex main.tex

formatted.pdf: formatted.tex
	pdflatex formatted.tex

t.pdf: t.tex
	pdflatex t.tex

musta.pdf: musta.tex
	pdflatex musta.tex

clean:
	rm -f *.aux
	rm -f *.log
	rm -f *.out
	rm -f *.pdf
	rm -f *.synctex.gz
	rm -f *.auxlock
	rm -f *.toc