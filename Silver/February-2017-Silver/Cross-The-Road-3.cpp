#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

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

int dfs(unordered_set<vector<int>, VectorHash > &roads, vector<vector<int> >&memo, vector<int>location, vector<vector<int> >& cows, int N) {
    if (memo[location[0]][location[1]] == 1) return 0;
    int count = cows[location[0]][location[1]];
    memo[location[0]][location[1]] = 1;
    for (int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if ((abs(i) + abs(j) == 2) || location[0]+i < 0 || location[0]+i >= N || location[1]+j < 0 || location[1]+j >= N || (i == 0 && j == 0))  continue;
            if (roads.find({location[0], location[1], location[0]+i, location[1]+j}) == roads.end() && roads.find({location[0]+i, location[1]+j, location[0], location[1]}) == roads.end()) {
                count += dfs(roads, memo, {location[0]+i, location[1]+j}, cows, N);
            }
        }
    }
    return count;
}

int main() {
    ifstream fin ("countcross.in");
    ofstream fout ("countcross.out");

    int N, K, R;
    fin >> N >> K >> R;

    unordered_set< vector<int>, VectorHash> roads;

    for (int i = 0; i < R; i++) {
        vector<int> road;
        int a;
        for(int j = 0; j < 4; j++) {
            fin >> a;
            road.push_back(a-1);
        }
        roads.insert(road);
    }


    vector< vector<int> > cows(N, vector<int>(N, 0));

    for (int i = 0; i < K; i++) {
        vector<int> cow;
        int x, y;
        fin >> x >> y;
        cows[x-1][y-1] = 1;
    }

    int total = 0;
    vector<int> pairs;
    vector< vector<int> > memo(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int pair = dfs(roads, memo, {i, j}, cows, N);
            if (pair != 0) pairs.push_back(pair);
        }
    }

    int psum = pairs[0];
    for (int i = 1; i < pairs.size(); i++) {
            total += psum * pairs[i];
            psum += pairs[i];
    }
    fout << total;
}