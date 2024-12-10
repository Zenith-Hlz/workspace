#include <iostream>
#include <cstdlib>
#include <cassert>

const int MAX_MELODY = 1500001;
const int MAX_ALBUM = 1000001;

int length, numOperations, operation, numNotes;

// The struct that stores the melody
struct Melody
{
    int melody;                     // The melody
    int prefixSuffix;               // The longest prefix of the melody that is also a suffix
    int nonOverlappingPrefixSuffix; // The longest prefix of the melody that is also a suffix with no overlap
} melody[MAX_MELODY];

int album[MAX_ALBUM];

// The function that calculates the prefix suffix of the melody
void getPrefixSuffix(int index)
{
    int pre = melody[index].prefixSuffix;

    // If the next note of the previous prefixsuffix is the same as the current note, adjust the prefix index
    while (melody[pre].melody != melody[index].melody && pre > 0)
        pre = melody[pre].prefixSuffix;
    if (melody[pre].melody == melody[index].melody)
        melody[index + 1].prefixSuffix = pre + 1;
}

// The function that calculates the non-overlapping prefix suffix of the melody
void getNonOverlappingPrefixSuffix(int index)
{
    int pre = melody[index].nonOverlappingPrefixSuffix;
    // Adjust the prefix index if it reaches half of the current index
    if (pre == (index + 1) / 2)
        pre = melody[pre].prefixSuffix;

    // If the next note of the previous prefixsuffix is the same as the current note, adjust the prefix index
    while (melody[pre].melody != melody[index].melody && pre > 0)
        pre = melody[pre].nonOverlappingPrefixSuffix;
    if (melody[pre].melody == melody[index].melody)
        melody[index + 1].nonOverlappingPrefixSuffix = pre + 1;
}

// The function that updates the prefix and suffix of the melody from left to right
void updatePrefixSuffix(int left, int right)
{
    for (int i = left; i < right; i++)
    {
        getPrefixSuffix(i);
        getNonOverlappingPrefixSuffix(i);
    }
}

// The function that finds the common prefix suffix of two melodies
int commonPrefixSuffix(int x, int y)
{
    while (x != y)
    {
        if (x < y)
            std::swap(x, y);
        x = (x >= 2 * y) ? melody[x].nonOverlappingPrefixSuffix : melody[x].prefixSuffix;
    }

    return x;
}

// The function that calculates the result, which traverses the album and finds the common prefix suffix of the melodies
int calculateResult()
{
    int result = melody[album[0]].nonOverlappingPrefixSuffix;
    for (int j = 1; j < numNotes; j++)
    {
        result = commonPrefixSuffix(result, melody[album[j]].nonOverlappingPrefixSuffix);
        if (result == 0)
            break;
    }

    return result;
}

int main()
{
    scanf("%d %d", &length, &numOperations);
    for (int i = 0; i < length; i++)
        scanf("%d", &melody[i].melody);

    // Calculate the prefix and suffix of the melody
    updatePrefixSuffix(1, length);

    for (int i = 0; i < numOperations; i++)
    {
        scanf("%d %d", &operation, &numNotes);

        if (operation == 1)
        {
            for (int j = 0; j < numNotes; j++)
                scanf("%d", &melody[length + j].melody);

            // Calculate the prefix and suffix of the new melody
            updatePrefixSuffix(length, length + numNotes);
            length += numNotes;
        }
        else if (operation == 2)
        {
            for (int j = 0; j < numNotes; j++)
                scanf("%d", album + j);

            qsort(album, numNotes, sizeof(int), [](const void *a, const void *b)
                  { return *(int *)a - *(int *)b; });

            printf("%d\n", calculateResult());
        }
    }

    return 0;
}