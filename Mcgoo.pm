=head1 NAME

Mcgoo - A scripted command line testing utility.

=cut

package Mcgoo;

use Time::HiRes qw(time);

my $DoUseSimplePrintout = 0;
sub UseSimplePrintout  { $DoUseSimplePrintout = 1; }
sub UseRegularPrintout { $DoUseSimplePrintout = 0; }

my $ExpectNumber = 0;

my $TestStartTime = 0;

my $TestIndex = 0;

my %TestFailureHash = ();

sub Announce
{
    my $Filename = $0;
    $Filename =~ s/\.pl$//;
    $Filename =~ s%^\./%%;

    my $TestStartMessage = "(test = $Filename) [ ";
    $TestStartMessage .= "\n" if !$DoUseSimplePrintout;

    $ExpectNumber = 0;
    $TestStartTime = time;
    $TestIndex = length $TestStartMessage;

    print $TestStartMessage;
}

sub Expect
{
    my $String1 = shift @_;
    my $String2 = shift @_;

    my $ExpectString = "($String1 =~ $String2)";

    my $ReturnValue;

    if ($String1 =~ /^$String2$/) {
        print ($DoUseSimplePrintout
               ? "."
               : "  SUCCESS ( $ExpectString ) \n");
        $ReturnValue = 0;
    } else {
        print ($DoUseSimplePrintout
               ? "X"
               : "  FAILURE ( $ExpectString )\n");
        $TestFailureHash{$TestIndex} = $ExpectString;
        $ReturnValue = 1;
    }
    $TestIndex ++;

    return $ReturnValue;
}

sub FileExists
{
  my $Filename = shift @_;
  
  my $ExpectString = "($Filename exists)";
  
  if (-f $Filename) {
    print ($DoUseSimplePrintout
           ? "."
           : "  SUCCESS ( $ExpectString ) \n");
    $ReturnValue = 0;
  } else {
    print ($DoUseSimplePrintout
           ? "X"
           : "  FAILURE ( $ExpectString )\n");
    $TestFailureHash{$TestIndex} = $ExpectString;
    $ReturnValue = 1;
  }
  $TestIndex ++;
  
}

sub Summarize
{
    my $TestTime = time - $TestStartTime;
    my $Row = 0;
    my $RowPrintedOn = 0;

    print  " " if $DoUseSimplePrintout;
    printf "] ( %0.5f s ) ", $TestTime;
    print  (%TestFailureHash ? "FAIL" : "PASS");
    print  "\n";

    if ($DoUseSimplePrintout) {
        foreach my $Key (sort keys %TestFailureHash) {
            print " " x $Key;
            for my $i ($Key .. $TestIndex) {
                print (exists $TestFailureHash{$i} ? "|" : " " );
            }
            print "\n";
            print " " x $Key;
            print "$TestFailureHash{$Key}\n";
        }
    }
}

1;
