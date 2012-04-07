#ifndef BOXSTORAGE_H
#define BOXSTORAGE_H

#define GRID_HEIGHT 5
#define GRID_WIDTH  5

#define DIR_LEFT    0b0001
#define DIR_UP      0b0010
#define DIR_RIGHT   0b0100
#define DIR_DOWN    0b1000

class BoxStorage
{
public:
    BoxStorage();

private:
    short _storage[GRID_HEIGHT][GRID_WIDTH];

};

#endif // BOXSTORAGE_H
