#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {
    private:
        int A, B, n, m;
        int hSet = 0;
        int vSet = 0;
        int prehSet = 0;
        int prevSet = 0;
        int vConnected = 0;
        int hConnected = 0;
        vector<int> hEdges;
        vector<int> vEdges;
        vector<vector<int>> edges; //first pos is length of edge, second pos is 1 for v and 0 for h
    public:
        void prepData() {
            ifstream fin ("fencedin.in");
            fin >> A >> B >> n >> m;
            int x;
            vEdges.push_back(0);
            for (int i = 0; i < n; i++) {
                fin >> x;
                vEdges.push_back(x);
            }
            vEdges.push_back(A);

            sort(vEdges.begin(), vEdges.end());
            int pI;

            for (auto i: vEdges) {
                if (i != 0) edges.push_back({i-pI, 1});
                pI = i;

            }

            hEdges.push_back(0);
            for (int i = 0; i < m; i++) {
                fin >> x;
                hEdges.push_back(x);
            }
            hEdges.push_back(B);

            sort(hEdges.begin(), hEdges.end());

            for (auto i: hEdges) {
                if (i != 0) edges.push_back({i-pI, 0});
                pI = i;
            }

            sort(edges.begin(), edges.end());
            
        } // evey time a vertical row is connect to another vertical row change the amount of edges in all horizontal rows that needs to be removed by -1
          // and vice versa

        void main() {
            prepData();
            ofstream fout ("fencedin.out");

            long long res = 0;
            for (auto i: edges) {
                if (i[1] == 1) {
                    long long edgesNeeded = (m - (hConnected < 1 ? 0 : hConnected-1));
                    // cout << "EdgesNeeded: " << edgesNeeded << endl;
                    // cout << "EdgeVal: " << i[0] << endl;
                    if (edgesNeeded > 0) res += edgesNeeded*i[0];
                    hConnected = hSet;
                    if (hSet > 0) vConnected++;
                    vSet++;
                } else {
                    long long edgesNeeded = (n - (vConnected < 1 ? 0 : vConnected-1));
                    // cout << "EdgesNeeded: " << edgesNeeded << endl;
                    // cout << "EdgeVal: " << i[0] << endl;
                    if (edgesNeeded > 0) res += edgesNeeded*i[0];
                    if (vSet > 0) hConnected++;
                    vConnected = vSet;
                    hSet++;
                }
                // cout << "Hset: " << hSet << endl;
                // cout << "Vset: " << vSet << endl;
                // cout << "Hconnected: " << hConnected << endl;
                // cout << "Vconnected: " << vConnected << endl;
                // cout << " --------------- " << endl << endl;
            }

            fout << res << endl;
        }
};

int main() {
    Solution s;
    s.main();
}