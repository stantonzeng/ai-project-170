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

int k = 3;

vector<vector<int>> final = {{1, 2, 3},
                             {4, 5, 6},
                             {7, 8, 0}};

vector<vector<int>> checker;

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
int getGn(vector<vector<int>> pb){
    int answ = 0;

    for(int i = 0; i < pb.size(); i++){
        for(int j = 0; j < pb.size(); j++){
            // cout << pb[i][j] << endl;
            if(pb[i][j] != 0){
                // cout << "for value: " << pb[i][j] << " is being compared with " << i << " - " << checker[pb[i][j]][0] << " , and " << j << " - " << checker[pb[i][j]][1] << endl;
                answ += abs(i - checker[pb[i][j]][0]) + abs(j - checker[pb[i][j]][1]);
            }
        }
    }

    return answ;
}

void UniformCostSearch(vector<vector<int>> problem){
    queue<Node*> UCS;

    UCS.push(new Node(0, 0, problem, ""));
    int i = 0;
    int j = 0;

    int count = 0;
    
    while(!UCS.empty()){
        // cout << "size: " << UCS.size() << endl;
        if(UCS.front()->state == final){
            cout << "UCS: found at depth " << UCS.front()->g_n << " and at queue size " << UCS.size() << "!" << endl;
            cout << "Evaluated " << count << " number of states" << endl << endl;
            return;
        }
        // cout << " a" << endl;

        Node* nd = UCS.front();
        count++;
        UCS.pop();

        // for(auto it1: nd->state){
        //     for(auto it2: it1){
        //         cout << it2 << " ";
        //     }
        //     cout << endl;
        // }

        for(int x = 0; x < problem.size(); x++){
            for(int y = 0; y < problem[0].size(); y++){
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
            UCS.push(new Node(0,nd->g_n+1, temp, "up"));
        }
        // cout << " c" << endl;
        if(i > 0 && nd->movement != "up"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i-1][j], temp[i][j]);
            UCS.push(new Node(0,nd->g_n+1, temp, "down"));
        }
        // cout << " d" << endl;
        if(j < problem[0].size()-1 && nd->movement != "left"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i][j+1], temp[i][j]);
            UCS.push(new Node(0,nd->g_n+1, temp, "right"));
        }
        // cout << " e" << endl;
        if(j > 0 && nd->movement != "right"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i][j-1], temp[i][j]);
            UCS.push(new Node(0,nd->g_n+1, temp, "left"));
        }
        // cout << " f" << endl;
    }
}




void AStar(vector<vector<int>> problem){
    priority_queue<Node*, vector<Node*>, node_cmp> pq;

    pq.push(new Node(-1, 0, problem, ""));

    int i = 0;
    int j = 0;

    int count = 0;

    while(!pq.empty()){
        if(pq.top()->state == final){
            cout << "Misplaced Tile: found at depth " << pq.top()->g_n << " and at queue size " << pq.size() << "!" << endl;
            cout << "Evaluated " << count << " number of states" << endl << endl;
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
        count++;
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
}





void manhattan(vector<vector<int>> problem){
    priority_queue<Node*, vector<Node*>, node_cmp> pq;

    pq.push(new Node(-1, 0, problem, ""));

    int i = 0;
    int j = 0;

    int count = 0;

    while(!pq.empty()){
        if(pq.top()->state == final){
            cout << "Manhattan Distance: found at depth " << pq.top()->g_n << " and at queue size " << pq.size() << "!" << endl;
            cout << "Evaluated " << count << " number of states" << endl << endl;
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
        count++;
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
        // cout << "a" << endl; 
        if(i < problem.size()-1 && nd->movement != "down"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i+1][j], temp[i][j]);
            pq.push(new Node(getGn(temp), nd->g_n+1, temp, "up"));
        }
        // cout << " c" << endl;
        if(i > 0 && nd->movement != "up"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i-1][j], temp[i][j]);
            pq.push(new Node(getGn(temp), nd->g_n+1, temp, "down"));
        }
        // cout << " d" << endl;
        if(j < problem[0].size()-1 && nd->movement != "left"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i][j+1], temp[i][j]);
            pq.push(new Node(getGn(temp), nd->g_n+1, temp, "right"));
        }
        // cout << " e" << endl;
        if(j > 0 && nd->movement != "right"){
            vector<vector<int>> temp = nd->state;
            swap(temp[i][j-1], temp[i][j]);
            pq.push(new Node(getGn(temp), nd->g_n+1, temp, "left"));
        }
    }
}

int main(){

    vector<vector<int>> test1 =  {{1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 0}};

    vector<vector<int>> test2 =  {{1, 2, 3},
                                  {4, 5, 6},
                                  {0, 7, 8}};

    vector<vector<int>> test3 =  {{1, 2, 3},
                                  {5, 0, 6},
                                  {4, 7, 8}};
    
    vector<vector<int>> test4 =  {{1, 3, 6},
                                  {5, 0, 2},
                                  {4, 7, 8}};

    vector<vector<int>> test5 =  {{1, 3, 6},
                                  {5, 0, 7},
                                  {4, 8, 2}};

    vector<vector<int>> test6 =  {{1, 6, 7},
                                  {5, 0, 3},
                                  {4, 8, 2}};

    vector<vector<int>> test7 =  {{7, 1, 2},
                                  {4, 8, 5},
                                  {6, 3, 0}};

    vector<vector<int>> test8 =  {{0, 7, 2},
                                  {4, 6, 1},
                                  {3, 5, 8}};

    checker.push_back(vector<int> (k-1, k-1));

    for(int i = 1; i < k*k; i++){
        checker.push_back(vector<int> {i/k, (i-1)%k});
    }

    // cout << getGn(inital2) << endl;

    cout << endl << endl;

    vector<vector<int>> test = test8;

    UniformCostSearch(test);
    AStar(test);
    manhattan(test);

    return 0;
}

