#include <fstream>
#include <vector>
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N, M;
        vector<int> edges[200001];
        stack<int> s;
        int numEdges = 0;
        int parent[200000] = {};
    public:
        void prepData() {
            ifstream fin ("closing.in");
            fin >> N >> M;
            int a, b;
            for (int i = 0; i < M; i++) {
                fin >> a >> b;
                edges[a].push_back(b);
                edges[b].push_back(a);
            }

            for (int i = 0; i < N; i++) {
                fin >> a;
                s.push(a);
            }
        }

        int find(int n) {
            int res = n;
            while (parent[res] != res) res = parent[res];
            int m; 
            while (parent[n] != n) {
                m = parent[n];
                parent[n] = res;
                n = m;
            } 
            return res; 
        }

        void Union(int x, int y) {
            if (parent[y] == 0) return;
            int xRoot = find(x);
            int yRoot = find(y);
            if (xRoot == yRoot) return;
            numEdges += 1;
            parent[xRoot] = yRoot;
        }

        void main() {
            prepData();
            ofstream fout ("closing.out");

            vector<string> res;
            int count = 0;
            while(!s.empty()) {
                int house = s.top(); s.pop(); count++;
                parent[house] = house;
                for (auto i: edges[house]) {
                    Union(house, i);
                }
                if (numEdges == count-1) res.push_back("YES");
                else res.push_back("NO");
            }

            for (auto i = res.rbegin(); i != res.rend(); i++) {
                fout << *i << endl;
            }
        }
};

int main() {
    Solution s;
    s.main();
}