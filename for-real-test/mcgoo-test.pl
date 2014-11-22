#!/usr/bin/perl

# Test for MCGOO CLI.

use strict;
use warnings;

use lib '..';
use Mcgoo;

Mcgoo::Announce;

`make clean`;
`make mcgoo`;

my $usage = `./mcgoo`;
chomp $usage;

Mcgoo::Expect $usage, qw/usage:.*/;

Mcgoo::Summarize;
