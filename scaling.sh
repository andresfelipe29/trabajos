#!/bin/bash
mpic++ mpi-integral.cpp

Nproc=(1 2 4 5 8)
allRuntimes=()
for nproc in ${Nproc[@]}; do
    runtime=$(mpirun -np $nproc --oversubscribe ./a.out | tail -n 1)
    allRuntimes+=( $runtime )
done
t1=${allRuntimes[0]}
speedups=()
for time in ${allRuntimes[@]}; do
    speedup=`awk -v y1=$t1 -v y2=$time 'BEGIN {print y1/y2}'`
    speedups+=( $speedup )
done
eficiencias=()
for i in ${!Nproc[@]}; do
    eficiencia=`awk -v y1=${speedups[$i]} -v y2=${Nproc[$i]} 'BEGIN {print y1/y2}'`
    eficiencias+=( $eficiencia )
done
for val in ${!Nproc[@]}; do
    echo "${Nproc[$val]} ${allRuntimes[$val]} ${speedups[$val]} ${eficiencias[$val]}"
done > scaling.txt

gnuplot plot_scaling.gp
