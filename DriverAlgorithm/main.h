#pragma once

#include <iostream>
#include <array>
#include <Windows.h>

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

void throwError(std::string err_string);

void startProcess();

std::vector<std::string> processDataToSolution(std::string& text, const char& separator, int& line);

std::pair<int, int> intersectionCoords(std::pair<int, int> A, std::pair<int, int> B, std::pair<int, int> C, std::pair<int, int> D);
