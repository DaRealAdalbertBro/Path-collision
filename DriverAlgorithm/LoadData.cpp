#include <fstream>
#include <vector>
#include <string>
#include <array>
#include "main.h"

std::array<int, 2> interval;
std::vector<driverStruct> driver1;
std::vector<std::string> driver2;

std::vector<std::string> trackDataToArray(std::string& text, const char& separator, int& line) {
    std::string temp = "";
    std::vector<std::string> output;
    //                                   x  y
    std::pair<int, int> lastPosition = { 0, 0 };
    int currentStepCount = 0;   // distance travelled

    for (int i = 0; i < text.length(); i++) {
        if (text[i] == separator) {
            if (separator == ',' && temp.back() != 'W' && temp.back() != 'E' && temp.back() != 'S' && temp.back() != 'N') throwError("Invalid track format given");
            else if (line == 1) {
                if (currentStepCount < interval[0]) {
                    char currentDirection = temp.back();
                    int currentToMove = std::stoi(temp.substr(0, temp.size()));
                    currentStepCount += currentToMove;

                    if (currentDirection == 'W') 
                        lastPosition.first = lastPosition.first - currentToMove;

                    else if (currentDirection == 'E')
                        lastPosition.first = lastPosition.first + currentToMove;

                    else if (currentDirection == 'S')
                        lastPosition.second = lastPosition.second - currentToMove;

                    else if (currentDirection == 'N')
                        lastPosition.second = lastPosition.second + currentToMove;
                }

                else if (!(currentStepCount > interval[1])) {
                    char currentDirection = temp.back();
                    int currentToMove = std::stoi(temp.substr(0, temp.size()));
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
                // to do
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
    std::ifstream file("Data.txt");
    std::string fileContent;

    if (file.is_open() == false) throwError("Couldn't open the Data.txt file");

    int line = 0;
    while (std::getline(file, fileContent)) {
        if (line == 0) {
            std::vector<std::string> tempInterval = trackDataToArray(fileContent, '-', line);
            if (tempInterval.size() != 2) throwError("Incorrect interval format, try using xxx-xxx in the Data.txt file.");
            else {
                interval[0] = std::stoi(tempInterval[0]);
                interval[1] = std::stoi(tempInterval[1]);
            };
        }
        else if (line == 1) trackDataToArray(fileContent, ',', line);

        else if (line == 2) {
            std::vector<std::string> tempDriver = trackDataToArray(fileContent, ',', line);
            driver2.insert(driver2.end(), tempDriver.begin(), tempDriver.end());
        }
        else break;

        line++;
    }
}