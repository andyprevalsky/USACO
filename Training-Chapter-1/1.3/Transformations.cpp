/*
    ID: andypre1
    LANG: C++11
    PROB: transform
*/


#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    private:
        int res;
        int N;
        vector<vector<char> > input;
        vector<vector<char> > output;
    public:
        vector<vector<char>> rotate90(vector<vector<char>>& input) {
            vector<vector<char>> out = input;
            for (int i = 0; i < out[0].size()/2; i++) {
                int startRow = i;
                int endRow = out[0].size()-i-1;
                for (int j = i; j < endRow; j++) {
                    char temp = out[startRow][j];                    
                    out[startRow][j] = out[out[0].size()-1-j][startRow];
                    out[out[0].size()-1-j][startRow] = out[endRow][out[0].size()-1-j];
                    out[endRow][out[0].size()-1-j] = out[j][endRow];
                    out[j][endRow] = temp;

                }
            }
            return out;
        }

        vector<vector<char>> reflection(vector<vector<char>>& input) {
            vector<vector<char>> out = input;
            for (int i = 0; i < out.size(); i++) {
                for (int j = 0; j < out[0].size()/2; j++) {
                    char temp = out[i][j];
                    out[i][j] = out[i][out[0].size()-1-j];
                    out[i][out[0].size()-1-j] = temp;
                }
            }
            return out;
        }

        bool isSame(vector<vector<char>>& c1, vector<vector<char>>& c2) {
            for (int i = 0; i < c1.size(); i++) {
                for (int j = 0; j < c1[0].size(); j++) {
                    if (c1[i][j] != c2[i][j]) return false;
                }
            }
            return true;
        }

        void main() {
            ifstream fin ("transform.in");
            ofstream fout ("transform.out");
            fin >> N;
            char c;
            for (int k = 0; k < 2; k++) {
                for (int j = 0; j < N; j++) {
                    vector<char> row;
                    for (int i = 0; i < N; i++) {
                        fin >> c;   
                        row.push_back(c);
                    }
                    if (k == 0) input.push_back(row);
                    else output.push_back(row);
                }
            }

            vector<vector<char>> out = reflection(input);
            vector<vector<char>> r1 = rotate90(input);
            vector<vector<char>> r2 = rotate90(r1);
            vector<vector<char>> r3 = rotate90(r2);
            vector<vector<char>> ref = reflection(input);
            vector<vector<char>> rr1 = rotate90(ref);
            vector<vector<char>> rr2 = rotate90(rr1);
            vector<vector<char>> rr3 = rotate90(rr2);

            if (isSame(output, r1)) fout << 1 << endl;
            else if (isSame(output, r2)) fout << 2 << endl;
            else if (isSame(output, r3)) fout << 3 << endl;
            else if (isSame(output, ref)) fout << 4 << endl;
            else if (isSame(output, rr1)) fout << 5 << endl;
            else if (isSame(output, rr2)) fout << 5 << endl;
            else if (isSame(output, rr3)) fout << 5 << endl;
            else if (isSame(output, input)) fout << 6 << endl;
            else fout << 7 << endl;
            return;

        }
};

int main() {
    Solution s;
    s.main();
}