import numpy as np
import time


def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr


def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]

        merge_sort(left_half)
        merge_sort(right_half)

        i = j = k = 0
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1

        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1

    return arr


def test_sorts(n):
    arr = np.random.randint(1 << 30, size=n).tolist()
    sorted_arr = sorted(arr)

    # Insertion Sort
    arr_copy = arr.copy()
    start_time = time.time()
    insertion_sorted = insertion_sort(arr_copy)
    insertion_time = time.time() - start_time

    # Merge Sort
    arr_copy = arr.copy()
    start_time = time.time()
    merge_sorted = merge_sort(arr_copy)
    merge_time = time.time() - start_time

    # Python's built-in sorted function
    start_time = time.time()
    builtin_sorted = sorted(arr)
    builtin_time = time.time() - start_time

    assert insertion_sorted == sorted_arr, "Insertion sort failed"
    assert merge_sorted == sorted_arr, "Merge sort failed"
    assert builtin_sorted == sorted_arr, "Built-in sort failed"

    print(f"Array size: {n}")
    print(f"Insertion Sort Time: {insertion_time:.6f} seconds")
    print(f"Merge Sort Time: {merge_time:.6f} seconds")
    print(f"Built-in Sort Time: {builtin_time:.6f} seconds")
    print("-" * 50)


for size in [100, 1000, 10000, 100000]:
    test_sorts(size)
