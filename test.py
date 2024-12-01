from collections import deque


def scottish_dance(operations):
    # Initialize the circle as a deque
    circle = deque()

    for operation in operations:
        op = operation.split()
        if op[0] == "I":  # Insert operation
            x = int(op[1])  # Dancer ID
            p = int(op[2])  # Position
            if p == 0:  # Insert at the beginning
                circle.appendleft(x)
            elif p == len(circle):  # Insert at the end
                circle.append(x)
            else:  # Insert in between
                circle.insert(p, x)
        elif op[0] == "S":  # Swap operation
            i = int(op[1])
            j = int(op[2])
            circle[i], circle[j] = circle[j], circle[i]
        elif op[0] == "R":  # Rotate operation
            r = int(op[1])
            circle.rotate(r)
        elif op[0] == "F":  # Flip operation
            i = int(op[1])
            j = int(op[2])
            length = len(circle)

            if i <= j:
                # Straightforward reversal
                while i < j:
                    circle[i], circle[j] = circle[j], circle[i]
                    i += 1
                    j -= 1
            else:
                # Circular reversal when i > j
                temp = []
                idx = i
                for _ in range(length):
                    temp.append(circle[idx])
                    idx = (idx + 1) % length
                    if idx == (j + 1) % length:
                        break

                # Reverse the extracted segment
                temp.reverse()

                # Put back the reversed segment
                idx = i
                for val in temp:
                    circle[idx] = val
                    idx = (idx + 1) % length

    return list(circle)


# Input processing
if __name__ == "__main__":
    n, m = map(int, input().split())
    operations = [input().strip() for _ in range(m)]
    result = scottish_dance(operations)
    print(" ".join(map(str, result)))
