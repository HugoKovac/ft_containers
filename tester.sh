#!/bin/bash
#!/usr/bin/bash

make fclean
mkdir -p exec
make -j
mv tester exec/tester_ft
make -j std
mv tester exec/tester_std

start_time=`date +%s%N`

./exec/tester_ft > exec/ft.log

end_time=`date +%s%N`
echo Exectue time of FT :  `expr $end_time - $start_time`


start_time=`date +%s%N`

./exec/tester_std > exec/std.log

end_time=`date +%s%N`
echo Exectue time of STL :  `expr $end_time - $start_time`

diff --text exec/ft.log exec/std.log

# rm -rf ft.log std.log exec