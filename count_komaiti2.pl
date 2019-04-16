#!/bin/perl

# 飛車と角の位置が変わったらプリントする。

use Encode;

$in = -1;
$get_masu = "";
$count = 0;
$init =0;
@count_list=();

@OO_GOMA=("飛", "角");

while(<STDIN>){
    if($in == -1){
	$in = 0 if(/^%%FOUND/);
	next;
    } 

    unless(/^%%$/){
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
	next;
    }

    $in = -1;
    $count++;
	
    utf8::decode($get_masu);
    @list = split(//, $get_masu);
    $get_masu = "";

    for $i (0 .. $#list){
	$t = $list[$i];
	utf8::encode($t);
	$list[$i] = $t;
    }

    if($init == 0) {
	@count_list = @list;
	$init = 1;
	next;
    }

    @save_count_list=@count_list;
    $oogoma_change=0;

    for $i (0 .. $#list){
	#print "DEBUG=",$list[$i], "\n";
	if($list[$i] ne $count_list[$i]){
	    $count_list[$i] = "△";
	    for $j (0 .. $#OO_GOMA) {
		$oogoma_change=1 if($OO_GOMA[$j] eq $list[$i]);
	    }
	}
    }

    #print "DEBUG=", $count, "\n";

    if($oogoma_change==1){
	&print_last($count-1, @save_count_list);

	@count_list = @list;
	$count = 1;
    }
}

&print_last($count, @count_list);

sub print_last
{
    local($co, @c) = @_;
    print "Total = ", $co, "\n";
    print "位置が変わらない駒\n";
    print "△ : 駒の変化があるマス\n";

    for $i (0 .. $#c){
	print $c[$i];
    }
    print "\n";
};
