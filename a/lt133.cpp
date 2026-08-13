/*
133. Clone Graph

*/

class Solution {
public:
    unordered_map<Node*, Node*> mp;
    Node* cloneGraph(Node* node) {
        if(node==NULL)
            return NULL;
        if(mp.count(node))
            return mp[node];
        Node* clone = new Node(node->val);
        mp[node]= clone;
        for(auto neigh: node->neighbors){
            clone->neighbors.push_back(cloneGraph(neigh));
        }
        return clone;
    }
};