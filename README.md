# median-performance-comparison
Performance comparison of different median search algorithms of random numbers (Xorshift algorithm).

Test protocol:
1. Generate random numbers
2. nth-Element Median
3. Quicksort Random-Pivot Median
4. Randomized Select Median
5. Median of Medians

Algorithm              |    Average Running Time [s] for n=2*10^6
-----------------------|-----------------------------------------
nth-Element            |    0.025
Quicksort              |    0.288
Randomized-Select      |    0.023
Median of Medians      |    0.376