#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N, Q;
        vector<vector<int>> questions;
        vector<vector<int>> pEdges[100001];
        int p[100001];
        int pSize[100001] = {};
    public:
        void readIn() {
            ifstream fin ("mootube.in");
            fin >> N >> Q;
            int a, b, c;
            for (int i = 1; i < N; i++) {
                fin >> a >> b >> c;
                pEdges[a].push_back({b, c});
                pEdges[b].push_back({a, c});
            }
            for (int i = 0; i < Q; i++) {
                fin >> a >> b;
                questions.push_back({a, b, i});
            }
            sort(questions.begin(), questions.end(), greater<vector<int>>());

            for (int i = 0; i < 100001; i++) { p[i] = i; pSize[i] = 1; }
        }

        int getRoot(int child) {
            int res = child;
            while (p[res] != res) res = p[res];
            int parent = p[child];
            while (child != res)  { p[child] = res; child = parent; parent = p[parent]; }
            return res;
        }

        void combine(int a, int b) {
            p[b] = a; pSize[a] += pSize[b];
            return;
        }

        void dfs(int key, int k, int parent, vector<vector<int>>& pE) {
            int pa = getRoot(key);
            if (pa == parent) return;
            combine(parent, pa);
            for (auto i: pEdges[pa]) {
                if (i[1] >= k) dfs(i[0], k, parent, pE);
                else pE.push_back({i[0], i[1]});
            }
            return;
        }

        void main() {
            ofstream fout ("mootube.out");
            readIn();
            vector<vector<int>> ans;
            for (int i = 0; i < questions.size(); i++) {
                int pa = getRoot(questions[i][1]); int k = questions[i][0];

                vector<vector<int>> pHolder;
                for (auto i: pEdges[pa]) {
                    if (i[1] >= k) dfs(i[0], k, pa, pHolder);
                    else pHolder.push_back({i[0], i[1]});
                }
                pEdges[pa] = pHolder;

                //cout << pSize[pa]-1 << endl;
                ans.push_back({questions[i][2], pSize[pa]-1});
            }   

            sort(ans.begin(), ans.end());
            for (auto i: ans) {
              //  cout << i[1] << endl;
                fout << i[1] << endl;
            }
        }

};

int main() {
    Solution s;
    s.main();
}