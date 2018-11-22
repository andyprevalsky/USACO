#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N;
        int max1 = 0;
        int max2 = 0;
        struct VectorHash {
            size_t operator()(const std::vector<int>& v) const {
                std::hash<int> hasher;
                size_t seed = 0;
                for (int i : v) {
                    seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                }
                return seed;
            }
        };
        vector<vector<int> > grid;
        vector<vector<int> > neighborMemo;
        unordered_map<vector<int>, int, VectorHash> islandSize;
        unordered_map<vector<int>, unordered_map<int, unordered_set<int> >, VectorHash> touchingIslands; //adjaceny list of islands
        unordered_map<int, int>numIslands; //takes a cowId as the input and outputs the number of islands so far;
        unordered_map<int, unordered_map<vector<int>, int, VectorHash> > coordinates; //take in a cowId and gives a hasmap of all coordinates with necessar attributes 
    public:
        void readIn() {
            ifstream fin ("multimoo.in");
            fin >> N;
            int a;
            for (int i = 0; i < N; i++) {
                vector<int> row;
                vector<int> nRow;
                for (int j = 0; j < N; j++) {
                    fin >> a;
                    row.push_back(a);
                    nRow.push_back(0);
                }
                neighborMemo.push_back(nRow);
                grid.push_back(row);
            }

        }

        int dfs1(int cowId, int id, vector<int> pos) {
            if (pos[0] < 0 || pos[0] >= N || pos[1] < 0 || pos[1] >= N) return 0; //out of bounds
            if (grid[pos[0]][pos[1]] != cowId) return 0;
            if (coordinates[cowId].find(pos) != coordinates[cowId].end()) return 0; //already visited
            coordinates[cowId][pos] = id; //mark as visited

            return (1 + dfs1(cowId, id, {pos[0]+1, pos[1]}) + dfs1(cowId, id, {pos[0]-1, pos[1]}) + dfs1(cowId, id, {pos[0], pos[1]+1}) + dfs1(cowId, id, {pos[0], pos[1]-1}) );

        }

        void dfsSetIds(vector<int>pos, int cowId, int id) {
            if (grid[pos[0]][pos[1]] != cowId) return;
            if (neighborMemo[pos[0]][pos[1]] == 1) return;
            neighborMemo[pos[0]][pos[1]] = 1;

            vector<vector<int> > checks = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto i: checks) {
                int currX = pos[0] + i[0];
                int currY = pos[1] + i[1];
                if (currX < 0 || currX >= N || currY < 0 || currY >= N) continue;
                dfsSetIds({currX, currY}, cowId, id);
                int neighCowId = grid[currX][currY];
                if (neighCowId == cowId) continue;
                int neighIslandId = coordinates[neighCowId][{currX, currY}];
                touchingIslands[{cowId, id}][neighCowId].insert(neighIslandId);
            }
        }


        int dfs2(vector<int> currIsland, int cowId1, int cowId2, unordered_set<vector<int>, VectorHash>& dfs2Memo){
            if (dfs2Memo.find(currIsland) != dfs2Memo.end()) return 0;
            dfs2Memo.insert(currIsland);
            int count = islandSize[currIsland];
            for (auto i: touchingIslands[currIsland][cowId2]) {
                count += dfs2({cowId2, i}, cowId2, cowId1, dfs2Memo);
            }
            touchingIslands[currIsland].erase(cowId2);
            return count;
        } //need to dfs through the island ids

        void main() {
            readIn();
            ofstream fout ("multimoo.out");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int size = dfs1(grid[i][j], numIslands[grid[i][j]], {i, j});
                    if (size != 0) {
                        islandSize[{grid[i][j], numIslands[grid[i][j]]}] = size;
                        numIslands[grid[i][j]]++;
                        if (size > max1) max1 = size;
                    }
                }
            }

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    dfsSetIds({i, j}, grid[i][j], coordinates[grid[i][j]][{i, j}]);
                }
            }

            for (auto i: touchingIslands) {
                for (auto j: i.second) {
                    unordered_set<vector<int>, VectorHash> dfs2Memo;
                    int size = dfs2(i.first, i.first[0], j.first, dfs2Memo);
                    if (size > max2) max2 = size;
                }
            }

            fout << max1 << endl << max2 << endl;

        }
};

int main() {
    Solution s;
    s.main();
}