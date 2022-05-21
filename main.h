#pragma once

#include <iostream>
#include <array>
#include <Windows.h>
#include "settings.h"

extern HANDLE hConsole;

struct driverStruct {
    int a1, a2, b1, b2;
    driverStruct(int a1, int a2, int b1, int b2) : a1(a1), a2(a2), b1(b1), b2(b2) {}
};

struct solutionStruct {
    int xCoord, yCoord;
    solutionStruct(int xCoord, int yCoord) : xCoord(xCoord), yCoord(yCoord) {};
};

struct find_duplicates : std::unary_function<solutionStruct, bool> {
    int x, y;
    find_duplicates(int& x, int& y) : x(x), y(y) {};
    bool operator()(solutionStruct const& structure) const {
        return structure.xCoord == x && structure.yCoord == y;
    }
};

extern std::array<int, 2> interval;
extern std::vector<driverStruct> driver1;
extern std::vector<solutionStruct> solution;

void throwError(const std::string &err_string, const std::pair<unsigned int, unsigned int> &line = { INT_MAX, INT_MAX });

void startProcess();

#if VISUALIZATION == true
void visualizeAlgorithm();
#endif

std::vector<std::string> processDataToSolution(std::string& text, const char& separator, int& line);

std::pair<int, int> intersectionCoords(const std::pair<int, int> &A, const std::pair<int, int> &B, const std::pair<int, int> &C, const std::pair<int, int> &D);