def custom_sort(arr):
    n = len(arr)
    for i in range(n):
        # Initially, the minimum element is assumed to be at the current index
        min_idx = i
        # Iterate through the unsorted portion to find the smallest element
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        # Swap the found minimum element directly with previous elements until it reaches its correct position
        while min_idx > i:
            arr[min_idx], arr[min_idx - 1] = arr[min_idx - 1], arr[min_idx]
            min_idx -= 1
    return arr


# Example usage
initial_list = [8, 5, 7, 6, 2, 3, 1, 4]
sorted_list = custom_sort(initial_list)
print(sorted_list)
