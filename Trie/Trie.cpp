#include "Trie.h"



Trie::Trie(char language[4]) {
    // Create root node for trie; its unigram is an empty C-string, and it is not a leaf
    std::shared_ptr<UnigramNode> rt(new UnigramNode);
    rt->unigram = '\0';
    rt->isLeaf = false;

    // Set root for the trie
    this->root = rt;
    this->ngramCount = 0;

    // Set lang for the tree
    strcpy(this->lang,language);
}

Trie::~Trie() {}

void Trie::PrintLanguage() {
    std::cout << this->lang << std::endl;

}

void Trie::PrintTrieContents(std::shared_ptr<UnigramNode> start, std::string gram) {

    // Starting point is root if no starting point is passed
    std::shared_ptr<UnigramNode> startingPoint = (!start) ? (this->root) : start;


    // BASE CASE: starting point is a leaf node, representing an ngram to be printed
    if (startingPoint->isLeaf) {

        // Print the ngram and its count
        std::cout << gram << ", " << startingPoint->count << std::endl;


        return;
    }


    // Recursive case: starting point is an internal node
    else {

        // If internal starting node has no children, then that node is the root of an empty trie
        if ((startingPoint->progeny).empty()) {
            std::cout << "Trie is empty." << std::endl;
        }

        // For each child in the starting node's progeny map
        for (auto it = (startingPoint->progeny).begin(); it != (startingPoint->progeny).end(); ++it) {

            // Recursively print tree contents for that child and it's corresponding character
            PrintTrieContents(it->second, gram + it->first);
        }
    }

    return;
}

std::shared_ptr<UnigramNode> Trie::InitNode(char c) {
    std::shared_ptr<UnigramNode> newnode(new UnigramNode);

    newnode->unigram = c;
    newnode->isLeaf = false;
    newnode->count = 0;
    return newnode;
}

void Trie::InsertGram(char gram[]) {
    std::shared_ptr<UnigramNode> current = this->root;

    // Position of character in ngram to be added
    int string_pos = 0;

    while (string_pos < (strlen(gram))) {

        auto it = (current->progeny).find(gram[string_pos]);

        // If the character is not already a child of the current node, add it
        if (it == (current->progeny).end()) {

            // Create new unigram node with the character at the specified position
            std::shared_ptr<UnigramNode> newnode = InitNode(gram[string_pos]);

            // Insert the new character/node into the progeny map
            (current->progeny).insert({gram[string_pos],newnode});

            // Move to the newly created node
            current = newnode;
        }

        // If the character is already a child of the current node, move to that child
        else {
            current = it->second;
        }

        // Insert the next character from the ngram
        ++string_pos;
    }

    // increment the trie's count of ngrams
    ++(this->ngramCount);

    // Incremenent the count of the leaf node, which represents the count for that ngram
    ++(current->count);
    (current->isLeaf) = true;

}

bool Trie::Prune(std::shared_ptr<UnigramNode> start) {

    // Create a starting point, using either the optional parameter for recursive calls or the trie root
    std::shared_ptr<UnigramNode> startingPoint = (!start) ? (this->root) : start;

    // BASE CASE: starting point is a leaf (representing an entire ngram)
    if (startingPoint->isLeaf) {


        // If the count for the ngram is below the pruning threshhold, remove it from the tree
        if ((startingPoint->count) < 2) {

            // Reduce trie's ngram count by the number of instances of the removed ngram
            (this->ngramCount) = (this->ngramCount) - (startingPoint->count);
            return true;
        }

        return false;
    }


    // RECURSIVE CASE: starting point is an internal node
    else {

        // next_it is used to specify the next iterator in the map, since sometimes the iterator is erased
        for (auto it = (startingPoint->progeny).begin(), next_it = it; it != (startingPoint->progeny).end(); it = next_it) {

            // Increment next iterator
            ++next_it;

            bool isPruned = Prune(it->second);
            if (isPruned) {
                (startingPoint->progeny).erase(it);
            }

        }

        if ((startingPoint->progeny).empty()) {
            return true;
        }

        else {return false;}
    }

}

int Trie::Lookup(char gram[]) {
    if (!strlen(gram)) {
        return 0;
    }

    std::shared_ptr<UnigramNode> current = this->root;
    int string_pos = 0;

    while (string_pos < strlen(gram)) {

        auto it = (current->progeny).find(gram[string_pos]);

        if (it == (current->progeny).end()) {return 0;}
        else {
            current = it->second;
        }


        ++string_pos;
    }

    return current->count;
}
