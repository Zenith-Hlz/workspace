#include <iostream>
#include <cstring>

using namespace std;

const int MAX_LENGTH = 50; // The maximum piece length as per problem statement

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break; // Stop input when '0' is encountered

        int lengths[MAX_LENGTH + 1] = {0}; // Array to count lengths

        // Read lengths into the counting array
        for (int i = 0; i < n; ++i)
        {
            int piece_length;
            cin >> piece_length;
            lengths[piece_length]++; // Increment count of this length
        }

        // Finding the minimum possible original length
        int min_length = MAX_LENGTH; // Start with the max possible stick length
        for (int target_length = 1; target_length <= MAX_LENGTH; ++target_length)
        {
            int total_pieces = 0;
            for (int length = 1; length <= MAX_LENGTH; ++length)
            {
                total_pieces += lengths[length]; // Total pieces of all lengths
            }

            // Check if we can form sticks of 'target_length'
            int required_sticks = total_pieces / target_length;
            if (required_sticks * target_length == total_pieces)
            {
                min_length = target_length; // Found a feasible original length
                break;                      // We stop at the smallest length
            }
        }

        // Output the minimum possible original length
        cout << min_length << endl;
    }

    return 0;
}