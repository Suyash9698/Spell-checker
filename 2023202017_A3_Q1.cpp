#include <iostream>
#include <vector>
using namespace std;

struct Node {
    struct Node* link[26];
    bool f;
    string word;
    Node() {
        f = false;
        for (int i = 0; i < 26; i++) {
            link[i] = nullptr;
        }
    }

    bool isPresent(char ch) {
        return link[ch - 'a'] != nullptr;
    }

    Node* get(char ch) {
        return link[ch - 'a'];
    }

    bool isSet() {
        return f;
    }

    void doSet() {
        f = true;
    }

    void put(char ch, Node* node) {
        link[ch - 'a'] = node;
    }
};

class Trie {
public:
    Node* root;

    Trie() {
        root = new Node();
    }

    void insert(string s) {
        Node* node = root;
        for (int i = 0; i < s.length(); i++) {
            if (!node->isPresent(s[i])) {
                node->put(s[i], new Node());
            }
            node = node->get(s[i]);
        }
        node->doSet();
        node->word=s;
    }

    bool search(string s) {
        Node* node = root;
        for (int i = 0; i < s.length(); i++) {
            if (!node->isPresent(s[i])) {
                return false;
            }
            node = node->get(s[i]);
        }
        return node->isSet();
    }

    void dfs(string curr, Node* node, vector<string>& ans) {
        if (node->isSet()) {
            ans.push_back(curr);
        }

        for (int i = 0; i < 26; i++) {
            char ch = (char)(97 + i);
            if (node->isPresent(ch)) {
                dfs(curr + ch, node->get(ch), ans);
            }
        }
    }

    vector<string> isPrefixAndSolve(string s) {
        vector<string> ans;
        Node* node = root;
        for (int i = 0; i < s.length(); i++) {
            if (!node->isPresent(s[i])) {
                return ans;
            }
            node = node->get(s[i]);
        }
        string curr = s;
        if (node->isSet()) {
            ans.push_back(curr);
        }
        for (int i = 0; i < 26; i++) {
            char ch = (char)(97 + i);
            if (node->isPresent(ch)) {
                dfs(curr + ch, node->get(ch), ans);
            }
        }
        return ans;
    }

    void help(Node* node,string s,char ch,vector<string>& ans,vector<int>& prevRow){
        vector<int> currRow;
        //appending or insertion operation in empty string which is prevRow[0]
        currRow.push_back(prevRow[0]+1);

        //matching with trie data and our s data if char matches then just push back else +1
        for(int i=1;i<=s.length();i++){
            if(s[i-1] == ch){
                currRow.push_back(prevRow[i-1]);
            }
            else{
                //take min 
                int mini= min(currRow[i-1]+1,min(prevRow[i-1]+1,prevRow[i]+1));
                currRow.push_back(mini);
            }
        }
        if(node->isSet() && currRow[s.size()] <= 3){
            ans.push_back(node->word);

        }

        //calculating min and seeing whether it is less than 3 or not 
        int mini=INT_MAX;
        for(int i=0;i<currRow.size();i++){
            mini=min(mini,currRow[i]);
        }

        if(mini<=3){
             for(int i=0;i<26;i++){
               char ch=(char)(97+i);
               if(node->isPresent(ch)){
                  help(node->get(ch),s,ch,ans,currRow);
                }
             }
        }
       
    }

    void myFunction(string s){
        Node* node=root;
        vector<int> currRow(s.size()+1);
        vector<string> ans;
        for(int i=0;i<26;i++){
            char ch=(char)(97+i);
            if(node->isPresent(ch)){
                help(node->get(ch),s,ch,ans,currRow);
            }
        }

        cout<<ans.size()<<endl;
        for(auto ele: ans){
            cout<<ele<<endl;
        }
    }

    

};

int main() {
    Trie t;
    int n;
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        string e;
        cin >> e;
        t.insert(e);
    }
    int a;
    string b;
    for (int i = 0; i < q; i++) {
        cin >> a;
        cin >> b;
        if (a == 1) {
            cout << t.search(b) << endl;
        }
        else if (a == 2) {
            vector<string> ans = t.isPrefixAndSolve(b);
            cout << ans.size() << endl;
            for (auto ele : ans) {
                cout << ele << endl;
            }
        }
        else if (a == 3) {
            vector<string> ans;
            t.myFunction(b);
            
        }
    }
    return 0;
}
