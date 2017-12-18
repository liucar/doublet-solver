/*
 * @author Caroline Liu
 * @date 12/3/17
 * @course CSCI 61
 * @file Liu_HW9.cpp
 *
 * This program solves doublets puzzles of length 5 using the Graph &
 * DoubletSolver class.
 *
 * MEMBER FUNCTIONS for Graph class:
 *      int n()
 *          Precondition: Graph created
 *          Postcondition: Returns # of vertices in graph
 *      void add_vertex()
 *          Precondition: Graph created
 *          Postcondition: Adds a new vertex (integer)
 *      void add_edge(int a, int b)
 *          Precondition: a & b are existing vertices
 *          Postcondition: edge(a,b) added
 *      void is_edge(int a, int b)
 *          Precondition: Graph created
 *          Postcondition: Returns true if edge is in graph
 *      list <int> shortest_path(int start, int end)
 *          Precondition: start and end are vertices
 *          Postcondition: Returns list of vertices of path from start
 *          to end
 *      void bfs(int start, vector<int> &parent)
 *          Precondition: Start vertex exists & parent vector created
 *          Postcondition: Traverses uses bfs
 *
 * MEMBER FUNCTIONS for DoubletSolver class:
 *      void build_dict(string dict)
 *          Precondition: Dictionary file is passed in
 *          Postcondition: Builds dictionary vector and adds edges
 *          to dictionary graph (words differing in 1 character are
 *          connected)
 *      void solve(string first_word, string last_word)
 *          Precondition: Two words are in the dictionary
 *          Postcondition: Solves and prints out the answer to the
 *          doublet (transforms first word to last word)
 *      int intersections(string string1, string string2)
 *          Precondition: none
 *          Postcondition: Returns count of num of matching characters
 *          between two words
 *
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <assert.h>
#include <queue>

using namespace std;

/* GRAPH CLASS */
class Graph {
public:
    //Constructor
    Graph() {};

    // Build adjacency list graph with integer vertices
    // Integers correspond to indices for words in dictionary vector
    int n();
    void add_vertex();
    void add_edge(int a, int b);
    bool is_edge(int a, int b);
    list<int> shortest_path(int start, int end);

private:
    // Adjacency list graph
    vector<list<int>> _v;

    // Helper function that does bfs traversal
    void bfs(int start, vector<int> &parent);
};

int Graph::n() {
    return _v.size();
}

void Graph::add_vertex() {
    _v.push_back(list<int>());
}

void Graph::add_edge(int a, int b) {
    assert(a < n() && b < n());
    if (!is_edge(a, b))
    {
        _v[a].push_front(b);
        _v[b].push_front(a);
    }
}

bool Graph::is_edge(int a, int b) {
    if (a >= n() || b >= n())
        return false;

    for (auto e: _v[a])
        if (e == b)
            return true;

    return false;
}

list<int> Graph::shortest_path(int start, int end) {
    vector<int> parent(n(),-1); // Holds parents
    bfs(start,parent);

    // No answer found
    if (parent[end] == -1) {
        cout << "None";
        return list<int>();
    }

    // Create answer list by tracing back parents from end word
    list<int> ans;
    list<int>::iterator it;
    for(int v = end; v!=start; v=parent[v]) {
        ans.push_front(v);
    }
    ans.push_front(start);

    return ans;
}

void Graph::bfs(int start, vector<int> &parent) {
    queue<int> vertex_num; // Holds unprocessed vertices

    vertex_num.push(start);
    parent[start] = start;

    while (!vertex_num.empty())
    {
        int current = vertex_num.front();
        vertex_num.pop();

        for (auto e:_v[current])
        {
            if(parent[e] == -1) {
                parent[e] = current;
                vertex_num.push(e);
            }
        }
    }
}

/* DOUBLETSOLVER CLASS */
class DoubletSolver {
public:
    //Constructor
    DoubletSolver() {};

    // Member functions
    void build_dict(string dict);
    void solve(string first_word, string last_word);

private:
    // Adjacency list graph where vertices represent words
    Graph graph;

    // Dictionary vector
    vector<string> dictionary;

    // Helper function determines number of chars in common for 2 words
    int intersections(string string1, string string2);
};

int DoubletSolver::intersections(string string1, string string2) {
    int matches = 0;

    // Count matching characters in strings of length 5
    for(int i=0; i < 5; i++) {
        if (string1[i] == string2[i]) {
            matches++;
        }
    }
    return matches;
}

void DoubletSolver::build_dict(string dict) {

    ifstream inFile(dict);
    string line;

    cout << "Building dictionary..." << "\n\n";

    // Create dictionary vector
    while(getline(inFile,line)) {
        if(line.length() != 0) {
            graph.add_vertex();
            dictionary.push_back(line);
        }
    }

    inFile.close();

    string word1, word2;

    // Add edges to graph for words that have 4 common characters
    for( int i = 0; i < dictionary.size(); i++) {
        word1 = dictionary[i];
        for( int j = i; j < dictionary.size(); j++) {
            word2 = dictionary[j];
            if (intersections(word1, word2) == 4) {
                graph.add_edge(i,j);
            }
        }
    }

}

void DoubletSolver::solve(string first_word, string last_word) {
    int index1, index2;

    // Find index of first word
    for (int i = 0; i < dictionary.size(); i++) {
        if (first_word == dictionary[i]) {
            index1 = i;
        }
    }

    // Find index of last word
    for (int i = 0; i < dictionary.size(); i++) {
        if (last_word == dictionary[i]) {
            index2 = i;
        }
    }

    // Execute breadth-first-search to find shortest path b/w first
    // and last word; print out answer
    cout << first_word << " -> " << last_word << endl;
    list <int> answer = graph.shortest_path(index1, index2);
    list <int>::iterator it;
    for(it = answer.begin(); it!= answer.end(); it++) {
        cout << dictionary[*it] << " ";
    }
    cout << "\n\n";
}

int main() {
    DoubletSolver puzzle;
    puzzle.build_dict("knuth.txt");
    puzzle.solve("black", "white");
    puzzle.solve("tears", "smile");
    puzzle.solve("small", "giant");
    puzzle.solve("stone", "money");
    puzzle.solve("angel", "devil");
    puzzle.solve("amino", "right");
    puzzle.solve("amigo", "signs");

    return 0;
}