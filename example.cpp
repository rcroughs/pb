#include "include/pb.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (auto &i : pb<std::vector<int>>(v))
        std::cout << *i << " ";
    return 0;
}