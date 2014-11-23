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

my $output = `mcgoo init hello.mak`;
chomp $output;

Mcgoo::FileExists "hello.mak";
Mcgoo::FileLineExists "hello.mak", "# .* framework";

Mcgoo::Summarize;
