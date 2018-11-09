#include "tn_trie.h"

using namespace std;

int main(){
    FILE* f = fopen("url02.txt", "rt");
    char lines[100];
    string urls[1000];
    int i;
    for(i = 0 ; !feof(f) ; i++) {
        char* tmp = fgets(lines, 100, f);
        urls[i] = tmp ? tmp : "";
        if(!urls[i].empty()){
            cout << urls[i];
        }
    }
}