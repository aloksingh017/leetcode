/*
990. Satisfiability of Equality Equations
You are given an array of strings equations that represent relationships between variables where each s
tring equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) 
that represent one-letter variable names.

Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.

 
Example 1:

Input: equations = ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
There is no way to assign the variables to satisfy both equations.

Example 2:

Input: equations = ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

Constraints:

1 <= equations.length <= 500
equations[i].length == 4
equations[i][0] is a lowercase letter.
equations[i][1] is either '=' or '!'.
equations[i][2] is '='.
equations[i][3] is a lowercase letter.
*/

class Solution {
public:
    vector<int> parent;
    int findPar(int x){
        if(parent[x]==x)
            return x;
        return parent[x]= findPar(parent[x]);
    }
    void Union(int u, int v){
        int pu= findPar(u);
        int pv= findPar(v);

        if(pu!=pv){
            parent[pu]=pv;
        }
    }
    bool equationsPossible(vector<string>& equations) {
        parent.resize(26,0);

        for(int i=0;i<26;i++){
            parent[i]=i;
        }

        for(auto it: equations){
            if(it[1]=='='){
                int u = it[0]-'a';
                int v = it[3]-'a';
                Union(u,v);
            }
        }
        for(auto it: equations){
            if(it[1]=='!'){
                int u = it[0]-'a';
                int v = it[3]-'a';
                if(findPar(u)==findPar(v))
                    return false;
            }
        }
        return true;
    }
};