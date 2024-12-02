import random


def generate_input(d, n, q):
    # Generate n d-dimensional vectors
    vectors = []
    for _ in range(n):
        vector = [random.randint(-(10**7), 10**7) for _ in range(d)]
        vectors.append(vector)

    # Generate q queries
    queries = []
    for _ in range(q):
        query = [random.randint(-(10**7), 10**7) for _ in range(d)]
        queries.append(query)

    # Printing the input in the required format
    print(f"{d} {n}")

    for vector in vectors:
        print(" ".join(map(str, vector)))

    print(q)

    for query in queries:
        print(" ".join(map(str, query)))


# Dimensionality of the vectors (between 2 and 5)
d = random.randint(2, 5)
# Number of vectors (up to 100,000)
n = random.randint(1, 100000)
# Number of queries (up to 200,000)
q = random.randint(1, 200000)

generate_input(d, n, q)
