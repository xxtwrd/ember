#include <iostream>
#include <string>
#include <sstream>
#include "memory.hpp"
#include "dump.hpp"

int main() {
    Memory mem{};
    std::string line;

    std::cout << "Ember Virtual Machine started. Type help for commands." << std::endl;

    while (true) {
        std::cout << "ember> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "quit" || cmd == "exit") {
            break;
        } else if (cmd == "dump") {
            mem_dump(mem);
        } else if (cmd == "set") {
            size_t addr;
            int val;
            if (ss >> addr >> val) {
                if (mem_set(mem, addr, static_cast<Byte>(val))) {
                    std::cout << "OK" << std::endl;
                } else {
                    std::cout << "Error: Address out of bounds" << std::endl;
                }
            } else {
                std::cout << "Usage: set <address> <value>" << std::endl;
            }
        } else if (cmd == "get") {
            size_t addr;
            if (ss >> addr) {
                Byte val = 0;
                if (mem_get(mem, addr, val)) {
                    show_byte(val);
                    std::cout << std::endl;
                } else {
                    std::cout << "Error: Address out of bounds" << std::endl;
                }
            } else {
                std::cout << "Usage: get <address>" << std::endl;
            }
        } else if (cmd == "help") {
            std::cout << "Commands:" << std::endl;
            std::cout << "  set <addr> <val> - Set byte at address" << std::endl;
            std::cout << "  get <addr>       - Show byte at address" << std::endl;
            std::cout << "  dump             - Dump memory contents" << std::endl;
            std::cout << "  quit             - Exit program" << std::endl;
        } else if (!cmd.empty()) {
            std::cout << "Unknown command: " << cmd << std::endl;
        }
    }

    return 0;
}

