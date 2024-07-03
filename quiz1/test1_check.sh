perf stat --repeat 100 -o test1_report/original/100000_report \
    -e branches,cache-misses,cycles,instructions,context-switches \
    ./test1

# sudo sysctl -w kernel.perf_event_paranoid=-1