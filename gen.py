import random


def generate_input(n_max=10**5, m_max=10**5):
    """
    Generates random test input for the problem and prints it to the console.

    Args:
    - n_max: Maximum number of cards (default: 100,000 for testing purposes).
    - m_max: Maximum number of operations (default: 100,000 for testing purposes).
    """

    # Ensure n_max and m_max are within valid constraints
    n = random.randint(1, n_max)
    m = random.randint(1, m_max)

    print(f"{n} {m}")

    for _ in range(m):
        operation_type = random.choice(["H", "Q"])
        s = random.randint(1, n)
        t = random.randint(s, n)  # Ensure s ≤ t
        print(f"{operation_type} {s} {t}")


if __name__ == "__main__":
    # Generate and print sample input
    generate_input(n_max=2**31, m_max=200_000)
