#include <iostream>
#include <vector>
#include <string>
#include "main.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void throwError(const std::string &err_string, const std::pair<unsigned int, unsigned int> &line) {
    SetConsoleTextAttribute(hConsole, 12);
    if(line.second != INT_MAX) std::cerr << "FATAL ERROR: " << err_string << " Line " << line.first << ":" << line.second << "\n";
    else std::cerr << err_string << "\n";

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

    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "\n\nNOTE: ";

    SetConsoleTextAttribute(hConsole, 4);
    std::cout << "the visualization is not 100% accurate due to the scale property in the settings (default value is 0.05), but if there is a shift, break points are circlered.";
    
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << "\n" << L_VISUALIZATION << "\n";

    while (true) {
        if (GetAsyncKeyState(0x59)) {
            visualizeAlgorithm();
            break;
        }
        else if (GetAsyncKeyState(0x4E)) break;
        Sleep(100);
    }

#endif

    SetConsoleTextAttribute(hConsole, 8);
    std::cin.get();
}
