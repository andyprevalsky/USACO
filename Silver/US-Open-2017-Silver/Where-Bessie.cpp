#include <fstream>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
    private:
        int N;
        int total = 0;
        struct VectorHash {
            size_t operator()(const std::vector<int>& v) const {
                hash<int> hasher;
                size_t seed = 0;
                for (int i : v) {
                    seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
                }
                return seed;
            }
        };
        vector<vector<int> > seen;
        vector<vector<char> > board;

    public: 
        bool getValidity(vector<int>& p1, vector<int>& p2) {
            for (int i = 0; i < seen.size(); i++) {
                if (seen[i][0] <= p1[0] && seen[i][1] <= p1[1] && seen[i][2] >= p2[0] && seen[i][3] >= p2[1]) return false;
            }
            return true;
        }

        int dfs(vector<int>& pos, vector<int>& p1, vector<int>& p2, vector<vector<int>>& memo) {
            if (memo[pos[0]][pos[1]] == 1) return 0;
            int count = 1;
            memo[pos[0]][pos[1]] = 1;
            int rbound = p2[1]+1;
            int ubound = p2[0]+1;
            if ((pos[0] + 1 < ubound) && (board[pos[0]+1][pos[1]] == board[pos[0]][pos[1]])) {
                vector<int> next;
                next.push_back(pos[0]+1);
                next.push_back(pos[1]);
                count += dfs(next, p1, p2, memo);
            }
            if ((pos[1] + 1 < rbound) && (board[pos[0]][pos[1]+1] == board[pos[0]][pos[1]])) {
                vector<int> next;
                next.push_back(pos[0]);
                next.push_back(pos[1]+1);
                count += dfs(next, p1, p2, memo);
            }
            if ((pos[1] - 1 >= p1[1]) && (board[pos[0]][pos[1]-1] == board[pos[0]][pos[1]])) {
                vector<int> next;
                next.push_back(pos[0]);
                next.push_back(pos[1]-1);
                count += dfs(next, p1, p2, memo);
            }
            if ((pos[0] - 1 >= p1[0]) && (board[pos[0]-1][pos[1]] == board[pos[0]][pos[1]])) {
                vector<int> next;
                next.push_back(pos[0]-1);
                next.push_back(pos[1]);
                count += dfs(next, p1, p2, memo);
            }
            return count;
        }

        int getColors(vector<int>& p1, vector<int>& p2) { 
            vector<char> colors;
            int count = 0;
            for (int i = p1[0]; i < p2[0]+1; i++) {
                for (int j = p1[1]; j < p2[1]+1; j++) {
                    char color = board[i][j];
                    if (find(colors.begin(), colors.end(), color) == colors.end()) {
                        colors.push_back(color);
                        count += 1;
                    }
                }
            }
            return count;
        }

        vector<vector<int> >getPP(int area) {
            vector<vector<int> > res;
                for (int i = 1; i <= area; i++) {
                    if (area % i == 0)
                        res.push_back({i, area/i});
                }
            return res;
        }

        void WheresBessie() {
            ifstream fin ("where.in");
            ofstream fout ("where.out");
            fin >> N;
            char c;
            for (int i = 0; i < N; i++) {
                vector<char> row;
                for (int j = 0; j < N; j++) {
                    fin >> c;
                    row.push_back(c);
                }
                board.push_back(row);
            }

            vector<int> p1;
            vector<int> p2;
            vector<int> ij = {0, 0};
            bool oset;
            bool many;
            for (int area = N*N; area >= 3; area--) {
                vector<vector<int> > pps = getPP(area);
                for (int i = 0; i < pps.size(); i++) {
                    for (int x = 0; x < N; x++) {
                        for (int y = 0; y < N; y++) {
                            p1 = {x, y};
                            p2 = {p1[0]+pps[i][0]-1, p1[1]+pps[i][1]-1};
                            if (p2[0] >= N || p2[1] >= N) continue;
                            if (!getValidity(p1, p2)) continue;
                            if (getColors(p1, p2) != 2) continue;
                            vector<vector<int> > memo (N, vector<int>(N, 0));
                            unordered_map<char, int> cs;
                            oset = false;
                            many = false;
                            for (int e3 = p1[0]; e3 < p2[0]+1; e3++) {
                                for (int e4 = p1[1]; e4 < p2[1]+1; e4++) {
                                    ij[0] = e3;
                                    ij[1] = e4;
                                    char color = board[e3][e4];
                                    if (dfs(ij, p1, p2, memo)) {
                                        cs[color] += 1;
                                    } 
                                }
                            }
                            for (auto e = cs.begin(); e != cs.end(); e++) {
                                if (e->second == 1) oset = true;
                                if (e->second > 1) many = true;
                            }
                            if (oset && many) {
                                seen.push_back({p1[0], p1[1], p2[0], p2[1]});                 
                                total += 1;
                            }
                        }
                    }
                }
            }
            fout << total;
        }
};

int main() {
    Solution s;
    s.WheresBessie();
    return 0;
}