all: project3

project3: Q1-1_brute_force_knapsack.out Q1-2_greedy_algorithm.out Q1-3_dynamic_programming_knapsack.out

Q1-1_brute_force_knapsack.out: Q1-1_brute_force_knapsack.c
	gcc -g Q1-1_brute_force_knapsack.c -o Q1-1_brute_force_knapsack.out -lm

Q1-2_greedy_algorithm.out: Q1-2_greedy_algorithm.c
	gcc -g Q1-2_greedy_algorithm.c -o Q1-2_greedy_algorithm.out

Q1-3_dynamic_programming_knapsack.out: Q1-3_dynamic_programming_knapsack.c
	gcc -g Q1-3_dynamic_programming_knapsack.c -o Q1-3_dynamic_programming_knapsack.out

clean:
	find . -type f -name "*.o" -delete
	find . -type f -executable -delete
