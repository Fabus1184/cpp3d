#!/bin/bash
set -e
./cpp3d
gprof cpp3d | gprof2dot -s -n1 -e1 --skew=1 | dot -Tpng -o profile.png
rm gmon.out
gthumb profile.png
