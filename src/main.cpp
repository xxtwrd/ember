#include <iostream>
#include <string>
#include <sstream>
#include "memory.hpp"
#include "dump.hpp"
#include "cpu.hpp"

int main() {
    Memory mem{};

    CPU cpu;
    cpu.mem = &mem;

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
        }
        else if (cmd == "dump") {
            mem_dump(mem);
        }
        else if (cmd == "set") {
            size_t addr;
            int val;
            if (ss >> addr >> val) {
                if (mem_set(mem, addr, static_cast<Byte>(val))) {
                    std::cout << "OK" << std::endl;
                }
                else {
                    std::cout << "Error: Address out of bounds" << std::endl;
                }
            }
            else {
                std::cout << "Usage: set <address> <value>" << std::endl;
            }
        }
        else if (cmd == "get") {
            size_t addr;
            if (ss >> addr) {
                Byte val = 0;
                if (mem_get(mem, addr, val)) {
                    show_byte(val);
                    std::cout << std::endl;
                }
                else {
                    std::cout << "Error: Address out of bounds" << std::endl;
                }
            }
            else {
                std::cout << "Usage: get <address>" << std::endl;
            }
        }
        
        else if (cmd == "reg") {
            std::string r, v;
            long value = 0;
            if (!(ss >> r) || !(ss >> v)) {
                std::cout << "Usage: reg <a|b> <0..255>" << std::endl;
            }
            else {
                try {
                    value = std::stol(v);
                    if (value < 0 || value > 255) {
                        std::cout << "Error: Value must be between 0 and 255" << std::endl;
                    }
                    else if (r == "a") {
                        cpu.a = static_cast<Byte>(value);
                        std::cout << "OK" << std::endl;
                    }
                    else if (r == "b") {
                        cpu.b = static_cast<Byte>(value);
                        std::cout << "OK" << std::endl;
                    }
                    else {
                        std::cout << "Unknown register: " << r << std::endl;
                    }
                }
                catch (...) {
                    std::cout << "Usage: reg <a|b> <0..255>" << std::endl;
                }
            }
        }
        else if (cmd == "step") {
            step(cpu);
            std::cout << "OK" << std::endl;
        }
        else if (cmd == "regs") {
            dump_regs(cpu);
        }

        else if (cmd == "help") {
            std::cout << "Commands:" << std::endl;
            std::cout << "  set <addr> <val> - Set byte at address" << std::endl;
            std::cout << "  get <addr>       - Show byte at address" << std::endl;
            std::cout << "  dump             - Dump memory contents" << std::endl;
            std::cout << "  regs             - Show CPU registers and flags" << std::endl;
            std::cout << "  reg <a|b> <val>  - Set register A or B" << std::endl;
            std::cout << "  step             - Execute one instruction" << std::endl;
            std::cout << "  quit             - Exit program" << std::endl;
        }
        else if (!cmd.empty()) {
            std::cout << "Unknown command: " << cmd << std::endl;
        }
    }

    return 0;
}