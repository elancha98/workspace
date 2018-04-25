all: entregable_multi.pdf entregable_multi_2.pdf entregable_topo.pdf discreta_reuc_2016_2.pdf practica_io_3.pdf discreta_2_11_d.pdf temp.pdf

entregable_multi.pdf: entregable_multi.tex
	pdflatex entregable_multi.tex

entregable_multi_2.pdf: entregable_multi_2.tex
	pdflatex entregable_multi_2.tex

entregable_topo.pdf: entregable_topo.tex
	pdflatex entregable_topo.tex

discreta_reuc_2016_2.pdf: discreta_reuc_2016_2.tex
	pdflatex discreta_reuc_2016_2.tex

practica_io_3.pdf: practica_io_3.tex
	pdflatex practica_io_3.tex

discreta_2_11_d.pdf: discreta_2_11_d.tex
	pdflatex discreta_2_11_d.tex

temp.pdf: temp.tex
	pdflatex temp.tex

clean:
	rm -f *.aux
	rm -f *.log
	rm -f *.out
	rm -f *.pdf
	rm -f *.synctex.gz
	rm -f *.auxlock
	rm -f *.toc
