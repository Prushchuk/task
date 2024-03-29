#include <stdexcept>
#include <iostream>
#include <fstream>

class MathError : public std::runtime_error {
public:
    MathError(const std::string& message) : std::runtime_error(message) {}
};

class DivisionByZeroError : public MathError {
public:
    DivisionByZeroError() : MathError("Division by zero!") {}
};

class OverflowError : public MathError {
public:
    OverflowError() : MathError("Overflow!") {}
};

class FileError : public std::runtime_error {
public:
    FileError(const std::string& message) : std::runtime_error(message) {}
};

class FileNotFoundError : public FileError {
public:
    FileNotFoundError() : FileError("File not found!") {}
};

class MemoryError : public std::bad_alloc {
public:
    MemoryError() : std::bad_alloc() {}
};

int main() {
    try {
        int a = 10, b = 0;
        if (b == 0) {
            throw DivisionByZeroError();
        }
        int result = a / b;
    }
    catch (const MathError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        int* ptr = new int[1000000000000000];
        delete[] ptr;
    }
    catch (const MemoryError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        std::ifstream file("wrong_file_name.txt");
        if (!file.is_open()) {
            throw FileNotFoundError();
        }
    }
    catch (const FileError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}