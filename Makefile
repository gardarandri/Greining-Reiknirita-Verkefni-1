


compile:
	gcc -o gas_sort gas_qsort.c
	gcc -o qsort_test gas_qsort.c -DUSE_QSORT

data: compile
	gas_sort 100 PIV_DEFAULT -p -d > default.csv
	gas_sort 100 PIV_LINEAR -p -d > linear.csv
	gas_sort 100 PIV_QUADRATIC -p -d > quadratic.csv
	gas_sort 100 PIV_TRICK_1 -p -d > trick1.csv
	gas_sort 100 PIV_TRICK_2 -p -d > trick2.csv

alpha: compile
	gas_sort 10000 PIV_ALPHA -p > alpha.csv

linquad: compile
	gas_sort 10 PIV_LINEAR
	gas_sort 30 PIV_LINEAR
	gas_sort 100 PIV_LINEAR
	gas_sort 300 PIV_LINEAR
	gas_sort 1000 PIV_LINEAR
	gas_sort 3000 PIV_LINEAR
	gas_sort 10000 PIV_LINEAR
	gas_sort 10 PIV_QUADRATIC
	gas_sort 30 PIV_QUADRATIC
	gas_sort 100 PIV_QUADRATIC
	gas_sort 300 PIV_QUADRATIC
	gas_sort 1000 PIV_QUADRATIC
	gas_sort 3000 PIV_QUADRATIC
	gas_sort 10000 PIV_QUADRATIC


info: compile
	gas_sort 100 PIV_DEFAULT 
	gas_sort 100 PIV_LINEAR
	gas_sort 100 PIV_QUADRATIC
	gas_sort 100 PIV_TRICK_1
	gas_sort 100 PIV_TRICK_2
	gas_sort 100 PIV_RANDOM
