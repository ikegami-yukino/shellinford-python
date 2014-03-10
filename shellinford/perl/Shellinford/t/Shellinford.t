# Before `make install' is performed this script should be runnable with
# `make test'. After `make install' it should work as `perl Shellinford.t'

#########################

# change 'tests => 1' to 'tests => last_test_to_print';

use strict;
use warnings;

use Test::More tests => 5;
BEGIN { use_ok('Shellinford') };

my @docs = ("apple", "orange", "remon", "application");
my @keys = ("app", "apple", "apply");

my $fm = Shellinford->new;
for my $doc (@docs) { $fm->push_back($doc); }
$fm->build();
is($fm->docsize(), 4, "docsize()");

my $res;
$res = $fm->search("app");   is(keys %$res, 2, "search()");
$res = $fm->search("apple"); is(keys %$res, 1, "search()");
$res = $fm->search("apply"); is(keys %$res, 0, "search()");

#########################

# Insert your test code below, the Test::More module is use()ed here so read
# its man page ( perldoc Test::More ) for help writing this test script.

