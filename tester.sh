#!/usr/bin/bash

make fclean
mkdir -p exec
make
mv tester exec/tester_ft
make std
mv tester exec/tester_std

exec/tester_ft > exec/ft.log
exec/tester_std > exec/std.log

diff --text exec/ft.log exec/std.log

# rm -rf ft.log std.log exec