#include <iostream>
#include "hashtable.h"

void show_usage(const char *prog_name)
{
    std::cout << "Usage: " << prog_name << " <hashing_strategy> <collision_strategy>\n";
    std::cout << "Hashing Strategies: naive, bad, good\n";
    std::cout << "Collision Strategies: linear, quadratic, overflow\n";
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        show_usage(argv[0]);
        return 1;
    }

    hashing_strategy *hashing = nullptr;
    collision_strategy *collision = nullptr;

    // Select hashing strategy
    if (strcmp(argv[1], "naive") == 0)
        hashing = new naive_hashing();
    else if (strcmp(argv[1], "bad") == 0)
        hashing = new bad_hashing();
    else if (strcmp(argv[1], "good") == 0)
        hashing = new good_hashing();
    else
    {
        std::cerr << "Invalid hashing strategy: " << argv[1] << "\n";
        show_usage(argv[0]);
        return 1;
    }

    // Select collision strategy
    if (strcmp(argv[2], "linear") == 0)
        collision = new linear_probe();
    else if (strcmp(argv[2], "quadratic") == 0)
        collision = new bidirectional_quadratic_probe();
    else if (strcmp(argv[2], "overflow") == 0)
        collision = new common_overflow_area(10000);
    else
    {
        std::cerr << "Invalid collision strategy: " << argv[2] << "\n";
        show_usage(argv[0]);
        return 1;
    }

    int type;
    char buffer[1000];
    int data;

    hashtable table(10000, hashing, collision);

    while (std::cin >> type)
    {
        if (type == 0) // Insert
        {
            std::cin >> buffer >> data;
            if (!table.insert(hash_entry(buffer, data)))
                std::cerr << "Failed to insert " << buffer << "\n";
        }
        else if (type == 1) // Query
        {
            std::cin >> buffer;
            int result = table.query(buffer);
            if (result == -1)
                std::cout << -1 << "\n";
            else
                std::cout << result << "\n";
        }
        else
            break;
    }

    return 0;
}