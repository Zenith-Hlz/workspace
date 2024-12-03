#include "hashtable.h"

int naive_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;
    else
        return (str[0] + N) % N;
}

int bad_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;

    unsigned long hash = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        hash += (str[i] * (i + 1));
    return hash % N;
}

// Refer to https://theartincode.stanis.me/008-djb2/ djb2 hash
int good_hashing::operator()(char *str, int N)
{
    if (str == NULL)
        return 0;

    unsigned long hash = 5381;
    for (int i = 0; str[i] != '\0'; ++i)
        hash = ((hash << 5) + hash) + str[i];
    return hash % N;
}

int linear_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
    return (last_choice + 1) % table_size;
}

void linear_probe::init()
{
    return; // do nothing
}

int bidirectional_quadratic_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
    step++; // Increment step for the next probe

    int direction = (step % 2 == 0) ? 1 : -1;                     // Alternate directions
    int offset = direction * ((step + 1) / 2) * ((step + 1) / 2); // Quadratic probing

    return (last_choice + offset + table_size) % table_size;
}

void bidirectional_quadratic_probe::init()
{
    step = 0; // Reset step for a new probing sequence
}

int common_overflow_area::operator()(hash_entry *Table, int table_size, int last_choice)
{
    for (int i = 0; i < overflow_size; ++i)
    {
        int index = (overflow_start + i) % table_size;
        if (Table[index].my_string == NULL)
            return index;
    }
    return -1;
}

void common_overflow_area::init()
{
    return;
}