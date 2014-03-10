#!/usr/bin/env perl -Iblib/lib -Iblib/arch
use strict;
use warnings;
use Shellinford;

my $filename = shift @ARGV;
my $fm = Shellinford->new();
$fm->read($filename) or die "ERROR($!): $filename cannot open.\n";
while (my $key = <>) {
  chomp($key);
  my $result = $fm->search($key);
  my @dids   = keys %$result;
  my $hits   = scalar(@dids);

  print "$hits hits.\n";
  for my $did (@dids) {
    my $doc = $fm->get_document($did);
    print "[$did]: $doc($result->{$did})\n";
  }
  print "\n";
}

