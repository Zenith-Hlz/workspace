#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate and print a random input
void generateInput(int n, int m)
{
    // Generate initial sequence of notes
    cout << n << " " << m << endl; // First line: n and m
    for (int i = 0; i < n; i++)
    {
        cout << 1 << " "; // Random note value [0, 10^9]
    }
    cout << endl;

    // Generate m operations
    for (int i = 0; i < m; i++)
    {
        int operationType = (rand() % 2) + 1; // Randomly choose 1 or 2
        int q = rand() % (1000) + 1;          // Random number of notes to add or check (1 to 1000)

        if (operationType == 1)
        {                                      // Create operation
            cout << operationType << " " << q; // Operation type and q
            for (int j = 0; j < q; j++)
            {
                cout << " " << 1; // Random non-negative note values
            }
            cout << endl;
        }
        else
        {                                      // Test album operation
            cout << operationType << " " << q; // Operation type and q
            for (int j = 0; j < q; j++)
            {
                // Pick a random length that does not exceed the current melody length
                cout << " " << (rand() % (n + i * 1000) + 1); // Ensure it doesn't exceed current length
            }
            cout << endl;
        }
    }
}

int main()
{
    // Seed the random number generator
    srand(time(0));

    int n = rand() % 5000 + 1; // Generate n in range [1, 500000]
    int m = rand() % 5000 + 1; // Generate m in range [1, 500000]

    generateInput(n, m);
    return 0;
}
