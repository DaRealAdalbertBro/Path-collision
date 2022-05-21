#include <iostream>
#include <vector>
#include <string>
#include "main.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void throwError(const std::string &err_string, const std::pair<unsigned int, unsigned int> &line) {
    SetConsoleTextAttribute(hConsole, 12);
    if(line.second != INT_MAX) std::cerr << "FATAL ERROR: " << err_string << " Line " << line.first << ":" << line.second;
    std::cerr << err_string << "\n";

    SetConsoleTextAttribute(hConsole, 8);
    exit(EXIT_FAILURE);
}

int main() {
#if PROCESS_TIME == true
    clock_t tStart = clock();
    
    startProcess();

    double tEnd = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    SetConsoleTextAttribute(hConsole, 8);
    std::cout << "\n---------------------------";
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << "\n " << L_PROCESS_TIME << ": ";
    SetConsoleTextAttribute(hConsole, 11);
    std::cout << tEnd << "s";
    SetConsoleTextAttribute(hConsole, 8);
    std::cout << "\n---------------------------\n";

#else
    startProcess();
#endif


#if VISUALIZATION == true
    char answer;
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << "\n" << L_VISUALIZATION <<"\n";
    std::cin >> answer;
    if (tolower(answer) == 'y')
        visualizeAlgorithm();

    SetConsoleTextAttribute(hConsole, 8);

#endif

    std::cin.get();
}