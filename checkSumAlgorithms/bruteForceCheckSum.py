import time
import os
import random

def brute_force_check_sum(arr, n, target):
    total_masks = 1 << n

    for mask in range(total_masks):
        sum = 0

        for i in range(n):
            if mask & (1 << i):
                sum += arr[i]
        
        if sum == target:
            return True
    return False

def main():
    sizes = [5, 15, 25]
    num_sizes = len(sizes)

    for idx in range(num_sizes):
        n = sizes[idx]
        arr = [random.randint(0, 99) for _ in range(n)]
        target = random.randint(0, n * 100 - 1)

        print(f"n = {n:2d} | Array: {arr}")
        print(f"target = {target}")

        start_time = time.time()
        found = brute_force_check_sum(arr, n, target)
        end_time = time.time()

        print(f"found = {int(found)} | time = {end_time - start_time:.6f} s\n")

if __name__ == "__main__":
    main()