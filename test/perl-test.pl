#!/usr/bin/perl

use strict;
use warnings;

use lib '..';
use Mcgoo;

Mcgoo::Announce;

# Basic checks.
Mcgoo::Expect "andrew", "andrew";
Mcgoo::Expect 1, 1;

# Wrong number.
Mcgoo::Expect 1, 3;

# Regex checks.
Mcgoo::Expect "andrew", qw/\w+/;
Mcgoo::Expect "andrew", qw/.*/;
Mcgoo::Expect "andrew5andrew", qw/.*\d[a-z]+/;

# Wrong string.
Mcgoo::Expect "andrew", "marshmallow";

# File exists
Mcgoo::FileExists "perl-test.pl";
Mcgoo::FileExists "../Mcgoo.pm";

# File does not exist.
Mcgoo::FileExists "Andrew.andrew";

# File line exists.
Mcgoo::FileLineExists "perl-test.pl", "# Basic checks.";
Mcgoo::FileLineExists "perl-test.pl", qw/File \w+/;

# File line does not exist.
Mcgoo::FileLineExists "../Mcgoo.pm", "asljkndflakjnsdlfkjansldkfjn";

Mcgoo::Summarize;
