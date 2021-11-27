use strict;
use warnings;

use File::Find;

my %records;

find sub { process_file() if -f $_ }, "./testdata/";

for (keys %records) {
    print("$_ $records{$_}\n");
}

exit;

sub process_file {
    open(my $f, "<", $_) or die $!;
    while (<$f>) {
        for (split /\s+/, $_) {
            $records{$_}++;
        }
    }
}
