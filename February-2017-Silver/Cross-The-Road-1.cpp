#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <map>
#include <limits>

using namespace std;

int main() {
    ifstream fin ("helpcross.in");
    ofstream fout ("helpcross.out");
    int C, N;
    fin >> C >> N;
    vector<int> chickens;
    int cTime;

    vector< vector<int> > pool;
    for (int i = 0; i < C; i++) {
        fin >> cTime;
        pool.push_back({cTime, 20001});
    }

    int i1, i2;
    for (int i = 1; i < N+1; i++) {
        fin >> i1 >> i2;
        pool.push_back({i1, 1, i, i2});
        pool.push_back({i2, 999999, -i});
    }

    sort(pool.begin(), pool.end());
    unordered_map<int, int> ids;
    map<int, vector<int>> EndToId;
    int total = 0;
    for (int i = 0; i < pool.size(); i++) {
        if (pool[i][1] != 20001) { //if not a chicken
            if (pool[i][2] > 0) { //if begining of interval then add id to the live pool and add the end to a map
                ids[pool[i][2]] = 1;
                EndToId[pool[i][3]].push_back(pool[i][2]);
            }
            else { //if end of interval then erase id
                ids.erase(-pool[i][2]);
                if (EndToId.find(pool[i][0]) != EndToId.end())
                    EndToId[pool[i][0]].pop_back();
                    if (EndToId[pool[i][0]].size() == 0)
                        EndToId.erase(pool[i][0]);
            }
        } else if (EndToId.size() != 0) {
            ids.erase(EndToId.begin()->second.back());
            EndToId.begin()->second.pop_back();
            if (EndToId.begin()->second.size() == 0)
                EndToId.erase(EndToId.begin()->first);
            total += 1;
        }
    }
    fout << total;
}