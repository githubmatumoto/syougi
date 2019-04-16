#!/bin/perl

#多倍長整数
use bigint;

$count = 0;
$in = -1;
$total = -1;
$ttotal = 0;
$get_masu = "";
while(<STDIN>){
    if($in == -1){
	if(/^%%UNIQ/){
	    $in = 0;
	    $l = $_;
	    chomp $l;
	    $l =~ /(\d+)$/;
	    $total = $1;

	    $ttotal += $total;

	}
	next;
    } 

    if($in >= 0){
	if(/^%%$/){

	    $count++;
	    print "No = ", $count, "\n";
	    print "Total = " . $total. "\n";
	    print "△ : 駒の変化があるマス\n";
	    print $get_masu;
	    print "\n";

	    $get_masu = "";
	    $total = -1;

	    $in = -1;
	} else {
	    $l  = $_ ;
	    $l =~ s/□/■/g;
	    $l =~ s/ 1/■/g;
	    $l =~ s/ 2/■/g;
	    $l =~ s/ 3/■/g;
	    $l =~ s/ 4/■/g;
	    $l =~ s/ 5/■/g;
	    $l =~ s/ 6/■/g;
	    $l =~ s/ 7/■/g;
	    $l =~ s/ 8/■/g;
	    $l =~ s/ 9/■/g;
	    $l =~ s/10/■/g;
	    $get_masu .= $l;
	}
    }
}


print "KUMIAWASE = " . $ttotal. "\n";
