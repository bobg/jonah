# Find target within the input list using recursive binary search.
# Return the index of the target if found, -1 otherwise.
def recursive_binary_search(inp, target):
    return recursive_binary_search_helper(inp, target, 0, len(inp))

def recursive_binary_search_helper(inp, target, low, high):
    if low >= high:
        return -1

    mid = (low + high) // 2

    if inp[mid] == target:
        return mid

    if inp[mid] < target:
        return recursive_binary_search_helper(inp, target, mid + 1, high)

    return recursive_binary_search_helper(inp, target, low, mid)

# Find target within the input list using iterative binary search.
# Return the index of the target if found, -1 otherwise.
def iterative_binary_search(inp, target):
    low = 0
    high = len(inp)

    while low < high:
        mid = (low + high) // 2

        if inp[mid] == target:
            return mid

        if inp[mid] < target:
            low = mid + 1
        else:
            high = mid

    return -1
