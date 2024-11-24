#ifndef TABLE_H
#define TABLE_H

#include <iostream>

class Table {
public:
    Table(int width = 5, int height = 5) : _width(width), _height(height) {
        if(_width < 0) _width = 0;
        if(_height < 0) _height = 0;
    }

    bool isOnTable(int x, int y) const {
        return (x >= 0 && x < _width) && (y >= 0 && y < _height);
    }

    int getWidth() const { return _width; }
    int getHeight() const { return _height; }

private:
    int _width, _height;  // Dimensions of the table
};

#endif // TABLE_H
