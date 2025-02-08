export module graph;
import building;

import <iostream>;
import <string>;

//===================================================================
// Graph (of Buildings and Connectors)
// Assumes no cycles and unique buildings.
//===================================================================

export class Graph {
    class Edge; // forward declaration
    enum Connector { BAD_CONNECTOR, bridge, tunnel, hall };

    // Implements a binary search tree of buildings in the graph
    // (could be a subset of a collection) and a list of all edges
    // connected to the building.
    struct Node {
        Building *b;
        Edge *edges;
        Node *left, *right;
        Node( Building* b );
        Node( const Node& n );
        Node( Node&& n );
        ~Node();
        std::string getCode() const;
        void insert( Building* b );
        Node* findNode( const std::string& code );
        bool inGraph( const Graph& g ) const;
        void print( std::ostream& o ) const;

        // *** Node helper methods:
        // *** Add here ***
    };

    // An edge is a singly-linked list of the type of connections to a
    // particular building, and to what other node (building) the edge is
    // connected.
    struct Edge {
        Node *connectsTo;
        Connector connType;
        Edge *next;
        Edge( Node *n, Connector c, Edge *e );
        // *** Can't copy an edge since need to know the new graph's nodes, which aren't
        // *** obtainable from either the old edge or the edge being copied.
        // Edge( const Edge& e );
        Edge( Edge&& e );
        ~Edge();
        Edge* remove( Node* n );
        const Edge* find( Building* b ) const;
        bool operator==( const Edge& e ) const;
        bool operator!=( const Edge& e ) const;
        bool inEdges( const Edge& e ) const;
        void print( std::ostream& out ) const;
        void deleteEdges( Node* n );

        // edge helper methods
        Edge* copyList( Node* newg, Node* oldg ) const;
        friend std::ostream& operator<<( std::ostream& out, const Edge& e );
    };

  public:
    Graph( const std::string& name = "" );
    ~Graph();
    Graph( const Graph& g );
    Graph( Graph&& g );
    void setName( const std::string& newName );
    const std::string& getName() const;
    void addNode( Building* b );
    void removeNode( const std::string& code );
    Building* findBuilding( const std::string& code ) const;
    void addEdge( const std::string& code1, const std::string& code2, 
        const std::string& connectorStr );
    void removeEdge( const std::string& code1, const std::string& code2 );
    void printPaths(  const std::string& code1, const std::string& code2, 
        const bool printall = false ) const;
    void deleteGraph();
    Graph& operator=( const Graph& g );
    Graph& operator=( Graph&& g );
    bool operator==( const Graph& g ) const;
    friend std::ostream& operator<<( std::ostream& out, const Graph& g );

  private:
    static bool search( Graph::Edge* path, Graph::Node* dest, 
        Graph::Node* source, const bool printall );
    static const std::string ConnectorStr[];
    friend std::ostream& operator<< ( std::ostream& out, const Edge& e );
    Node* copyNodes( Node* src ) const;  // Helper method to copy nodes recursively

    Node *nodes; // root of tree of nodes
    std::string name; // graph name                            
};


export std::ostream& operator<<( std::ostream& out, const Graph::Edge& e );
export std::ostream& operator<<( std::ostream& out, const Graph& graph );
