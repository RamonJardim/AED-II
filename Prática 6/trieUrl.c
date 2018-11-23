#include "tn_trie.h"
#include <fstream>

using namespace std;

tn_trie_node* create_trie() {
    tn_trie_node* node = new_node();

    string line;
    ifstream myfile ("url02.txt");
    if(myfile.is_open()) {
        while (getline (myfile,line)) {
            line.pop_back(); // retira a quebra de linha
            insert(node, line);
        }
        myfile.close();
    }

    return node;
}

int main(){
    tn_trie_node* root = create_trie();
    string url;

    cout << "Digite a url (ou o início dela): ";
    cin >> url;
    tn_suggest(root, url);
}

/*  Os sites que contém um traço (-) no link, não são adicionados na trie,
 * pois o traço não está no alfabeto definido*/