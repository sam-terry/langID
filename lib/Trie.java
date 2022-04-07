import java.util.HashMap;

public class Trie {

    // Constructor
    public Trie(String lang) {
        language = lang;
        root = new Node('\000');
    }

    String language; // Model language

    private class Node {

        // Constructor
        public Node(char c) {
            unigram = c;
            count = 0;
        }

        public char unigram;

        public int count;

        public double score;

        public HashMap<Character,Node> progeny;

    }

    private Node root;

    private int gramCount;

    public void insertGram(String trigram) {
        return;
    }

    public void score() {
        return;
    }

}