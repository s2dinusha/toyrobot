#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "table.h"

class Robot {
public:
    enum Direction {
        NORTH = 0,
        EAST,
        SOUTH,
        WEST
    };

    Robot(Table& table);

    void commandPlace(int x, int y, Direction direction);

    void commandMove();

    void commandLeft();

    void commandRight();

    void commandReport() const;

    void handleCommand(const std::string command);

    std::tuple<int, int, Direction> getCurrentPosition() const;

private:
    int _xPos, _yPos;  // Position on the table (x, y)
    Direction _direction;  // Direction the robot is facing (NORTH, EAST, SOUTH, WEST)
    bool _isPlaced; // Flag set to true when robot is placed on table
    Table& _table;  // Reference to the table object

    std::unordered_map<Direction, std::string> _directionToStringMap;
    std::unordered_map<std::string, Robot::Direction> _stringToDirectionMap;
};

#endif // ROBOT_H
