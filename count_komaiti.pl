#!/bin/perl

use Encode;




$count = 0;
$in = -1;
$get_masu = "";

$init =0;
@count_list=();

while(<STDIN>){
    if($in == -1){
	$in = 0 if(/^%%FOUND/);
	next;
    } 

    if($in >= 0){
	if(/^%%$/){

	    $count++;
	    #print "No = ", $count, "\n";
	    #print $get_masu;

	    if(0){
		$get_masu =~ s/\r//g;
		$get_masu =~ s/\n//g;
		$get_masu =~ s/\-//g;
		$get_masu =~ s/\|//g;
		$get_masu =~ s/\+//g;
	    }

	    utf8::decode($get_masu);
	    @list = split(//, $get_masu);
	    $get_masu = "";

	    for $i (0 .. $#list){
		$t = $list[$i];
		utf8::encode($t);
		$list[$i] = $t;
	    }
	    #exit;

	    if($init == 0) {
		@count_list = @list;
		$init = 1;
	    }else {
		for $i (0 .. $#list){
		    #print "DEBUG=",$list[$i], "\n";
		    if($list[$i] ne $count_list[$i]){
			$count_list[$i] = "△";
		    }
		}
	    }

	    $in = -1;
	} else {
	    $l  = $_ ;
	    #$l =~ s/□/■/g;
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

print "位置が変わらない駒\n";
print "△ : 駒の変化があるマス\n";

for $i (0 .. $#count_list){
    print $count_list[$i];
}
print "\n";

