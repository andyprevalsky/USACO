#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;

vector< vector<int> > getChildren(vector<int> node, int l) {
    vector< vector<int> > children;
    vector< vector<int> >temp;
    for (int i = 1; i < 3; i++) {
        temp.push_back(vector<int>{i, 3-i});
        temp.push_back(vector<int>{-i, 3-i});
        temp.push_back(vector<int>{-i, -3+i});
        temp.push_back(vector<int>{i, -3+i});
    } 
    temp.push_back(vector<int>{3, 0});
    temp.push_back(vector<int>{0, 3});
    temp.push_back(vector<int>{-3, 0});
    temp.push_back(vector<int>{0, -3});   
    temp.push_back(vector<int>{1, 0});
    temp.push_back(vector<int>{0, 1});
    temp.push_back(vector<int>{-1, 0});
    temp.push_back(vector<int>{0, -1});
    
    
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i][0] + node[0] >= 0 && temp[i][0] + node[0] < l && temp[i][1] + node[1] >= 0 && temp[i][1] + node[1] < l)
            children.push_back(vector<int>{node[0] + temp[i][0], node[1] + temp[i][1]});
    }

    return children;
}

int main() {
    ofstream fout("visitfj.out");
    ifstream fin ("visitfj.in");
    int lineCount, T;
    fin >> lineCount >> T;
    int imax = std::numeric_limits<int>::max();

    vector< vector<int> > fields;
    int c;
    for (int i = 0; i < lineCount; i++) {
        vector<int> row;
        for (int j = 0; j < lineCount; j++) {
            fin >> c;
            row.push_back(c);
        }
        fields.push_back(row);
    }
    vector< vector<int> > shortestP(lineCount, vector<int>(fields[0].size(), imax));
    queue< vector<int> > q;
    q.push({0, 0});

    shortestP[0][0] = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            vector<int> node = q.front();
            q.pop();
            vector< vector<int> > nChilds = getChildren(node, lineCount);
            for (int j = 0; j < nChilds.size(); j++) {
                vector<int> n = nChilds[j];
                int pathVal = shortestP[node[0]][node[1]] + 3*T + fields[n[0]][n[1]];
                if (pathVal < shortestP[n[0]][n[1]]) {
                    shortestP[n[0]][n[1]] = pathVal;
                    q.push(n);
                }
            }
        }
    }
    
    int l = lineCount;
    vector<int> last = {shortestP[l-1][l-1], shortestP[l-1][l-2] + T, shortestP[l-2][l-1] + T, shortestP[l-3][l-1] + T*2, shortestP[l-1][l-3] + T*2, shortestP[l-2][l-2] + T*2};
    auto ans = min_element(last.begin(), last.end());
    fout << *ans;

    return 0;
}
