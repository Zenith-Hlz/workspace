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


# Test and benchmarking  
def test_and_benchmark():  
    for n in [100, 1000, 10000, 100000]:  
        arr = np.random.randint(1 << 30, size=n).tolist()  

        # Validate correctness  
        sorted_arr = sorted(arr)  
        assert insertion_sort(arr.copy()) == sorted_arr, "Insertion sort failed"  
        assert merge_sort(arr.copy()) == sorted_arr, "Merge sort failed"  

        print(f"Array size: {n}\n")  
        
        # Performance measurement  
        print("Insertion Sort Time:")  
        %timeit insertion_sort(arr.copy())  
        
        print("Merge Sort Time:")  
        %timeit merge_sort(arr.copy())  
        
        print("Python's Built-in Sort Time:")  
        %timeit sorted(arr)  
        
        print("\n")
        
# Run the test and benchmarking  
test_and_benchmark()  