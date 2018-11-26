#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    private:
        int minBoots;
        int numTiles, numBoots;
        vector<int> tiles;
        vector<vector<int>> boots;
        vector<int> memo;

    public:
        void readIn() {
            ifstream fin ("snowboots.in");
            fin >> numTiles >> numBoots;
            int a, b;
            for (int i = 0; i < numTiles; i++) {
                fin >> a;
                tiles.push_back(a);
                memo.push_back(numBoots+1);
            }
            for (int i = 0; i < numBoots; i++) {
                fin >> a >> b;
                boots.push_back({a, b});
            }
            minBoots = numBoots+1;
        }
        void dfs(int currBoot, int currTile) {
            if (currTile == tiles.size()-1) {
                if (currBoot < minBoots) minBoots = currBoot;
                return;
            }

            if (currBoot == numBoots) return;
            if (boots[currBoot][0] < tiles[currTile]) {
                dfs(currBoot+1, currTile);
                return;
            }
            
            if (memo[currTile] > currBoot) memo[currTile] = currBoot;

            int tileDepth = tiles[currTile];
            int bootReach = boots[currBoot][1];
            int bootHeight = boots[currBoot][0];

            
            for (int i = 1; i <= boots[currBoot][1]; i++) {
                if (currTile+i < tiles.size() && tiles[currTile+i] <= boots[currBoot][0] && memo[currTile+i] > currBoot) dfs(currBoot, currTile+i);
            }
            
            dfs(currBoot+1, currTile);
        }

        void main() {
            readIn();
            ofstream fout ("snowboots.out");
            dfs(0, 0);
            fout << minBoots;
        }
};

int main() {
    Solution s;
    s.main();
}