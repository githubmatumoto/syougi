#!/bin/perl
#
# 枠を手抜きして取る。
# perl ../conv_line.pl < kawazu-exec2.txt | sort | uniq
#
$in = 1;
while(<STDIN>)
{
    if(/^\|/){
	s/\|\n$//;
	#s/^\+.*\+$/|/;
	print;
	$in  = 0;
	next;
    }

    next if($in == 1);
    print "|\n";
    $in  =1;
}
