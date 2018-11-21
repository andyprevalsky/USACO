#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

//list of barns and their ids, check if all ids are the same to check if fully connected
//when adding a new barn change all connected barns to be the id of the lowest, touching, make new id if none avail



class Solution {
    private:
        int idCount = 1;
        int N, M;
        unordered_map<int, vector<int> > edges;
        unordered_map<int, int> ids;
        vector<int> removal;
        vector<string> answers;
    public:
        void readIn() {
            ifstream fin ("closing.in");
            fin >> N >> M;
            int a, b;
            for (int i = 0; i < M; i++) {
                fin >> a >> b;
                edges[a].push_back(b);
                edges[b].push_back(a);
            }
            for(int i = 0; i < N; i++) {
                fin >> a;
                removal.push_back(a);
            }
        }      

        void connect(int house, int minId) {
            if (ids.find(house) == ids.end() || ids[house] == minId) return;
            ids[house] = minId;
            for (auto i: edges[house]) {
                connect(i, minId);
            }
        }

        bool isConnected() {
            for (auto i: ids) {
                if (i.second != 1) return false;
            }
            return true;
        }
        void main() {
            readIn();
            ofstream fout ("closing.out");
            for (int i = removal.size()-1; i >= 0; i--) {
                int currHouse = removal[i];
                // loop through edges connecting to all avail nodes while also keeping track of min id
                int minId = 9999999;
                for (auto i: edges[currHouse]) { //find lowest id first
                    if (ids.find(i) != ids.end() && ids[i] < minId) minId = ids[i];
                }
                for (auto i: edges[currHouse]) {
                    connect(i, minId);
                }
                if ((minId) == 9999999) ids[currHouse] = idCount++;
                else ids[currHouse] = minId;
                if (isConnected()) answers.push_back("YES");
                else answers.push_back("NO");
            }

            for (auto i = answers.rbegin(); i != answers.rend(); i++) {
                fout << *i << endl;
            }
        }
};

int main() {
    Solution s;
    s.main();
}