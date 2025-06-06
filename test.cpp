#include <filesystem>
#include <iostream>


int main() {
    std::filesystem::directory_iterator it("./data/");

    while (it != std::filesystem::end(it)) {
        std::cout << it->path() << '\n';
        it++;
    }
}