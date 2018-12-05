#include <fstream>
#include <vector>
#include <deque>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <ctime>
#include <algorithm>
using namespace std;

class Solution {
    private:
        struct door {
            deque<int> cows;
            long long numCows = 0;
            long long walkVal = 0;
            int pos = 1;
            door(int p) {
                pos = p;
            }
        };
        int n, k;
        vector<int> rooms;
        vector<door*> doors;
    public:
        void prepData() {

            ifstream fin ("cbarn2.in");
            fin >> n >> k;
            int a;
            for (int i = 0; i < n; i++) {
                fin >> a;
                rooms.push_back(a);
            }

            set<int> rands;
            vector<int> js;
            for (int i = 0; i < k; i++) {
                int j = rand()%n;
                while (rands.find(j) != rands.end()) j = rand()%n;
                rands.insert(j);
                js.push_back(j);
            }
            sort(js.begin(), js.end());
            for (int i = 0; i < js.size(); i++) {
                door* b = new door(js[i]);
                doors.push_back(b);
            }
            for (int i = 0; i < doors.size(); i++) {
                door* currDoor = doors[i];
                int p = (currDoor->pos+1)%n;
                int multiplier = 1;
                while(p != doors[(i+1)%doors.size()]->pos) {
                    currDoor->cows.push_back(rooms[p]);
                    currDoor->numCows += rooms[p];
                    currDoor->walkVal += rooms[p]*multiplier;
                    p = (p+1)%n;
                    multiplier += 1;
                }
            }
        }
        
        void search() {
            while (1) {
                bool unchanged = true;

                for (int i = 0; i < k; i++) {
                    door* currDoor = doors[i];
                    door* rightDoor = doors[(i+1)%k];
                    door* leftDoor = doors[(i-1 == -1 ? k-1 : i-1)];
                    if ((currDoor->pos+1)%n != rightDoor->pos && (rooms[currDoor->pos]*(leftDoor->cows.size()+1) < currDoor->numCows)) { //adjust right if it makes smaller
                        int newLeft = rooms[currDoor->pos];
                        leftDoor->numCows += newLeft;
                        leftDoor->cows.push_back(newLeft);
                        leftDoor->walkVal += (leftDoor->cows.size()*newLeft);

                        currDoor->pos = (currDoor->pos+1)%n;    
                        currDoor->cows.pop_front();
                        currDoor->walkVal -= (currDoor->numCows);
                        currDoor->numCows -= rooms[currDoor->pos];
                        
                        unchanged = false;
                    }
                    if ((leftDoor->pos+1)%n != currDoor->pos && (currDoor->numCows + rooms[currDoor->pos] < leftDoor->cows.back()*leftDoor->cows.size())) { //check adjust curr door left
                        currDoor->cows.push_front(rooms[currDoor->pos]);
                        currDoor->numCows += rooms[currDoor->pos];
                        currDoor->walkVal += (currDoor->numCows);
                        currDoor->pos = (currDoor->pos-1 == -1 ? n-1 : currDoor->pos-1);

                        int lastSpot = leftDoor->cows.back();
                        leftDoor->walkVal -= (lastSpot*leftDoor->cows.size());
                        leftDoor->numCows -= lastSpot;
                        leftDoor->cows.pop_back();

                        unchanged = false;
                    }
                }

                if (unchanged) return;
            }
        }

        int main() {
            prepData();
            search();

            long long endWalkVal = 0;
            for (auto i: doors) {
                endWalkVal += i->walkVal;
            }
            return endWalkVal;
            
        }
};

int main() {
    ofstream fout ("cbarn2.out");
    srand(time(NULL));
    long long  min = 0x3FFFFFFFFFFFFFFFLL;
    for (int i = 0; i < 1000; i++) {
        Solution s;
        long long a = s.main();
        if (a < min) min = a;
    }
    fout << min << endl;
}