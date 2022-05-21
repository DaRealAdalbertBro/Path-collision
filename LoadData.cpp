#include <fstream>
#include <vector>
#include <string>
#include <array>
#include "main.h"

std::array<int, 2> interval;
std::vector<driverStruct> driver1;
std::vector<solutionStruct> solution;

std::vector<std::string> processDataToSolution(std::string& text, const char& separator, unsigned short int& line) {
    std::string temp = "";
    std::vector<std::string> output;
    //                                   x  y
    std::pair<int, int> lastPosition = { 0, 0 };
    int currentStepCount = 0;   // distance travelled
    for (int i = 0; i <= text.length(); i++) {

        if (text[i] == separator || i == text.length()) {
            if (temp.size() == 0) throwError(L_INVALID_TRACK_FORMAT, { line, i });
            
            // track format validation
            if (separator == ',' && temp.back() != 'W' && temp.back() != 'E' && temp.back() != 'S' && temp.back() != 'N')
                throwError(L_INVALID_TRACK_FORMAT, { line, i });

            // create an array of driver1 intervals
            else if (line == 1) {
                int currentToMove = std::stoi(temp.substr(0, temp.size()));
                if (currentStepCount < interval[0]) {
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;

                    if (currentDirection == 'W') {
                        if (currentStepCount > interval[0])
                            driver1.emplace_back(lastPosition.first - (interval[0] - lastPosition.first), lastPosition.second, lastPosition.first - currentToMove, lastPosition.second);

                        lastPosition.first -= currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        if (currentStepCount > interval[0])
                            driver1.emplace_back(lastPosition.first + (interval[0] - lastPosition.first), lastPosition.second, lastPosition.first + currentToMove, lastPosition.second);

                        lastPosition.first += currentToMove;
                    }
                    else if (currentDirection == 'S') {
                        if (currentStepCount > interval[0])
                            driver1.emplace_back(lastPosition.first, lastPosition.second - (interval[0] - lastPosition.second), lastPosition.first, lastPosition.second - currentToMove);

                        lastPosition.second -= currentToMove;
                    }
                    else if (currentDirection == 'N') {
                        if (currentStepCount > interval[0])
                            driver1.emplace_back(lastPosition.first, lastPosition.second + (interval[0] - lastPosition.second), lastPosition.first, lastPosition.second + currentToMove);

                        lastPosition.second += currentToMove;
                    }
                }
                else if (currentStepCount < interval[1]) {
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;
                    if (currentStepCount > interval[1]) {
                        currentToMove = interval[1] - (currentStepCount - currentToMove);
                    }

                    if (currentDirection == 'W') {
                        driver1.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first - currentToMove, lastPosition.second);
                        lastPosition.first -= currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        driver1.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first + currentToMove, lastPosition.second);
                        lastPosition.first += currentToMove;
                    }

                    else if (currentDirection == 'S') {
                        driver1.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first, lastPosition.second - currentToMove);
                        lastPosition.second -= currentToMove;
                    }

                    else if (currentDirection == 'N') {
                        driver1.emplace_back(lastPosition.first, lastPosition.second, lastPosition.first, lastPosition.second + currentToMove);
                        lastPosition.second += currentToMove;
                    }
                }

            }
            // search for intersections of driver1 and driver2
            else if (line == 2) {
                int currentToMove = std::stoi(temp.substr(0, temp.size()));
                if (currentStepCount < interval[0]) {
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;

                    if (currentDirection == 'W') {
                        if (currentStepCount > interval[0]) {
                            for (const auto& value : driver1) {
                                std::pair<int, int> coords = intersectionCoords(
                                    { lastPosition.first - (interval[0] - lastPosition.first), lastPosition.second }, { lastPosition.first - currentToMove, lastPosition.second },
                                    { value.a1, value.a2 }, { value.b1, value.b2 }
                                );
                                auto tempStruct = std::find_if(solution.begin(), solution.end(), find_duplicates({ coords.first, coords.second }));
                                if (coords.first != INT_MAX && solution.end() == tempStruct) {
                                    solution.emplace_back(coords.first, coords.second);
                                    if (solution.size() == RESULT_LIMIT) return output;
                                }
                            }
                            //std::cout << "" << lastPosition.first - (interval[0] - lastPosition.first) << " " << lastPosition.second << " " << lastPosition.first - currentToMove << " " << lastPosition.second << "\n\n";
                        }
                        lastPosition.first -= currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        if (currentStepCount > interval[0]) {
                            for (const auto& value : driver1) {
                                std::pair<int, int> coords = intersectionCoords(
                                    { lastPosition.first + (interval[0] - lastPosition.first), lastPosition.second }, { lastPosition.first + currentToMove, lastPosition.second },
                                    { value.a1, value.a2 }, { value.b1, value.b2 }
                                );
                                auto tempStruct = std::find_if(solution.begin(), solution.end(), find_duplicates({ coords.first, coords.second }));
                                if (coords.first != INT_MAX && solution.end() == tempStruct) {
                                    solution.emplace_back(coords.first, coords.second);
                                    if (solution.size() == RESULT_LIMIT) return output;
                                }
                            }
                            //std::cout << "" << lastPosition.first + (interval[0] - lastPosition.first) << " " << lastPosition.second << " " << lastPosition.first + currentToMove << " " << lastPosition.second << "\n\n";
                        }
                        lastPosition.first += currentToMove;
                    }
                    else if (currentDirection == 'S') {
                        if (currentStepCount > interval[0]) {
                            for (const auto& value : driver1) {
                                std::pair<int, int> coords = intersectionCoords(
                                    { lastPosition.first, lastPosition.second - (interval[0] - lastPosition.second) }, { lastPosition.first, lastPosition.second - currentToMove },
                                    { value.a1, value.a2 }, { value.b1, value.b2 }
                                );
                                auto tempStruct = std::find_if(solution.begin(), solution.end(), find_duplicates({ coords.first, coords.second }));
                                if (coords.first != INT_MAX && solution.end() == tempStruct) {
                                    solution.emplace_back(coords.first, coords.second);
                                    if (solution.size() == RESULT_LIMIT) return output;
                                }
                            }
                            //std::cout << "" << lastPosition.first << " " << lastPosition.second - (interval[0] - lastPosition.first) << " " << lastPosition.first << " " << lastPosition.second - currentToMove << "\n\n";
                        }
                        lastPosition.second -= currentToMove;
                    }
                    else if (currentDirection == 'N') {
                        if (currentStepCount > interval[0]) {
                            for (const auto& value : driver1) {
                                std::pair<int, int> coords = intersectionCoords(
                                    { lastPosition.first, lastPosition.second + (interval[0] - lastPosition.second) }, { lastPosition.first, lastPosition.second + currentToMove },
                                    { value.a1, value.a2 }, { value.b1, value.b2 }
                                );
                                auto tempStruct = std::find_if(solution.begin(), solution.end(), find_duplicates({ coords.first, coords.second }));
                                if (coords.first != INT_MAX && solution.end() == tempStruct) {
                                    solution.emplace_back(coords.first, coords.second);
                                    if (solution.size() == RESULT_LIMIT) return output;
                                }
                            }
                            //std::cout << "" << lastPosition.first << " " << lastPosition.second + (interval[0] - lastPosition.first) << " " << lastPosition.first << " " << lastPosition.second + currentToMove << "\n\n";
                        }
                        lastPosition.second += currentToMove;
                    }

                }
                else if (currentStepCount < interval[1]) {
                    char currentDirection = temp.back();
                    currentStepCount += currentToMove;

                    if (currentStepCount > interval[1]) {
                        currentToMove = interval[1] - (currentStepCount - currentToMove);
                    }

                    if (currentDirection == 'W') {
                        for (const auto& value : driver1) {
                            std::pair<int, int> coords = intersectionCoords(
                                { lastPosition.first, lastPosition.second }, { lastPosition.first - currentToMove, lastPosition.second },
                                { value.a1, value.a2 }, { value.b1, value.b2 }
                            );
                            auto tempStruct = std::find_if(solution.begin(), solution.end(), find_duplicates({ coords.first, coords.second }));
                            if (coords.first != INT_MAX && solution.end() == tempStruct) {
                                solution.emplace_back(coords.first, coords.second);
                                if (solution.size() == RESULT_LIMIT) return output;
                            }
                        }
                        //std::cout << "" << lastPosition.first << " " << lastPosition.second << " " << lastPosition.first - currentToMove << " " << lastPosition.second << "\n\n";
                        lastPosition.first -= currentToMove;
                    }
                    else if (currentDirection == 'E') {
                        for (const auto& value : driver1) {
                            std::pair<int, int> coords = intersectionCoords(
                                { lastPosition.first, lastPosition.second }, { lastPosition.first + currentToMove, lastPosition.second },
                                { value.a1, value.a2 }, { value.b1, value.b2 }
                            );
                            auto tempStruct = std::find_if(solution.begin(), solution.end(), find_duplicates({ coords.first, coords.second }));
                            if (coords.first != INT_MAX && solution.end() == tempStruct) {
                                solution.emplace_back(coords.first, coords.second);
                                if (solution.size() == RESULT_LIMIT) return output;
                            }
                        }
                        //std::cout << "" << lastPosition.first << " " << lastPosition.second << " " << lastPosition.first + currentToMove << " " << lastPosition.second  << "\n\n";
                        lastPosition.first += currentToMove;
                    }

                    else if (currentDirection == 'S') {
                        for (const auto& value : driver1) {
                            std::pair<int, int> coords = intersectionCoords(
                                { lastPosition.first, lastPosition.second }, { lastPosition.first, lastPosition.second - currentToMove },
                                { value.a1, value.a2 }, { value.b1, value.b2 }
                            );
                            auto tempStruct = std::find_if(solution.begin(), solution.end(), find_duplicates({ coords.first, coords.second }));
                            if (coords.first != INT_MAX && solution.end() == tempStruct) {
                                solution.emplace_back(coords.first, coords.second);
                                if (solution.size() == RESULT_LIMIT) return output;
                            }
                        }
                        //std::cout << "" << lastPosition.first << " " << lastPosition.second << " " << lastPosition.first << " " << lastPosition.second - currentToMove << "\n\n";
                        lastPosition.second -= currentToMove;
                    }

                    else if (currentDirection == 'N') {
                        for (const auto& value : driver1) {
                            std::pair<int, int> coords = intersectionCoords(
                                { lastPosition.first, lastPosition.second }, { lastPosition.first, lastPosition.second + currentToMove },
                                { value.a1, value.a2 }, { value.b1, value.b2 }
                            );
                            auto tempStruct = std::find_if(solution.begin(), solution.end(), find_duplicates({ coords.first, coords.second }));
                            if (coords.first != INT_MAX && solution.end() == tempStruct) {
                                solution.emplace_back(coords.first, coords.second);
                                if (solution.size() == RESULT_LIMIT) return output;
                            }
                        }
                        //std::cout << "" << lastPosition.first << " " << lastPosition.second << " " << lastPosition.first << " " << lastPosition.second + currentToMove << "\n\n";
                        lastPosition.second += currentToMove;
                    }
                    
                }
            }

            output.push_back(temp);
            temp = "";
        } else temp.push_back(text[i]);

    }
    return output;
}

void startProcess() {
    std::ifstream file(DEFAULT_DATA_DIRECTORY);
    std::string fileContent;

    if (!file.is_open()) throwError(L_FILE_NOT_FOUND);

    unsigned short int line = 0;
    while (std::getline(file, fileContent)) {
        if (line == 0) {
            std::vector<std::string> tempInterval = processDataToSolution(fileContent, '-', line);
            if (tempInterval.size() != 2) throwError(L_INVALID_INTERVAL_FORMAT);
            else {
                interval[0] = std::stoi(tempInterval[0]);
                interval[1] = std::stoi(tempInterval[1]);
                if (interval[0] > interval[1]) std::swap(interval[0], interval[1]);
            };
        }
        else if (line == 1) processDataToSolution(fileContent, ',', line);
        else if (line == 2) {
            processDataToSolution(fileContent, ',', line);
            if (solution.size() == 0) {
                SetConsoleTextAttribute(hConsole, 12);
                std::cout << L_NO_SOLUTIONS << "\n";
                SetConsoleTextAttribute(hConsole, 8);
            }
            else {
                
                SetConsoleTextAttribute(hConsole, 8);
                std::cout << "\n------------------------------------------------";
                SetConsoleTextAttribute(hConsole, 7);
                std::cout << "\n " << L_RESULT_COORDS << ":\n";
                SetConsoleTextAttribute(hConsole, 8);
                std::cout << "------------------------------------------------\n";
                SetConsoleTextAttribute(hConsole, 10);

                for (int i = 0; i < solution.size(); i++) {
                    if (i == 1) {
                        SetConsoleTextAttribute(hConsole, 8);
                        std::cout << "\n------------------------";
                        SetConsoleTextAttribute(hConsole, 7);
                        std::cout << "\n " << L_RESULT_COORDS_OTHER << ":\n";
                        SetConsoleTextAttribute(hConsole, 8);
                        std::cout << "------------------------\n";
                        SetConsoleTextAttribute(hConsole, 14);

                    }
                    std::cout << "[" << solution[i].xCoord << ", " << solution[i].yCoord << "]\n";
                    
                }
                
            }
        }
        else break;

        line++;
    }

    SetConsoleTextAttribute(hConsole, 7);
}
