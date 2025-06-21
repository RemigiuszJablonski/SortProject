#include "include/Menu.h"

int main() {
    try {
        Menu menu;
        menu.readConfig();
        menu.handleInput();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}