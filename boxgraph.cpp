#include "boxgraph.h"

Chain::Chain() : _isLoop(-1)
{
}

void Chain::AddVertex(Coordinate &vertex)
{
    links.push_back(vertex);
}

bool Chain::isLoop() const
{
    if(_isLoop == -1)
    {
        //Calculate
    }

    return _isLoop;
}

bool Chain::isOpenLoop() const
{
    return (_loopType == 0);
}

bool Chain::isClosedLoop() const
{
    return (_loopType == 1);
}

int Chain::length() const
{
    if(links.size() > 0)
    {
        if(links[0].branch_point)
            return links.size()-1;
    }
    return links.size();
}

BoxGraph::BoxGraph() : _graph(NULL), _bestMoveX(-1), _bestMoveY(-1)
{
}

BoxGraph::BoxGraph(BoxStorage* bs) : _graph(bs), _bestMoveX(-1), _bestMoveY(-1)
{
}

void BoxGraph::SelectBestMove()
{
    //Seperate Chains
    bool visited[GRID_HEIGHT][GRID_WIDTH] = {{false}};

    for(int row = 0; row < GRID_HEIGHT; row++)
    {
        for(int col = 0; col < GRID_WIDTH; col++)
        {
            //Already visited
            if(visited[row][col])
                continue;

            //Not visited


            if(_graph->getLineCount(row, col) == 4)
            {
                //Taken square
                visited[row][col] = true;
            }
            else if(_graph->getLineCount(row, col) == 3)
            {
                //Start of a chain
                //MUST FOLLOW THIS CHAIN!!!!!!!!!!!!
            }
            else if(_graph->getLineCount(row, col) == 2)
            {
                //Chain found, point could be mid chain
            }
            else if(_graph->getLineCount(row, col) == 1)
            {

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
