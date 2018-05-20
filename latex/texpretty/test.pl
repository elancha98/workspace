
open(MYINPUTFILE, '<', "test.tex"); # open for input

my(@lines) = <MYINPUTFILE>; # read file into list
#@lines = sort(@lines); # sort the list

my($line);

#print "hola\n @lines";

@test = ((1, 2), (3, 4), (5, 6));

print "test: @test[0]";

foreach $line (@lines) # loop thru list
 {
 print "$line"; # print in sort order
 }
close(MYINPUTFILE);
