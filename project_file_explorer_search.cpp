// Project : File explorer search by Yash Kumar

#include <iostream>
using namespace std;

// Node structure for Trie
struct Node {
    // Array to store links to child nodes,
    // each index represents a letter
    Node* links[26];
    // Flag indicating if the node
    // marks the end of a word
    bool flag = false;

    // Check if the node contains
    // a specific key (letter)
    bool containsKey(char ch) {
        return links[ch - 'a'] != NULL;
    }

    // Insert a new node with a specific
    // key (letter) into the Trie
    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    // Get the node with a specific
    // key (letter) from the Trie
    Node* get(char ch) {
        return links[ch - 'a'];
    }

    // Set the current node
    // as the end of a word
    void setEnd() {
        flag = true;
    }

    // Check if the current node
    // marks the end of a word
    bool isEnd() {
        return flag;
    }

    void unsetEnd(){
        flag = false;
    }
};

// Trie class
class Trie {
private:
    Node* root;

public:
    // Constructor to initialize the
    // Trie with an empty root node
    Trie() {
        root = new Node();
    }

    // Inserts a word into the Trie
    // Time Complexity O(len), where len
    // is the length of the word
    void insert(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                // Create a new node for
                // the letter if not present
                node->put(word[i], new Node());
            }
            // Move to the next node
            node = node->get(word[i]);
        }
        // Mark the end of the word
        node->setEnd();
    }

    // Returns if the word
    // is in the trie
    bool search(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                // If a letter is not found,
                // the word is not in the Trie
                return false;
            }
            // Move to the next node
            node = node->get(word[i]);
        }
        // Check if the last node
        // marks the end of a word
        return node->isEnd();
    }

    // Returns if there is any word in the
    // trie that starts with the given prefix
    bool startsWith(string prefix) {
        Node* node = root;
        for (int i = 0; i < prefix.length(); i++) {
            if (!node->containsKey(prefix[i])) {
                // If a letter is not found, there is
                // no word with the given prefix
                return false;
            }
            // Move to the next node
            node = node->get(prefix[i]);
        }
        // The prefix is found in the Trie
        helper_print_words(node, prefix);
        return true;
    }

    void helper_print_words(Node* node, string &curr){
        if(!node)   return;
        if(node -> flag)
            cout << curr << endl;
        
        string temp = curr;
        int n = curr.length();
        curr += '*';

        for(int i = 0; i < 26; i++){
            curr[n] = 'a' + i;
            helper_print_words(node->links[i],curr);
        }
        curr = temp;
        return;
    }

    bool delete_word(string word){
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                // If a letter is not found,
                // the word is not in the Trie
                return false;
            }
            // Move to the next node
            node = node->get(word[i]);
        }
        // Check if the last node
        // marks the end of a word
        node->unsetEnd();
        return true;
    }

    void deleteNode(Node* node) {
        if (!node) return;
        for (int i = 0; i < 26; i++) {
            deleteNode(node->links[i]);
        }
        delete node;
    }

    bool delete_all_starting_with(string word){
        Node* node = root;
        Node* parent = nullptr;
        char last_char = 0;

        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                // If a letter is not found,
                // the word is not in the Trie
                return false;
            }
            // Move to the next node
            parent = node;
            node = node->get(word[i]);
            last_char = word[i];
        }

        // Unset end flag of the prefix node
        node->unsetEnd();

        // Delete the entire subtree from the last character node
        if (parent != nullptr) {
            parent->put(last_char, nullptr);
            deleteNode(node);
        }

        return true;
    }

};

//aim -> if given search file
//aim -> starting with

int main() {
    Trie trie;
    cout << "Enter no. of files : "; 
    int n;
    cin >> n;
    cout << "Only alphabet file names allowed." << endl;
    cout << "Enter file names: ";
    for (int i = 0; i < n; i++)
    {
        string temp;
        cin >> temp;
        trie.insert(temp);
    }   
    cout << "Enter no. of queries : ";
    int q;
    cin >> q;
    cout << "If you want to search exact word, enter 1 and then query" << endl;
    cout << "If you want to search all files starting with word, enter 2 and then query" << endl;
    cout << "If you want to delete a word, enter 3 and then query" << endl;
    cout << "If you want to delete all files starting with word, enter 4 and then query"<<endl;
    cout << "If you want to add a new file, enter 4 and then query"<<endl;
    while (q--)
    {
        int query; string str;
        cin >> query >> str;
        if(query == 1){
            cout << "Assessing query 1 : "<< endl;
            if(trie.search(str))
                cout << "File named " << str << " exists in the directory." << endl;
            
            else
                cout << "File named " << str << " does not exist in the directory." << endl;
            cout << "Query answered." << endl;

        }
        else if(query == 2){
            cout << "Assessing query 2 : "<< endl;
            trie.startsWith(str);
            cout << "Query answered." << endl;
        }
        else if(query == 3){
            cout << "Assessing query 3 : "<< endl;
            trie.delete_word(str);
            cout << "Query answered." << endl;
        }
        else if(query == 4){
            cout << "Assessing query 4 : "<< endl;
            trie.delete_all_starting_with(str);
            cout << "Query answered." << endl;
        }
        else if(query == 5){
            trie.insert(str);
        }

    }
    

    return 0;
}