#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

int main() {

    string languages [] = {"German", "Dutch", "Swedish", "French"};
    ifstream langStream;
    stringstream langBuf;
    stringstream pathStream;
    map<string,string> corpora;
    map<string, map<string,float> > models;
    string gram;

    // Read corpora into the language-corpus mapping
    for (int i = 0; i < 4; i++) {
        pathStream << "corpora/Monolingual_data/" << languages[i] << ".txt";
        langStream.open(pathStream.str());

        langBuf << langStream.rdbuf();
        
        corpora[languages[i]] = langBuf.str();

        langBuf = stringstream();
        pathStream = stringstream();
        langStream = ifstream();


    }
    
    cout << corpora.size() << endl;
    
    // Iterate over the corpora to count the trigrams within
    map<string,string>::iterator corpIt;
    for (corpIt = corpora.begin(); corpIt != corpora.end(); corpIt++) {

        // Extract trigrams and store counts in the model map
        int corpSize = (corpIt->second).length();
        for (int c = 0; c < (corpSize - 2); c++) {
            gram = (corpIt->second).substr(c,3);

            // Make sure all languages have a value for every trigram encountered
            for (string lang : languages) {
                if (!(models[lang].count(gram))) {
                    models[lang][gram] = 0;
                }
            
            models[corpIt->first][gram] += 1; // Increment language's count for current trigram
            // cout << models[corpIt->first][gram] << endl;
            }

        }
        cout << corpIt->first << endl;
    }

    map<string,float>::iterator modelIt;
    // Iterate over the corpora again, using the number of trigrams in each to turn counts into probabilities
    // for (corpIt = corpora.begin(); corpIt != corpora.end(); corpIt++) {
        // int trigrams = (corpIt->second).length() - 2;

        // for (modelIt = models[corpIt->first].begin(); modelIt != models[corpIt->first].end(); modelIt++) {
            // cout << modelIt->second << endl;
        // }
    // }
    
    return 0;
}