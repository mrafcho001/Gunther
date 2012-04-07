#include "boxgraph.h"



BoxGraph::BoxGraph() : _graph(NULL), _bestMoveX(-1), _bestMoveY(-1)
{
}

BoxGraph::BoxGraph(BoxStorage* bs) : _graph(bs), _bestMoveX(-1), _bestMoveY(-1)
{
}

void BoxGraph::SelectBestMove()
{
    //Determine if there are any 3 sides boxes:
    for(int row = 0; row < GRID_HEIGHT; row++)
    {
        for(int col = 0; col < GRID_WIDTH; col++)
        {
            if(_graph->getLineCount(row, col) == 3)
            {
                //Add 3 sided chain
                Chain newChain;
                createFollowChain(row, col, newChain);
                chains.push_back(newChain);
            }
        }
    }
    if(chains.size() > 0)
    {
        Coordinate move;
        int max_points = -1;
        //Choose one of 3 sided boxes
        for(int i = 0; i< chains.size(); i++)
        {
            move = chains[i];
            max_points = chainPointCount();
        }

        _bestMoveX = move.x;
        _bestMoveY = move.y;
        return;
    }

    // else find best move

    //Seperate Chains
    initVisited();

    for(int row = 0; row < GRID_HEIGHT; row++)
    {
        for(int col = 0; col < GRID_WIDTH; col++)
        {
            //Already visited
            if(visited[row][col])
                continue;

            //Not visited

            visited[row][col] = true;

            if(_graph->getLineCount(row, col) == 3)
            {
                //Start of a chain
                //MUST FOLLOW THIS CHAIN!!!!!!!!!!!!
                //SHould be done already
            }
            else if(_graph->getLineCount(row, col) == 2)
            {
                std::vector<Chain> newChains = createChains(row, col);

                for(int i = 0; i < newChains.size(); i++)
                    chains.push_back(newChains[i]);
            }
            else if(_graph->getLineCount(row, col) == 1)
            {
                //Shitfest
            }
        }
    }

    //Decide best chain?
}

int BoxGraph::BestMoveX() const
{
    return 0;
}

int BoxGraph::BestMoveY() const
{
    return 0;
}

std::ostream &operator<<(std::ostream& out, const BoxGraph &bg)
{
    (void) bg;
    out << "Answer: 0 0";
    return out;
}
