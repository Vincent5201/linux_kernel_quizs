perf stat --repeat 10 -o test1_report/mid3/100000_report \
    -e branches,cache-misses,cycles,instructions,context-switches \
    ./test1_improve

# sudo sysctl -w kernel.perf_event_paranoid=-1