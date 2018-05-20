import argparse
import re

def stripFirst(s):
    while (s.startswith(' ') or s.startswith('\t')):
        s = s[1:]
    return s

def isEmpty(s):
    for c in s:
        if (c != ' ' and c != '\t'):
            return False
    return True

def getCommand(s):
    m = re.match(r'\\(.+?)[\[\{]', s)
    if (m):
        return m[1]
    return s[1:]


def indentLine(f, times):
    ctr = 0 
    for i in range(times):
        if (USE_TABS):
            f.write('\t')
            ctr += 4
            # TODO not hardcode this value
        else:
            for i in range(TAB_SIZE):
                f.write(' ')
                ctr += TAB_SIZE
    return ctr

##################

parser = argparse.ArgumentParser(
        description='Reindent and prettify latex file')

parser.add_argument('input_file', metavar='/path/to/file', 
        nargs='?', help='input file')
parser.add_argument('-o', '--output', help='Optional file for' +
        'output.\nIf empty, the input one will be used.')
parser.add_argument('-m', '--max-line-width', 
        help='Specifies max line length. Default: 80')
parser.add_argument('-t', '--use-tabs', action='store_true',
        help='The prgram will use tabs to indent'
        + '(instead of spaces).')
parser.add_argument('-s', '--tab-size', type=int,
        help='Sets the tab width. Ignored if -t is present. '
        + 'Default=4')

tmp = parser.parse_args()

if (not tmp.input_file):
    parser.print_help()
    exit(1)

input_path = tmp.input_file
output_path = (tmp.output if tmp.output else input_path)
MAX_LINE = (tmp.max_line_width if tmp.max_line_width else 80)
USE_TABS = tmp.use_tabs
TAB_SIZE = (tmp.tab_size if tmp.tab_size else 4)


parrafos = []

with open(input_path, 'r') as f:
    data = f.read()

lines = data.split('\n')

parc = 0
changep = True

for line in lines:
    line = stripFirst(line)
    if (not isEmpty(line)):
        changep = True
        if (len(parrafos) == parc):
            parrafos.append(line.split(' '))
        else:
            parrafos[parc] += line.split(' ')
    else:
        if (changep):
            parc += 1
        changep = False
        
# ================
# =  OUTPUT PART =
# ================

counter = 0
indent = 0
forceBefore = False
forceAfter = False
postindent = 0

with open(output_path, 'w') as f:
    for par in parrafos:
        for w in par:


            if (w.startswith('\\')):
                # ITS A COMMAND
                cmd = getCommand(w)
                if (cmd == 'begin'):
                    forceBefore = True
                    forceAfter = True
                    postindent = 1 
                elif (cmd == 'end'):
                    forceBefore = True
                    forceAfter = True
                    indent -= 1
                elif (cmd == 'usepackage'):
                    forceBefore = True
                    forceAfter = True
                elif (cmd == '['):
                    forceBefore = True
                    forceAfter = True
                    postindent = 1
                elif (cmd == ']'):
                    forceBefore = True
                    forceAfter = True
                    indent -= 1
                else:
                    print(cmd)
                # TODO 
                # elif (cmd == 'item'):

                    

            if (counter + len(w) > MAX_LINE or forceBefore):
                f.write('\n')
                counter = indentLine(f, indent)
            
            f.write(w)
            counter += len(w)
            indent += postindent

            if (forceAfter or counter + 3 > MAX_LINE):
                f.write('\n')
                counter = indentLine(f, indent)
            else:
                f.write(' ')
                counter += 1


            forceBefore = False
            forceAfter = False
            postindent = 0

        
        f.write('\n\n')
        counter = indentLine(f, indent)
