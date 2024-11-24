#include <sstream>
#include "robot.h"

Robot::Robot(Table& table) : _xPos(-1), _yPos(-1), _direction(NORTH), _isPlaced(false), _table(table) {
    _directionToStringMap = {
        {Direction::NORTH, "NORTH"},
        {Direction::EAST, "EAST"},
        {Direction::SOUTH, "SOUTH"},
        {Direction::WEST, "WEST"}
    };
    _stringToDirectionMap = {
        {"NORTH", Robot::Direction::NORTH},
        {"EAST", Robot::Direction::EAST},
        {"SOUTH", Robot::Direction::SOUTH},
        {"WEST", Robot::Direction::WEST}
    };
}

void Robot::commandPlace(int x, int y, Direction direction) {
    if (_table.isOnTable(x, y)) {
        _xPos = x;
        _yPos = y;
        _direction = direction;
        _isPlaced = true;
    } else {
        std::cout << "Invalid position: (" << x << "," << y << ")" << std::endl;
        std::cout << "Table dimentions: (" << _table.getWidth() << "," << _table.getHeight() << ")" << std::endl;
    }
}

void Robot::commandMove() {
    if (!_isPlaced) return;

    int newX = _xPos, newY = _yPos;
    switch (_direction) {
        case NORTH: newY++; break;
        case EAST: newX++; break;
        case SOUTH: newY--; break;
        case WEST: newX--; break;
    }

    if (_table.isOnTable(newX, newY)) {
        _xPos = newX;
        _yPos = newY;
    }
}

void Robot::commandLeft() {
    if (!_isPlaced) return;
    _direction = static_cast<Direction>((_direction + 3) % 4);
}

void Robot::commandRight() {
    if (!_isPlaced) return;
    _direction = static_cast<Direction>((_direction + 1) % 4);
}

void Robot::commandReport() const {
    std::cout << _xPos << "," << _yPos << "," << _directionToStringMap.find(_direction)->second << std::endl;
}

void Robot::handleCommand(const std::string command) {
    if (command.find("PLACE") == 0) {
        int x, y;
        std::string strPlace, strDir;
        strPlace = command.substr(5); // Remove "PLACE " prefix (5 characters)
        std::istringstream stream(strPlace);
        char comma;  // To consume the comma between x and y
        stream >> x >> comma >> y >> comma >> strDir;
        auto it = _stringToDirectionMap.find(strDir);
        if (it != _stringToDirectionMap.end()) 
            commandPlace(x, y, it->second);
        else
            std::cout << "Invalid direction: (" << strDir << ")" << std::endl;
    } else if (command == "MOVE") {
        commandMove();
    } else if (command == "LEFT") {
        commandLeft();
    } else if (command == "RIGHT") {
        commandRight();
    } else if (command == "REPORT") {
        commandReport();
    } else {
        std::cout << "Invalid command: (" << command << ")" << std::endl;
    }
}

std::tuple<int, int, Robot::Direction> Robot::getCurrentPosition() const {
    return std::make_tuple(_xPos, _yPos, _direction);
}
