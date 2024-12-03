#include <iostream>
#include "hashtable.h"

int main()
{
    hashing_strategy *hashing = new good_hashing();
    collision_strategy *collision = new linear_probe();

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