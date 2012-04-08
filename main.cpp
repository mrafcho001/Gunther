#include <iostream>
#include "boxstorage.h"
#include "boxgraph.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    BoxStorage board;

    ifstream inFile("sample.txt");
    if(!inFile.is_open())
    {
        cout << "SHIT WENT WERONG";
    }
    
    // Use this variable??
    int playerNumber;
    inFile >> playerNumber;
    
    // Populate board
    board.MakeStorage(inFile);
    
    // If edge exists that does not give adjacent boxes 3 edges, claim it!
    Coordinates coordinate = board.BestPosition();
    if ( (coordinate.X != -1) && (coordinate.Y != -1) ) {
        cout << coordinate.X << ' ' << coordinate.Y << endl;
    }
    else
    {
        BoxGraph graph(&board);

        graph.SelectBestMove();
        int x = graph.BestMoveX();
        int y = graph.BestMoveY();

        int col = x*2+1;
        int row = y*2+1;

        if(graph.BestMoveDir() == SIDE_LEFT)
            col --;
        if(graph.BestMoveDir() == SIDE_RIGHT)
            col++;
        if(graph.BestMoveDir() == SIDE_UP)
            row --;
        if(graph.BestMoveDir() == SIDE_DOWN)
            row++;

        cout << row << " " << col << endl;
    }
    
    return 0;
}
