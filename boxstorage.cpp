#include "boxstorage.h"

BoxStorage::BoxStorage()
{
}

void BoxStorage::MakeStorage(std::istream& cin)
{
    // Temporary store input data
    int tempStorage[2*GRID_HEIGHT+1][2*GRID_WIDTH+1];
    
    for (int i=0; i<(2*GRID_HEIGHT+1); i++) {
        for (int j=0; j<(2*GRID_WIDTH+1); j++) {
            cin >> tempStorage[i][j];
        }
    }
    
    // Fill _storage[][] and BoxCounts[][]
    for (int i=0; i<GRID_HEIGHT; i++) {
        for (int j=0; j<GRID_WIDTH; j++) {
            _storage[i][j] = 0b0000;
            BoxCounts[i][j] = 0;
            
            // Edge on left side
            if (tempStorage[2*i+1][2*j] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_LEFT;
                BoxCounts[i][j]++;
            }
            
            // Edge on up side
            if (tempStorage[2*i][2*j+1] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_UP;
                BoxCounts[i][j]++;
            }
            
            // Edge on right side
            if (tempStorage[2*i+1][2*j+2] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_RIGHT;
                BoxCounts[i][j]++;
            }
            
            // Edge on down side
            if (tempStorage[2*i+2][2*j+1] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_DOWN;
                BoxCounts[i][j]++;
            }
        }
    }
}

Coordinates BoxStorage::BestPosition()
{
    for (int i=0; i<GRID_HEIGHT; i++) {
        for (int j=0; i<GRID_WIDTH; j++) {
            // Box has fewer than 2 edges
            if (BoxCounts[i][j] < 2) {
                
                // No left side
                if (!(_storage[i][j] & SIDE_LEFT)) {
                    // Box on left has fewer than 2 edges
                    if ( (j==0) || ((j>0) && (BoxCounts[i][j-1]<2)) )
                    {
                        Coordinates value(2*i+1, 2*j);
                        return value;
                    }
                }
                
                // No up side
                if (!(_storage[i][j] & SIDE_UP)) {
                    // Upper box has fewer than 2 edges
                    if ( (i==0) || ((i>0) && (BoxCounts[i-1][j]<2)) )
                    {
                        Coordinates value(2*i, 2*j+1);
                        return value;
                    }
                }
                
                // No right side
                if (!(_storage[i][j] & SIDE_RIGHT)) {
                    // Box to right has fewer than 2 edges
                    if ( (j=GRID_WIDTH-1) || ((j<GRID_WIDTH-1) && (BoxCounts[i][j+1]<2)) ) {
                        Coordinates value(2*i+1, 2*j+2);
                        return value;
                    }
                }
                
                // No down side
                if (!(_storage[i][j] & SIDE_DOWN)) {
                    // Lower box has fewer than 2 edges
                    if ( (i=GRID_HEIGHT-1) || ((i<GRID_HEIGHT-1) && (BoxCounts[i+1][j]<2)) ) {
                        Coordinates value(2*i+2, 2*j+1);
                        return value;
                    }
                }
            }
        }
    }
    
    return Coordinates(-1, -1);  // No position
}

int BoxStorage::getLineCount(int x, int y)
{
    return BoxCounts[x][y];
}

short BoxStorage::getMask(int x, int y)
{
    return _storage[x][y];
}
