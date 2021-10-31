#include<iostream>
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<cmath>
#include<climits>
#include<string>

using namespace std;

vector<vector<int>> final = {{1, 2, 3},
                             {4, 5, 6},
                             {7, 8, 0}};

void UniformCostSearch(vector<vector<int>> problem){
    queue<vector<vector<int>>> UCS;
    queue<string> move;
    // vector<vector<int>> temp = problem;

    int i = 0;
    int j = 0;

    
    
    UCS.push(problem);
    move.push("null");
    while(!UCS.empty()){
        cout << "size: " << UCS.size() << endl;
        if(UCS.front() == final){
            cout << "found!" << endl;
            return;
        }
        // cout << " a" << endl;
        

        for(int x = 0; x < problem.size(); x++){
            for(int y = 0; y < problem[0].size(); y++){
                if(UCS.front()[x][y] == 0){
                    i = x;
                    j = y;
                    break;
                }
            }
        }
        // if(i == 0 && j == 0) cout << "aaaaaaaAHHHHHHHHHHHHHHHHHHHHHHHHH -----------------------------------------------------------------------" << endl;
        // cout << " b" << endl;
        // cout << "i: " << i << " j: " << j << endl;

        if(i < problem.size()-1 && move.front() != "down"){
            vector<vector<int>> temp = UCS.front();
            swap(temp[i+1][j], temp[i][j]);
            UCS.push(temp);
            move.push("up");
        }
        // cout << " c" << endl;
        if(i > 0 && move.front() != "up"){
            vector<vector<int>> temp = UCS.front();
            swap(temp[i-1][j], temp[i][j]);
            UCS.push(temp);
            move.push("down");
        }
        // cout << " d" << endl;
        if(j < problem[0].size()-1 && move.front() != "left"){
            vector<vector<int>> temp = UCS.front();
            swap(temp[i][j+1], temp[i][j]);
            UCS.push(temp);
            move.push("right");
        }
        // cout << " e" << endl;
        if(j > 0 && move.front() != "right"){
            vector<vector<int>> temp = UCS.front();
            swap(temp[i][j-1], temp[i][j]);
            UCS.push(temp);
            move.push("left");
        }
        // cout << " f" << endl;

        for(auto it1: UCS.front()){
            for(auto it2: it1){
                cout << it2 << " ";
            }
            cout << endl;
        }
        UCS.pop();
        move.pop();
    }



}

int main(){
    vector<vector<int>> inital = {{1, 3, 6},
                                  {5, 0, 2},
                                  {4, 7, 8}};

    UniformCostSearch(inital);

    return 0;
}