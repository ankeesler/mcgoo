#!/usr/bin/perl

# Test for MCGOO CLI.

use strict;
use warnings;

use lib '../..';
use Mcgoo;

my $EXEC = "./build/mcgoo";

Mcgoo::Announce;

`make clean`;
`make compile`;

my $usage = `$EXEC`;
chomp $usage;

Mcgoo::Expect $usage, qw/usage:.*/;

my $output = `$EXEC init`;
chomp $output;

Mcgoo::FileExists "Mcgoo.mak";
Mcgoo::FileLineExists "Mcgoo.mak", "# .* framework";

Mcgoo::Summarize;
