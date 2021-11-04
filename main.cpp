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

        // for(auto it1: UCS.front()){
        //     for(auto it2: it1){
        //         cout << it2 << " ";
        //     }
        //     cout << endl;
        // }
        UCS.pop();
        move.pop();
    }
}

struct Node{
    int f_n;
    int h_n;
    int g_n;
    vector<vector<int>> state;
    string movement;
    Node(int hn, int gn, vector<vector<int>> temp, string str){
        this->h_n = hn;
        this->g_n = gn;
        this->f_n = h_n + g_n;
        this->state = temp;
        this->movement = str;
    }
};

struct node_cmp
{
   bool operator()( const Node* a, const Node* b ) const 
   {
    return a->f_n > b->f_n;
   }
};

int getHn(vector<vector<int>> pb){
    int answ = 0;
    for(int i = 0; i < pb.size(); i++){
        for(int j = 0; j < pb.size(); j++){
            if(pb[i][j] != 0 && pb[i][j] != final[i][j]) answ++;
        }
    }
    return answ;
}

void AStar(vector<vector<int>> problem){
    priority_queue<Node*, vector<Node*>, node_cmp> pq;
    queue<string> move;

    pq.push(new Node(-1, -1, problem, ""));

    int i = 0;
    int j = 0;

    while(!pq.empty()){
        if(pq.top()->state == final){
            cout << "found at size: " << pq.size() << "!" << endl;
            return;
        }
        Node* nd = pq.top();
        // cout << "size: " << pq.size() << endl;
        // for(auto it1: nd->state){
        //     for(auto it2: it1){
        //         cout << it2 << " ";
        //     }
        //     cout << endl;
        // }
        pq.pop();

        for(int x = 0; x < nd->state.size(); x++){
            for(int y = 0; y < nd->state[0].size(); y++){
                if(nd->state[x][y] == 0){
                    i = x;
                    j = y;
                    break;
                }
            }
        }

        if(i < problem.size()-1 && nd->movement != "down"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i+1][j], temp[i][j]);
            pq.push(new Node(getHn(temp),nd->g_n+1, temp, "up"));
        }
        // cout << " c" << endl;
        if(i > 0 && nd->movement != "up"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i-1][j], temp[i][j]);
            pq.push(new Node(getHn(temp), nd->g_n+1, temp, "down"));
        }
        // cout << " d" << endl;
        if(j < problem[0].size()-1 && nd->movement != "left"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i][j+1], temp[i][j]);
            pq.push(new Node(getHn(temp), nd->g_n+1, temp, "right"));
        }
        // cout << " e" << endl;
        if(j > 0 && nd->movement != "right"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i][j-1], temp[i][j]);
            pq.push(new Node(getHn(temp), nd->g_n+1, temp, "left"));
        }


    }

    // for(int x = 0; x < problem.size(); x++){
    //     for(int y = 0; y < problem[0].size(); y++){
    //         if(problem[x][y] != final[x][y]) h_n++;
    //     }
    // }

    // pq.push(h_n);

    // while(!pq.empty()){

    // }
}

int main(){
    vector<vector<int>> inital = {{8, 7, 1},
                                  {6, 0, 2},
                                  {5, 4, 3}};

    // UniformCostSearch(inital);
    AStar(inital);

    return 0;
}

