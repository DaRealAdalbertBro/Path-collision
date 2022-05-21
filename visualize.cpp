#include "settings.h"

#if VISUALIZATION == true

/*
 * File:   show_two_turtle.cpp
 * Author: Jesse W. Walker
 */

#include "CTurtle.hpp"
#include <fstream>
#include "main.h"

namespace ct = cturtle;

int covertDirectionToAngle(char& direction) {
    if (direction == 'E')
        return 0;
    else if (direction == 'N')
        return 90;
    else if (direction == 'W')
        return 180;
    else if (direction == 'S')
        return 270;
}

void visualizeAlgorithm() {
    std::ifstream file(DEFAULT_DATA_DIRECTORY);
    std::string fileContent;

    if (!file.is_open()) throwError(L_FILE_NOT_FOUND);

    ct::TurtleScreen scr;
    ct::Turtle driver1(scr);
    ct::Turtle driver2(scr);
    ct::Turtle solutionPoints(scr);


    driver1.speed(V_SPEED);
    driver1.pencolor({ V_DRIVER1_COLOR });
    driver1.penup();
    driver1.setpos(V_OFFSET_X, V_OFFSET_Y);
    driver1.pendown();

    driver2.speed(V_SPEED);
    driver2.pencolor({ V_DRIVER2_COLOR });
    driver2.penup();
    driver2.setpos(V_OFFSET_X, V_OFFSET_Y);
    driver2.pendown();

    solutionPoints.speed(V_SPEED);
    solutionPoints.pencolor({ V_SOLUTION_POINTS_COLOR });
    solutionPoints.penup();
    solutionPoints.setpos(V_OFFSET_X, V_OFFSET_Y);
    solutionPoints.pendown();
    solutionPoints.width(V_SOLUTION_POINTS_PEN_WIDTH * V_SCALE);

    unsigned short int line = 0;
    std::string temp = "";
    while (std::getline(file, fileContent)) {
        if (line == 0) {}
        else if (line == 1) {
            for (unsigned short int i = 0; i <= fileContent.size(); i++) {
                if (fileContent[i] == ',' || i == fileContent.length()) {
                    if (temp.size() == 0) throwError(L_INVALID_TRACK_FORMAT, {line, i});

                    char direction = temp.back();
                    driver1.setheading(covertDirectionToAngle(direction));
                    driver1.forward(std::stoi(temp.substr(0, temp.size() - 1)) * V_SCALE);
                    temp = "";
                }
                else temp.push_back(fileContent[i]);
            }
        }
        else if (line == 2) {
            for (unsigned short int i = 0; i <= fileContent.size(); i++) {
                if (fileContent[i] == ',' || i == fileContent.length()) {
                    if (temp.size() == 0) throwError(L_INVALID_TRACK_FORMAT, { line, i });

                    char direction = temp.back();
                    driver2.setheading(covertDirectionToAngle(direction));
                    driver2.forward(std::stoi(temp.substr(0, temp.size() - 1)) * V_SCALE);
                    temp = "";
                }
                else temp.push_back(fileContent[i]);
            }
        }
        else break;
        line++;
    }

    for (const auto& value : solution) {
        solutionPoints.penup();
        solutionPoints.setpos(value.xCoord * V_SCALE + V_OFFSET_X - 4, value.yCoord * V_SCALE + V_OFFSET_Y - 4);
        solutionPoints.pendown();
        solutionPoints.forward(3);
        solutionPoints.right(90);
        solutionPoints.forward(3);
        solutionPoints.right(90);
        solutionPoints.forward(3);
    }

    solutionPoints.hideturtle();

    scr.mainloop();
}

#endif