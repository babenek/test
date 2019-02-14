//
// Created by user on 16.01.19.
//

#include <map>
#include <iostream>

class Eagle {
public:
    std::map<int, int> entries;
    int exit;

    int
    findNest(int egg) {
        int prev = -1;
        for (auto n:entries)
        {
            if (0 > prev)
            {
                prev = n.first;
            }
            else
            {
                if (prev < egg and egg < n.first)
                {
                    std::cout << "found:" << n.first;
                    break;
                }
            }
        };
        return 0;
    }
};

int
main(void) {
    Eagle e;
    e.entries[2] = 0;
    e.entries[5] = 0;
    e.findNest(3);
    return 0;
};