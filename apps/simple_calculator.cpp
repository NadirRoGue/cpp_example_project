#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

#include <cpp_example_lib/operations.h>

void printMenu() {
    std::cout << "Simple calculator. Usage: <operation> [number a] [number b+\n"
              << "Operations:\n"
              << "\t - add: Adds two numbers.\n"
              << "\t - sub: Substract two numbers.\n"
              << "\t - mult: Multiply two numbers.\n"
              << "\t - div: Divide number a by number b.\n"
              << "\t - exit: Exits program.\n\n"
              << "Example: simple_calculator add 5 10" << std::endl;
}

std::vector<std::string> splitString(const std::string& s) {
    std::vector<std::string> result;

    size_t lastIndex = 0;
    size_t prevIndex = 0;
    while (lastIndex != std::string::npos) {
        lastIndex = s.find(' ', prevIndex);
        if (lastIndex != std::string::npos) {
            auto token = s.substr(prevIndex, lastIndex - prevIndex);

            std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            result.push_back(token);

            prevIndex = lastIndex + 1;
        } else {
            result.push_back(s.substr(prevIndex, s.size() - prevIndex));
        }
    }

    return result;
}

int main(int /*argc*/, char** /*argv*/) {
    const std::unordered_map<
        std::string,
        std::function<bbp::examplelib::Real(bbp::examplelib::Real, bbp::examplelib::Real)>>
        operationMap = {
            {"add", bbp::examplelib::add<bbp::examplelib::Real>},
            {"sub", bbp::examplelib::sub<bbp::examplelib::Real>},
            {"mult", bbp::examplelib::mul<bbp::examplelib::Real>},
            {"div", bbp::examplelib::divideBy<bbp::examplelib::Real>},
        };

    printMenu();

    while (true) {
        std::cout << "Your operation: ";
        std::string line;
        std::getline(std::cin, line);
        auto tokens = splitString(line);

        if (*tokens.begin() == "exit") {
            std::cout << "Bye" << std::endl;
            break;
        }

        if (tokens.size() < 3) {
            std::cout << "\nNot enough arguments!\n";
            printMenu();
            continue;
        }

        auto it = operationMap.find(*(tokens.begin()));
        if (it == operationMap.end()) {
            std::cout << "\nUnknown operation " << *(tokens.begin()) << "\n";
            printMenu();
            continue;
        }

        try {
            auto a = std::stod(tokens[1]);
            auto b = std::stod(tokens[2]);
            std::cout << "Result: " << it->second(a, b) << std::endl;
        } catch (...) {
            std::cout << "There input numbers could not be parsed\n";
        }
    }

    return 0;
}
