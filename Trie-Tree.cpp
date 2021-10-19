#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class TrieNode
{
public:
    int count;
    int prefix;
    vector<TrieNode *> nextNode = vector<TrieNode *>(26);

    TrieNode() : count(0), prefix(0) {
    }

    ~TrieNode(){
        for(int i=0;i<26; ++i){
            if(nextNode[i]!=NULL){
                delete nextNode[i];
            }
        }
    }
};

class TrieTree
{
private:
    TrieNode *root;
public:
    TrieTree(){
        root = new TrieNode();
    }

    ~TrieTree(){
        delete root;
    }

    int insert( string s)
    {
        if (s.size() == 0)
        {
            return -1;
        }

        TrieNode *trieroot = root; // 临时根节点

        for (int i = 0; i < s.size(); ++i)
        {
            if (trieroot->nextNode[s[i] - 'a'] == nullptr)
            {
                trieroot->nextNode[s[i] - 'a'] = new TrieNode();
            }
            trieroot = trieroot->nextNode[s[i] - 'a'];
            ++trieroot->prefix;
        }
        ++(trieroot->count);
        return 0;
    }

    int search(string s)
    {
        if (s.size() == 0)
        {
            return -1;
        }

        TrieNode *trieroot = root; // 临时根节点

        for (int i = 0; i < s.size(); ++i)
        {
            if (trieroot->nextNode[s[i] - 'a']==nullptr)
            {
                return -1;
            }
            trieroot = trieroot->nextNode[s[i] - 'a'];
        }
        if (trieroot->count == 0)
        {
            return -1;
        }
        return trieroot->count;
    }

    int searchPrefix(string s){
        if (s.size() == 0)
        {
            return -1;
        }

        TrieNode *trieroot = root; // 临时根节点
        for (int i = 0; i < s.size(); ++i)
        {
            if (trieroot->nextNode[s[i] - 'a'] == nullptr)
            {
                return -1;
            }
            trieroot = trieroot->nextNode[s[i] - 'a'];
        }
        return trieroot->prefix;
    }
};

int main(){
    TrieTree trie;
    trie.insert("Hello");
    trie.insert("Hello");
    trie.insert("world");
    cout << trie.search("Hello")<<endl;
    cout << trie.searchPrefix("H") << endl;
    cout << trie.searchPrefix("He") << endl;
    cout << trie.searchPrefix("Hel") << endl;
    cout << trie.searchPrefix("Hellot") << endl;
    cout << trie.search("world") << endl;
    cout << trie.searchPrefix("worl") << endl;

    return 0;
}