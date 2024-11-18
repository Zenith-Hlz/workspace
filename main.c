#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 64

int main()
{
    int n;
    int l[MAX_LENGTH];
    int u[MAX_LENGTH];

    while (1)
    {
        // Read the number of parts
        scanf("%d", &n);
        if (n == 0)
            break; // Exit if the input is 0

        int total_length = 0;

        // Read the lengths of the parts
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &l[i]);
            total_length += l[i]; // Accumulate total length
            u[i] = 0;             // Initialize usage array
        }

        // Try every possible length from the minimum to the total length
        for (int possible_length = l[0]; possible_length <= total_length; possible_length++)
        {
            // Check if total length can be divided equally into sticks of this length
            if (total_length % possible_length == 0)
            {
                int current_length = 0;
                int remaining_sticks = n;
                int start_index = 0;
                int is_possible = 1; // Flag to check if we can group pieces into sticks

                // Attempt to group pieces into sticks of 'possible_length'
                for (int j = 0; j < n; j++)
                {
                    int i;
                    for (i = start_index; i < n; i++)
                    {
                        // If we can add the piece to the current stick without exceeding the length
                        if (u[i] == 0 && current_length + l[i] <= possible_length)
                        {
                            u[i] = 1;               // Mark the piece as used
                            current_length += l[i]; // Add length to current stick

                            // Check if the stick is complete
                            if (current_length == possible_length)
                            {
                                current_length = 0; // Reset for the next stick
                                start_index = 0;    // Start searching from the beginning for the next stick
                                remaining_sticks--; // One less stick to form
                                break;              // Move to the next stick formation
                            }
                            start_index = i + 1; // Continue search from the next index
                        }
                    }
                    // If we exhausted pieces and didn't complete a stick
                    if (i == n)
                    {
                        is_possible = 0; // Mark as not possible to form all sticks
                        break;
                    }
                }

                // If it's possible to form all sticks
                if (is_possible && remaining_sticks == 0)
                {
                    printf("%d\n", possible_length); // Output the valid stick length
                    break;                           // Break from the current length trial
                }

                // Reset usage array for next trial
                for (int k = 0; k < n; k++)
                {
                    u[k] = 0;
                }
            }
        }
    }
    return 0;
}