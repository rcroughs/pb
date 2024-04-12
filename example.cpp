#include "include/pb.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>

int main() {
    std::vector<int> v(50, 1);
    int counter = 0;
    for (auto &i : pb<std::vector<int>>(v)) {
        sleep(1);
        counter++;
    }
    return 0;
}