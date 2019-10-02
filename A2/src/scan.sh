#/usr/sh

find . -type f -name "*.$1" -printf '%p %s\n' | sort -t" " -k 2 -n -r | head -$2 | awk '{ x += $2 ; print $1 " " $2} END { print "Total Size: " x }'