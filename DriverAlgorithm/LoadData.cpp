#include <fstream>
#include <vector>
#include <string>
#include <array>
#include "main.h"

std::array<int, 2> interval;
std::vector<driverStruct> driver1;
std::vector<driverStruct> driver2;
std::vector<solutionStruct> solution;

std::vector<std::string> trackDataToArray(std::string& text, const char& separator, int& line) {
    std::string temp = "";
    std::vector<std::string>  output;
    //                                   x  y
    std::pair<int, int> lastPosition = { 0, 0 };
    int currentStepCount = 0;   // distance travelled

    for (int i = 0; i < text.length(); i++) {
        if (text[i] == separator) {
            if (separator == ',' && temp.back() != 'W' && temp.back() != 'E' && temp.back() != 'S' && temp.back() != 'N')
                throwError("Invalid track format given");

            else if (line == 1) {
                int currentToMove = std::stoi(temp.substr(0, temp.size()));
                if (currentStepCount < interval[0]) {
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;

                    if (currentDirection == 'W') {
                        if (currentStepCount > interval[0])
                            driver1.emplace_back(lastPosition.first - (currentStepCount - interval[0]), lastPosition.second, lastPosition.first - currentToMove, lastPosition.second);

                        lastPosition.first -= currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        if (currentStepCount > interval[0])
                            driver1.emplace_back(lastPosition.first + (currentStepCount - interval[0]), lastPosition.second, lastPosition.first + currentToMove, lastPosition.second);

                        lastPosition.first += currentToMove;
                    }
                    else if (currentDirection == 'S') {
                        if (currentStepCount > interval[0])
                            driver1.emplace_back(lastPosition.first, lastPosition.second - (currentStepCount - interval[0]), lastPosition.first, lastPosition.second - currentToMove);

                        lastPosition.second -= currentToMove;
                    }
                    else if (currentDirection == 'N') {
                        if (currentStepCount > interval[0])
                            driver1.emplace_back(lastPosition.first, lastPosition.second + (currentStepCount - interval[0]), lastPosition.first , lastPosition.second + currentToMove);

                        lastPosition.second += currentToMove;
                    }
                }
                else if (currentStepCount < interval[1]) {
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;
                    if (currentStepCount > interval[1]) {
                        currentToMove = interval[1]-(currentStepCount-currentToMove);
                    }

                    if (currentDirection == 'W') {
                        driver1.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first - currentToMove, lastPosition.second);
                        lastPosition.first = lastPosition.first - currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        driver1.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first + currentToMove, lastPosition.second);
                        lastPosition.first = lastPosition.first + currentToMove;
                    }

                    else if (currentDirection == 'S') {
                        driver1.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first, lastPosition.second - currentToMove);
                        lastPosition.second = lastPosition.second - currentToMove;
                    }

                    else if (currentDirection == 'N') {
                        driver1.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first, lastPosition.second + currentToMove);
                        lastPosition.second = lastPosition.second + currentToMove;
                    }
                }

            }
            else if (line == 2) {
                int currentToMove = std::stoi(temp.substr(0, temp.size()));

                // to fix
                if (currentStepCount < interval[0]) {
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;

                    if (currentDirection == 'W') {
                        if (currentStepCount > interval[0])
                            driver2.emplace_back(lastPosition.first - (currentStepCount - interval[0]), lastPosition.second, lastPosition.first - currentToMove, lastPosition.second);

                        lastPosition.first -= currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        if (currentStepCount > interval[0])
                            driver2.emplace_back(lastPosition.first + (currentStepCount - interval[0]), lastPosition.second, lastPosition.first + currentToMove, lastPosition.second);

                        lastPosition.first += currentToMove;
                    }
                    else if (currentDirection == 'S') {
                        if (currentStepCount > interval[0])
                            driver2.emplace_back(lastPosition.first, lastPosition.second - (currentStepCount - interval[0]), lastPosition.first, lastPosition.second - currentToMove);

                        lastPosition.second -= currentToMove;
                    }
                    else if (currentDirection == 'N') {
                        if (currentStepCount > interval[0])
                            driver2.emplace_back(lastPosition.first, lastPosition.second + (currentStepCount - interval[0]), lastPosition.first , lastPosition.second + currentToMove);

                        lastPosition.second += currentToMove;
                    }

                }

                // to fix - loguje jen jednou - neco s range
                else if (currentStepCount < interval[1]) {
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;
                    if (currentStepCount > interval[1]) {
                        currentToMove = currentStepCount-interval[1];
                    }

                    if (currentDirection == 'W') {
                        driver2.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first - currentToMove, lastPosition.second);
                        lastPosition.first = lastPosition.first - currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        driver2.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first + currentToMove, lastPosition.second);
                        lastPosition.first = lastPosition.first + currentToMove;
                    }

                    else if (currentDirection == 'S') {
                        driver2.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first, lastPosition.second - currentToMove);
                        lastPosition.second = lastPosition.second - currentToMove;
                    }

                    else if (currentDirection == 'N') {
                        driver2.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first, lastPosition.second + currentToMove);
                        lastPosition.second = lastPosition.second + currentToMove;
                    }

                    /*
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;
                    if (currentStepCount > interval[1]) {
                        currentToMove = interval[1]-(currentStepCount-currentToMove);
                    }

                    if (currentDirection == 'W') {
                        for (const auto& value : driver1) {
                            std::pair<int, int> coords = intersection(
                                    {lastPosition.first, lastPosition.second}, {lastPosition.first - currentToMove, lastPosition.second},
                                    {value.a1, value.a2}, {value.b1, value.b2}
                            );
                            if(coords.first != INT_MAX) solution.emplace_back(coords.first, coords.second);
                        }
                        //std::cout << "PC: " << lastPosition.first << ", " << lastPosition.second << ", " << lastPosition.first - currentToMove << ", " << lastPosition.second << "\n\n";
                        lastPosition.first -= currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        for (const auto& value : driver1) {
                            std::pair<int, int> coords = intersection(
                                    {lastPosition.first, lastPosition.second}, {lastPosition.first + currentToMove, lastPosition.second},
                                    {value.a1, value.a2}, {value.b1, value.b2}
                            );
                            if(coords.first != INT_MAX) solution.emplace_back(coords.first, coords.second);
                        }
                        //std::cout << "PC: " << lastPosition.first << ", " << lastPosition.second << ", " << lastPosition.first + currentToMove << ", " << lastPosition.second << "\n\n";
                        lastPosition.first += currentToMove;
                    }

                    else if (currentDirection == 'S') {
                        for (const auto& value : driver1) {
                            std::pair<int, int> coords = intersection(
                                    {lastPosition.first, lastPosition.second}, {lastPosition.first, lastPosition.second - currentToMove},
                                    {value.a1, value.a2}, {value.b1, value.b2}
                            );
                            if(coords.first != INT_MAX) solution.emplace_back(coords.first, coords.second);
                        }
                        //std::cout << "PC: " << lastPosition.first << ", " << lastPosition.second << ", " << lastPosition.first<< ", " << lastPosition.second - currentToMove << "\n\n";
                        lastPosition.second -= currentToMove;
                    }

                    else if (currentDirection == 'N') {
                        for (const auto& value : driver1) {
                            std::pair<int, int> coords = intersection(
                                    {lastPosition.first, lastPosition.second}, {lastPosition.first, lastPosition.second + currentToMove},
                                    {value.a1, value.a2}, {value.b1, value.b2}
                            );
                            if(coords.first != INT_MAX) solution.emplace_back(coords.first, coords.second);
                        }
                        //std::cout << "PC: " << lastPosition.first << ", " << lastPosition.second << ", " << lastPosition.first  << ", " << lastPosition.second  + currentToMove << "\n\n";
                        lastPosition.second += currentToMove;
                    }
*/
                }
            }
            output.push_back(temp);
            temp = "";
        }
        else temp.push_back(text[i]);

    }
    output.push_back(temp);
    return output;
}

void load() {
    std::ifstream file("../Data.txt");
    std::string fileContent;

    if (!file.is_open()) throwError("Couldn't open the Data.txt file");

    int line = 0;
    while (std::getline(file, fileContent)) {
        if (line == 0) {
            std::vector<std::string> tempInterval = trackDataToArray(fileContent, '-', line);
            if (tempInterval.size() != 2) throwError("Incorrect interval format, try using xxx-xxx in the Data.txt file.");
            else {
                interval[0] = std::stoi(tempInterval[0]);
                interval[1] = std::stoi(tempInterval[1]);
                if (interval[0] > interval[1]) std::swap(interval[0], interval[1]);
            };
        }
        else if (line == 1) trackDataToArray(fileContent, ',', line);
        else if (line == 2) {
            trackDataToArray(fileContent, ',', line);
            if(solution.size() == 0) std::cout << "No solutions found!\n";
            else {
                for (const auto& value : solution) {
                    std::cout << "X: " << value.xCoord << ", Y:" << value.yCoord << "\n\n";
                }
            }
        }
        else break;

        line++;
    }
}
