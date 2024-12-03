#include <cstring>
#include <cstdio>

const int TABLE_SIZE = 499883; // = 124970 * 4 + 3

// Structure for a hash entry
struct hash_entry
{
    char *my_string;
    int my_data;

    hash_entry()
    {
        my_string = NULL;
        my_data = 0;
    }

    hash_entry(char *str, int data) : my_data(data)
    {
        my_string = new char[strlen(str) + 1];
        strcpy(my_string, str);
    }
};

// Abstract class for hashing strategy
struct hashing_strategy
{
    virtual int operator()(char *str, int N) = 0;
};

// Naive hashing strategy
struct naive_hashing : public hashing_strategy
{
    int operator()(char *str, int N) override;
};

// Bad hashing strategy
struct bad_hashing : public hashing_strategy
{
    int operator()(char *str, int N) override;
};

// Good hashing strategy
struct good_hashing : public hashing_strategy
{
    int operator()(char *str, int N) override;
};

// Abstract class for collision strategy
struct collision_strategy
{
    virtual void init() = 0; // pure virtual function
    virtual int operator()(hash_entry *Table, int table_size, int last_choice) = 0;
};

// Linear probing collision strategy
struct linear_probe : public collision_strategy
{
    void init();
    int operator()(hash_entry *Table, int table_size, int last_choice) override;
};

struct bidirectional_quadratic_probe : public collision_strategy
{
    int step = 0; // Keep track of probing step

    void init() override;
    int operator()(hash_entry *Table, int table_size, int last_choice) override;
};

struct common_overflow_area : public collision_strategy
{
    int overflow_start; // Start index of overflow area
    int overflow_size;  // Size of overflow area

    common_overflow_area(int table_size, int overflow_ratio = 10)
    {
        overflow_start = table_size - table_size / overflow_ratio;
        overflow_size = table_size / overflow_ratio;
    }

    void init() override;
    int operator()(hash_entry *Table, int table_size, int last_choice) override;
};

// Structure for a hashtable
struct hashtable
{
    hash_entry *Table;
    int table_size;

    hashing_strategy *my_hashing; // 如果改为hashing_strategy my_hashing, 即不是用指针作为hashtable的成员, 而是让hashing_strategy结构体直接作为hashtable的成员. 会发生什么bug?
    collision_strategy *my_collision;

    // Constructor for a hashtable
    hashtable(int size, hashing_strategy *hashing, collision_strategy *collision)
        : table_size(size), my_hashing(hashing), my_collision(collision)
    {
        Table = new hash_entry[table_size];
    }

    // Insert an entry into the hashtable
    bool insert(hash_entry entry)
    {
        // Hash within the main table only
        int main_table_size = table_size - static_cast<common_overflow_area *>(my_collision)->overflow_size;
        int last_choice = (*my_hashing)(entry.my_string, main_table_size);
        my_collision->init();

        // Try inserting in the main table
        while (last_choice < main_table_size && Table[last_choice].my_string != NULL)
            last_choice = (*my_collision)(Table, main_table_size, last_choice);

        // If main table is full, try the overflow area
        if (last_choice >= main_table_size || Table[last_choice].my_string != NULL)
            last_choice = (*my_collision)(Table, table_size, last_choice);

        if (last_choice == -1 || Table[last_choice].my_string != NULL)
            return false; // No space available

        Table[last_choice] = entry;
        return true;
    }

    // Query an entry in the hashtable
    int query(char *query_string)
    {
        // Hash within the main table only
        int main_table_size = table_size - static_cast<common_overflow_area *>(my_collision)->overflow_size;
        int last_choice = (*my_hashing)(query_string, main_table_size);
        my_collision->init();

        // Search in the main table
        while (last_choice < main_table_size && Table[last_choice].my_string != NULL &&
               strcmp(Table[last_choice].my_string, query_string) != 0)
            last_choice = (*my_collision)(Table, main_table_size, last_choice);

        // If not found in main table, search in the overflow area
        if (last_choice >= main_table_size || Table[last_choice].my_string == NULL)
            last_choice = (*my_collision)(Table, table_size, last_choice);

        if (last_choice == -1 || Table[last_choice].my_string == NULL)
            return -1; // Not found

        return Table[last_choice].my_data;
    }
};
