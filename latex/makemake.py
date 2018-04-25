import glob, os, sys

if (len(sys.argv) < 2):
	print('Error: Usage {} [folder]'.format(sys.argv[0]))
	sys.exit(-1)

path = os.path.join(os.getcwd(), sys.argv[1])

alls = 'all:'
rest = ''

for f in glob.glob(os.path.join(path, '*.tex')):
	fname = os.path.splitext(os.path.basename(f))[0]
	if ('preamble' not in fname):
		alls += ' ' + fname + '.pdf'
		rest += fname + '.pdf: ' + fname + '.tex\n\tpdflatex ' + fname + '.tex\n\n'

with open(os.path.join(path, 'Makefile'), 'w') as f:
	f.write(alls + '\n\n')
	f.write(rest)
	f.write('clean:\n\trm -f *.aux\n\trm -f *.log\n\trm -f *.out\n\trm -f *.pdf\n\trm -f *.synctex.gz\n\trm -f *.auxlock\n\trm -f *.toc')
	f.close()
