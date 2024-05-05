/*

*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Pos
{
    int y;
    int x;
};

struct BlockInfo
{
    vector<Pos> pBlockGroup;
    int iRainbowNum;
    Pos pStandardBlock;

    bool operator<(const BlockInfo& input) const
    {
        if (pBlockGroup.size() == input.pBlockGroup.size())
        {
            if (iRainbowNum == input.iRainbowNum)
            {
                if (pStandardBlock.y == input.pStandardBlock.y)
                {
                    return pStandardBlock.x > input.pStandardBlock.x;
                }
                else
                {
                    return pStandardBlock.y > input.pStandardBlock.y;
                }
            }
            else
            {
                return iRainbowNum > input.iRainbowNum;
            }
        }
        else
        {
            return pBlockGroup.size() > input.pBlockGroup.size();
        }
    }
};


int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

const int MAX_SIZE = 20;
vector<vector<int>> iGrid(MAX_SIZE, vector<int>(MAX_SIZE));

int N, M;

vector<BlockInfo> findAllBlockGroups()
{
    vector<BlockInfo> bi_BlockGroupCandidates;
    vector<vector<int>> bVisited(MAX_SIZE, vector<int>(MAX_SIZE));

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (bVisited[r][c] || iGrid[r][c] == -1 || iGrid[r][c] == 8 || iGrid[r][c] == 0) continue;

            queue<Pos> q;
            q.push({r, c});
            vector<Pos> BlockGroup;
            int iNowNum = iGrid[r][c];
            int iRainbowBlockNum = 0;

            while (!q.empty())
            {
                Pos v = q.front();
                q.pop();

                if (bVisited[v.y][v.x]) continue;
                bVisited[v.y][v.x] = true;

                BlockGroup.push_back({v.y, v.x});
                if (iGrid[v.y][v.x] == 0) iRainbowBlockNum++;

                for (int dir = 0; dir < 4; dir++)
                {
                    int iTargetY = v.y + dy[dir];
                    int iTargetX = v.x + dx[dir];

                    if (iTargetY < 0 || iTargetY >= N || iTargetX < 0 || iTargetX >=N 
                    || iGrid[iTargetY][iTargetX] == -1
                    || iGrid[iTargetY][iTargetX] == 8
                    || (iGrid[iTargetY][iTargetX] != 0 && iGrid[iTargetY][iTargetX] != iNowNum)) continue;

                    q.push({iTargetY, iTargetX});
                }
            }

            if (BlockGroup.size() > 1)
            {
                sort(BlockGroup.begin(), BlockGroup.end(), [](const Pos& P1, const Pos& P2)
                {
                    return P1.x < P2.x;
                });

                sort(BlockGroup.begin(), BlockGroup.end(), [](const Pos& P1, const Pos& P2)
                {
                    return P1.y < P2.y;
                });

                Pos pStandardBlock;
                for (auto element : BlockGroup)
                {
                    if (iGrid[element.y][element.x] == 0) continue;
                    
                    pStandardBlock = element;
                    break;
                }

                bi_BlockGroupCandidates.push_back({BlockGroup, iRainbowBlockNum, pStandardBlock});
            }

            for (int r = 0; r < N; r++)
            {
                for (int c = 0; c < N; c++)
                {
                    if (iGrid[r][c] == 0) bVisited[r][c] = false;
                }
            }
        }
    }

    return bi_BlockGroupCandidates;
}

void removeBlocks(vector<Pos> pOptimalBlockGroup)
{
    for (auto block : pOptimalBlockGroup)
    {
        iGrid[block.y][block.x] = 8;
    }
}

void gravitateGrid()
{
    for (int c = 0; c < N; c++)
    {
        for (int r = N - 2; r >= 0; r--)
        {
            if (iGrid[r][c] == -1 || iGrid[r][c] == 8) continue;

            int y = r;
            while (y < N - 1)
            {
                if (iGrid[y + 1][c] != 8) break;
                y++;
            }

            if (y == r) continue;

            iGrid[y][c] = iGrid[r][c];
            iGrid[r][c] = 8;
        }
    }
}

void rotateGrid()
{
    vector<vector<int>> iTempGrid(N, vector<int>(N));

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            iTempGrid[r][c] = iGrid[c][N - r - 1];
        }
    }

    iGrid = iTempGrid;
}

void printGrid()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (iGrid[r][c] == -1) cout << iGrid[r][c] << " ";
            else cout << iGrid[r][c] << "  ";
        }

        cout << endl;
    }
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> M;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> iGrid[r][c];
        }
    }

    int iSumScore = 0;
    while (true)
    {
        vector<BlockInfo> bi_BlockGroupCandidates;
        bi_BlockGroupCandidates = findAllBlockGroups();
        if (bi_BlockGroupCandidates.size() == 0) break;

        sort(bi_BlockGroupCandidates.begin(), bi_BlockGroupCandidates.end());
        iSumScore += bi_BlockGroupCandidates[0].pBlockGroup.size() * bi_BlockGroupCandidates[0].pBlockGroup.size();

        //cout << "==== Start ====" << endl;
        //printGrid();
        removeBlocks(bi_BlockGroupCandidates[0].pBlockGroup);
        //cout << "==== Remove ====" << endl;
        //printGrid();
        gravitateGrid();
        //cout << "Score : " << iSumScore << endl;
        //cout << "==== Gravitate ====" << endl;
        //printGrid();
        rotateGrid();
        //cout << "==== Rotate ====" << endl;
        //printGrid();
        gravitateGrid();
        //cout << "==== Gravitate ====" << endl;
        //printGrid();
    }
    
    cout << iSumScore;

    return 0;
}
