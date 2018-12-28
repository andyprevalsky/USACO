#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define INF 0x3FFFFFFFFFFFFFFFLL

class Solution {
    private:
        int N;
        pair<string, vector<int>>  edges[100000];
        int memo[100000] = {};
        int numLeaves[100000];
        long long res = INF;
    public:
        void prepData() {
            ifstream fin ("dirtraverse.in");
            fin >> N; string s; int a, b;
            for (int i = 0; i < N; i++) {
                fin >> s; fin >> a; edges[i].first = s;
                for (int j = 0; j < a; j++) {
                    fin >> b; b--;
                    edges[i].second.push_back(b); 
                    edges[b].second.push_back(i);
                }
            }
        }

        int getLeaves(int root) {
            if (memo[root] == 1) return 0;
            memo[root] = 1;
            int total = 0;
            for (auto& e: edges[root].second) {
                total += getLeaves(e);
            }
            numLeaves[root] = total;
            if (total == 0) return 1;
            return total;
        }

        long long getBase(int root) {
            memo[root] = 1;
            long long total = 0;
            for (auto& e: edges[root].second) {
                if (memo[e] != 1) {
                    if (numLeaves[e] == 0) total += edges[e].first.size();   
                    else {
                        total += numLeaves[e]*(edges[e].first.size()+1) + getBase(e);
                    }
                }
            }
            return total;
        }

        void greed(int root, long long currV) {
            memo[root] = 1;
            res = min(currV, res);
            for (auto& e: edges[root].second) {
                if (memo[e] == 1) continue;
                int nextAdds = (numLeaves[0]-numLeaves[e])*3; 
                int nextSubs = numLeaves[e]*(edges[e].first.size()+1);
                if (nextSubs > nextAdds) greed(e, currV-nextSubs+nextAdds);
            }
            return;
        }

        void main() {
            prepData();
            ofstream fout ("dirtraverse.out");
            getLeaves(0);
            for (int i = 0; i < 100000; i++) memo[i] = 0;
            
            long long base = getBase(0);
            for (int i = 0; i < 100000; i++) memo[i] = 0;

            greed(0, base);
            fout << res << endl;
        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}