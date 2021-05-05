#include <vector>
#include <list>
#include <cstddef>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    int a = atoi(argv[argc - 1]);
    std::cout << a << std::endl;
    for (int ctr = 0; ctr < a; ++ctr) {
        #if 0
            std::vector<std::size_t> a(10'000);
            for (std::size_t i = 0; i < a.size(); ++i)
                a[i] = i;
        #endif

        #if 1
        std::list<std::size_t> b(10'000);
        std::size_t counter = 0;
        for (auto& it : b) {
            it = counter;
            ++counter;
        }
        #endif
    }
}
