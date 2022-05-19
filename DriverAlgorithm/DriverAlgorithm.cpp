#include <iostream>
#include <vector>
#include <string>
#include "main.h"
#include <time.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void throwError(std::string err_string) {
    std::cerr << err_string << std::endl;
    exit(EXIT_FAILURE);
}

template<typename T>
void PrintVector(T& v) {
    for (int i = 0; i < v.size(); ++i)
        std::cout << v[i] << ((i == v.size() - 1) ? "" : ",");
    std::cout << "\n\n";
}

int main()
{
    clock_t tStart = clock();
    
    startProcess();

    double tEnd = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    SetConsoleTextAttribute(hConsole, 8);
    std::cout << "\n---------------------------";
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << "\n Execution time: ";
    SetConsoleTextAttribute(hConsole, 11);
    std::cout << tEnd << "s";
    SetConsoleTextAttribute(hConsole, 8);
    std::cout << "\n---------------------------\n";

    std::cin.get();

}
