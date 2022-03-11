#!/bin/bash
./main
gprof main | gprof2dot -s -n1 -e1 --skew=1 | dot -Tpng -o profile.png
rm gmon.out
gthumb profile.png