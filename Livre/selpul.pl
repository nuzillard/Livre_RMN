#!/usr/bin/perl

# usage : selpul.pl 
#	[angle de nutation en deg.]
#	[x|y|z]
#	[offset minimim en multiples de omega1]
#	[offset maximum en multiples de omega1]
#	[nombre d'offsets

my $pi = 3.1415926535 ;

my($a0, $axis, $vmin, $vmax, $nv) ;

$a0 = (defined($ARGV[0])) ? $ARGV[0] : 1 ; $a0 *= $pi/180 ;
$axis = (defined($ARGV[1])) ? $ARGV[1] : "z" ;
$vmin = (defined($ARGV[2])) ? $ARGV[2] : -5 ;
$vmax = (defined($ARGV[3])) ? $ARGV[3] : 5 ;
$nv = (defined($ARGV[4])) ? $ARGV[4] : 100 ;
$scalex = (defined($ARGV[5])) ? $ARGV[5] : 1 ;
$scaley = (defined($ARGV[6])) ? $ARGV[6] : 1 ;

print STDERR $a0, " ", $axis, " ", $vmin, " ", $vmax, " ", $nv, "\n"  ;

my $dv = ($vmax - $vmin)/$nv ;
my $v = $vmin ;
for(my $i=0 ; $i <= $nv ; $i++) {
	printf("%.4f %.4f\n", $v*$scalex, f($v, $a0, $axis)*$scaley) ;
	$v += $dv ;
}

sub f {
	my $v = shift ;
	my $a0 = shift ;
	my $axis = shift ;
	
	my $z = $v * $v ;
	my $x = 1 + $z ;
	my $y = sqrt($x) ;
	my $a = $a0 * $y ;
	
	if($axis eq "x") {
		return sin($a)/$y ;
	} elsif($axis eq "y") {
		return $v * (1 - cos($a)) / $x ;
	} elsif($axis eq "z") {
		return (cos($a) + $z) / $x ;
	} else {
		return undef ;
	}
}
