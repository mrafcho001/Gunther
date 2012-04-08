#include "boxgraph.h"
#include <iostream>


BoxGraph::BoxGraph() : _graph(NULL), _bestMoveX(-1), _bestMoveY(-1)
{
}

BoxGraph::BoxGraph(BoxStorage* bs) : _graph(bs), _bestMoveX(-1), _bestMoveY(-1)
{
}

void BoxGraph::SelectBestMove()
{
    std::vector<Chain> chain3;
    //Determine if there are any 3 sides boxes:
    for(int row = 0; row < GRID_HEIGHT; row++)
    {
        for(int col = 0; col < GRID_WIDTH; col++)
        {
            if(_graph->getLineCount(row, col) == 3)
            {
                //Add 3 sided chain
                createChains(row, col);
                for(int i= 0; i < chains.size();i++)
                {
                    if(chains[i].position().x == col && chains[i].position().y == row)
                    {
                        chain3.push_back(chains[i]);
                    }
                }
                chains.clear();
            }
        }
    }
    if(chain3.size() > 0)
    {
        Coordinate move;
        int max_points = -1;
        //Choose one of 3 sided boxes
        for(int i = 0; i< chain3.size(); i++)
        {
            if(max_points < chain3[i].length())
            {
                move.x = chain3[i].position().x;
                move.y = chain3[i].position().y;
                move.branch_point = chain3[i].position().branch_point;
                max_points = chain3[i].length();
            }
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
                createChains(row, col);
            }
            else if(_graph->getLineCount(row, col) == 1)
            {
                //Shitfest
            }
        }
    }

    //Decide best chain?
    int best_chain_pos = -1;
    int best_chain_score = 10000;
    for(int i=0; i < chains.size(); i ++)
    {
        if(chains[i].length() < best_chain_score)
        {
            best_chain_score = chains[i].length();
            best_chain_pos = i;
        }
    }

    std::cout << "Chain size: " << chains.size() << std::endl;
    _bestMoveX = chains[best_chain_pos].position().x;
    _bestMoveY = chains[best_chain_pos].position().y;

    _bestMoveDir = chains[best_chain_pos].direction();

    if(_bestMoveDir==SIDE_LEFT)
    {
        _bestMoveDir = SIDE_RIGHT;
    }
    else if(_bestMoveDir == SIDE_RIGHT)
    {
        _bestMoveDir = SIDE_LEFT;
    }
    else if(_bestMoveDir == SIDE_DOWN)
    {
        _bestMoveDir = SIDE_UP;
    }
    else if(_bestMoveDir == SIDE_UP)
    {
        _bestMoveDir = SIDE_DOWN;
    }

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
void BoxGraph::createChains(int row, int col)
{
    Chain chain;
    Coordinate point(col, row);
    short mask = _graph->getMask(row, col);
    if(_graph->getLineCount(row, col) >= 2)
    {
        point.branch_point = false;
        chain.AddVertex(point);
        if((mask&SIDE_LEFT) == 0 && col > 0 && !visited[row][col-1])
            visit(row, col-1, &chain);
        if((mask&SIDE_RIGHT) == 0 && col+1 < GRID_WIDTH && !visited[row][col+1])
            visit(row, col+1, &chain);
        if((mask&SIDE_DOWN) == 0 && row+1 < GRID_HEIGHT && !visited[row+1][col])
            visit(row+1, col, &chain);
        if((mask&SIDE_UP) == 0 && row > 0 && !visited[row-1][col])
            visit(row-1, col, &chain);
    }
    else if(_graph->getLineCount(row, col) == 1)
    {
        if((mask&SIDE_LEFT) == 0 && col >= 0 && !visited[row][col-1])
        {
            Chain chain2;
            Coordinate co(col, row);
            co.branch_point = true;
            chain2.AddVertex(co);
            visit(row, col-1, &chain2);
            if(chain2.length() > 1)
            {
                if(!chain2.isLoop())
                    chain.removeFront();
                chains.push_back(chain2);
            }
        }
        if((mask&SIDE_RIGHT) == 0 && col+1 < GRID_WIDTH && !visited[row][col+1])
        {
            Chain chain2;
            Coordinate co(col, row);
            co.branch_point = true;
            chain2.AddVertex(co);
            visit(row, col+1, &chain2);
            if(chain2.length() > 1)
            {
                if(!chain2.isLoop())
                    chain.removeFront();
                chains.push_back(chain2);
            }
        }
        if((mask&SIDE_DOWN) == 0 && row+1 < GRID_HEIGHT && !visited[row+1][col])
        {
            Chain chain2;
            Coordinate co(col, row);
            co.branch_point = true;
            chain2.AddVertex(co);
            visit(row+1, col, &chain2);
            if(chain2.length() > 1)
            {
                if(!chain2.isLoop())
                    chain.removeFront();
                chains.push_back(chain2);
            }
        }
        if( (mask&SIDE_UP)==0 && row > 0 && !visited[row-1][col])
        {
            Chain chain2;
            Coordinate co(col, row);
            co.branch_point = true;
            chain2.AddVertex(co);
            visit(row-1, col, &chain2);
            if(chain2.length() > 1)
            {
                if(!chain2.isLoop())
                    chain.removeFront();
                chains.push_back(chain2);
            }
        }
    }
}

void BoxGraph::visit(int row, int col, Chain *chain)
{
    visited[row][col] = true;

    Coordinate co;
    co.x = col;
    co.y = row;
    if(_graph->getLineCount(row, col) <= 1)
    {
        co.branch_point = true;
        if(chain->length() > 0)
        {
            createChains(row, col);
            return;
        }
    }
    else
        co.branch_point = false;

    chain->AddVertex(co);

    short mask = _graph->getMask(row, col);

    if((mask&SIDE_LEFT) == 0 && col >= 0 && !visited[row][col-1])
    {
        visit(row, col-1, chain);
    }
    if((mask&SIDE_RIGHT) == 0 && col+1 < GRID_WIDTH && !visited[row][col+1])
    {
        visit(row, col+1, chain);
    }
    if((mask&SIDE_DOWN) == 0 && row+1 < GRID_HEIGHT && !visited[row+1][col])
    {
        visit(row+1, col, chain);
    }
    if( (mask&SIDE_UP)==0 && row > 0 && !visited[row-1][col])
    {
        visit(row-1, col, chain);
    }
}

void BoxGraph::initVisited()
{
    for(int i= 0; i < GRID_HEIGHT; i++)
    {
        for( int j = 0; j < GRID_WIDTH; j++)
        {
            visited[i][j] = false;
        }
    }
}

int BoxGraph::BestMoveDir() const
{
    return _bestMoveDir;
}
