#include <iostream>
#include "boxstorage.h"
#include "boxgraph.h"

using namespace std;

int main(int argc, char *argv[])
{
    BoxStorage board;
    
    // Use this variable??
    int playerNumber;
    cin >> playerNumber;
    
    // Populate board
    board.MakeStorage(cin);
    
    // If edge exists that does not give adjacent boxes 3 edges, claim it!
    Coordinates coordinate = board.BestPosition();
    if ( (coordinate.X != -1) && (coordinate.Y != -1) ) {
        cout << coordinate.X << ' ' << coordinate.Y << endl;
    }
    else
    {
        BoxGraph graph(&board);

        graph.SelectBestMove();
    }
    
    return 0;
}
