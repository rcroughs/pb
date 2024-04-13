#include "include/pb.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>

int main() {
    std::vector<int> v(100, 1);
    for (auto &i : pb<std::vector<int>>(v)) {
        usleep(100000);
    }
    return 0;
}