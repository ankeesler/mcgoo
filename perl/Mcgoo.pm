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
    
    my $ItMatches = ($String1 =~ /^$String2$/);

    return InternalExpect($ItMatches, "$String1 =~ $String2");
}

sub FileExists
{
  my $Filename = shift @_;
  
  return InternalExpect(-f $Filename, "$Filename exists");
}

sub FileLineExists
{
  my $Filename = shift @_;
  my $FileLine = shift @_;

  my $FoundIt = 0;
  
  open FILE, $Filename or return 1;
  
  while (my $Line = <FILE>) {
    if ($Line =~ $FileLine) {
      $FoundIt = 1;
      last;
    }
  }
  
  return InternalExpect($FoundIt, "$Filename contains '$FileLine'");
}

sub NExpect
{
    my $String1 = shift @_;
    my $String2 = shift @_;
    
    my $ItMatches = ($String1 !~ /^$String2$/);

    return InternalExpect($ItMatches, "$String1 !~ $String2");    
}

sub InternalExpect
{
  my $Thing = shift @_;
  my $ExpectString = shift @_;
  
  my $ExpectString = "{ $ExpectString }";
  my $CurrentTime = sprintf "%0.5f", time - $TestStartTime;
  my $ReturnValue;
  
  if ($Thing) {
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

sub Summarize
{
    my $TestTime = time - $TestStartTime;
    my $Row = 0;
    my $RowPrintedOn = 0;
    my $WasFailure = (%TestFailureHash ? 1 : 0);

    print  " " if $DoUseSimplePrintout;
    printf "] ( %0.5f s ) ", $TestTime;
    print  ($WasFailure ? "FAIL" : "PASS");
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

    return $WasFailure;
}

1;
