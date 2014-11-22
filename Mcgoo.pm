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

    my $ExpectString = "{ $String1 =~ $String2 }";
    my $CurrentTime = sprintf "%0.5f", time - $TestStartTime;
    my $ReturnValue;

    if ($String1 =~ /^$String2$/) {
        print ($DoUseSimplePrintout
               ? "."
               : "  ( $CurrentTime s ) SUCCESS $ExpectString\n");
        $ReturnValue = 0;
    } else {
        print ($DoUseSimplePrintout
               ? "X"
               : "  ( $CurrentTime s )  * FAILURE $ExpectString\n");
        $TestFailureHash{$TestIndex} = $ExpectString;
        $ReturnValue = 1;
    }
    $TestIndex ++;

    return $ReturnValue;
}

sub FileExists
{
  my $Filename = shift @_;
  
  my $ExpectString = "{ $Filename exists }";
  my $CurrentTime = sprintf "%0.5f", time - $TestStartTime;
  my $ReturnValue;
  
  if (-f $Filename) {
    print ($DoUseSimplePrintout
           ? "."
           : "  ( $CurrentTime s ) SUCCESS $ExpectString\n");
    $ReturnValue = 0;
  } else {
    print ($DoUseSimplePrintout
           ? "X"
           : "  ( $CurrentTime s )  * FAILURE ( $ExpectString )\n");
    $TestFailureHash{$TestIndex} = $ExpectString;
    $ReturnValue = 1;
  }
  $TestIndex ++;
  
  return $ReturnValue;
}

sub FileLineExists
{
  my $Filename = shift @_;
  my $FileLine = shift @_;
  
  my $ExpectString = "{ $Filename contains '$FileLine' }";
  my $CurrentTime = sprintf "%0.5f", time - $TestStartTime;
  my $ReturnValue = 1;
  
  open FILE, $Filename or return $ReturnValue;
  
  while (my $Line = <FILE>) {
    if ($Line =~ $FileLine) {
      $ReturnValue = 0;
      last;
    }
  }
  
  if ($ReturnValue == 0) {
    print ($DoUseSimplePrintout
           ? "."
           : "  ( $CurrentTime s ) SUCCESS $ExpectString\n");
  } else {
    print ($DoUseSimplePrintout
           ? "X"
           : "  ( $CurrentTime s )  * FAILURE ( $ExpectString )\n");
    $TestFailureHash{$TestIndex} = $ExpectString;
  }
  $TestIndex ++;
  
  return $ReturnValue;
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
