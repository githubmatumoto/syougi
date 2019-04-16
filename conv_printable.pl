#!/bin/perl

$count = 0;
$in = -1;
$get_masu = "";
while(<STDIN>){
    if($in == -1){
	$in = 0 if(/^%%FOUND/);
	next;
    } 

    if($in >= 0){
	if(/^%%$/){

	    $count++;
	    print "No = ", $count, "\n";
	    print $get_masu;
	    $get_masu = "";

	    $in = -1;
	} else {
	    $l  = $_ ;
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
