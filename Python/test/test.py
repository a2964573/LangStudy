from itertools import product

candidates = [1, 4, 5, 32, 33, 36, 37, 128, 129, 132, 133, 160, 161, 164, 165]
target = 908

valid_combinations = set()

for length in range(1, 7):
    for combo in product(candidates, repeat=length):
        if sum(combo) == target:
            valid_combinations.add(tuple(sorted(combo)))

sorted_combos = sorted(valid_combinations, key=lambda x: (len(x), x))
sorted_combos[:10], len(sorted_combos)

print(sorted_combos)

