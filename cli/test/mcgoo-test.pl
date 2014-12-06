#!/usr/bin/perl

# Test for MCGOO CLI.

use strict;
use warnings;

use Mcgoo;

Mcgoo::Announce;

my $usage = `mcgoo`;
chomp $usage;

Mcgoo::Expect $usage, qw/usage:.*/;

my $output = `mcgoo init`;
chomp $output;

Mcgoo::FileExists "Mcgoo.mak";
Mcgoo::FileLineExists "Mcgoo.mak", "# .* framework";

$output = `mcgoo add`;
chomp $output;
Mcgoo::Expect $output, "Error: cannot add test: [0-9]+";

$output = `mcgoo add hello-test`;
chomp $output;
Mcgoo::FileLineExists "Mcgoo.mak", "HELLO-TEST";

Mcgoo::Summarize;
