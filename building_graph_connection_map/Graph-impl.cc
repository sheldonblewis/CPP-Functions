module graph;
import building;
import <iostream>;
import <string>;
import <utility>; // std::swap
using namespace std;

const string Graph::ConnectorStr[] = { "", "bridge", "tunnel", "hall" };

Graph::Graph( const std::string& name ) : nodes{nullptr}, name{name} {}
Graph::~Graph() { deleteGraph(); } 
void Graph::setName( const std::string& newName ) { name = newName; }
const std::string& Graph::getName() const { return name; }


void Graph::deleteGraph() {
    delete nodes;
    nodes = nullptr;
} // Graph::deleteGraph()


Graph::Graph( const Graph& g ) : name{g.name} {
    nodes = copyNodes( g.nodes );
} // Graph::Graph


Graph::Graph( Graph&& g ) : nodes{g.nodes}, name{std::move(g.name)} {
    g.nodes = nullptr;
} // Graph::Graph


void Graph::addNode( Building *b ) {
    if ( !b ) return;   
    if ( !nodes ) nodes = new Node{ b };
    else nodes->insert( b );
} // Graph::addNode


Building* Graph::findBuilding( const string& code ) const {
    if ( nodes ) {
        Node* n = nodes->Node::findNode( code );
        if ( n ) return n->b;
    } // if
    
    return nullptr;
} // Graph::findBuilding


void Graph::removeNode( const string& code ) {
    if ( !nodes ) return;
    
    // find node
    Node *fodder = nodes;
    Node *parent = nullptr;
    
    while ( fodder ) {
        if ( fodder->getCode() == code ) break;
        
        parent = fodder;
        if ( fodder->getCode() > code ) {
            if ( fodder->left ) fodder = fodder->left;
            else return;
        } else {
            if ( fodder->right ) fodder = fodder->right;
            else return;
        } // if
    } // while

    // fodder has no children
    if ( !fodder->left  &&  !fodder->right  ) {
        if ( !parent ) nodes = nullptr;
        else if ( parent->left == fodder ) parent->left = nullptr;
        else parent->right = nullptr;
        delete fodder;
        return;
    } // if
        
    // fodder has one right child
    if ( !fodder->left ) {
        if ( !parent ) nodes = nodes->right;
        else if ( parent->left == fodder ) parent->left = fodder->right;
        else parent->right = fodder->right;
        fodder->right = nullptr; // unlink from rest of tree
        delete fodder;
        return;
    } // if
    
    // fodder had one left child
    if ( !fodder->right ) {
        if ( !parent ) nodes = nodes->left;
        else if ( parent->left == fodder ) parent->left = fodder->left;
        else parent->right = fodder->left;
        fodder->left = nullptr; // unlink from rest of tree
        delete fodder;
        return;
    } // if
    
    // fodder has two children
    if ( !parent ) nodes = nodes->left;
    else if ( parent->left == fodder ) parent->left = fodder->left;
    else parent->right = fodder->left;

    Node *maxleft = fodder->left;
    while ( maxleft->right )
        maxleft = maxleft->right;
    maxleft->right = fodder->right;

    // unlink node before free so don't affect rest of graph
    fodder->left = nullptr;
    fodder->right = nullptr;
    delete fodder;
} // Graph::removeNode


void Graph::addEdge( const string& code1, const string& code2, const string& connectorStr ) {
    if ( nodes ) {
        Node* b1 = nodes->Node::findNode( code1 );
        if ( !b1 ) return;
        Node* b2 = nodes->Node::findNode( code2 ) ;
        if ( !b2 ) return;
        
        Connector conn = BAD_CONNECTOR;
        
        for ( int i = sizeof(Connector)-1; i>0; i--) {
            if ( ConnectorStr[i] == connectorStr ) {
                conn = (Connector)i;
                break;
            } // if
        } // for
        
        b1->edges = new Edge{ b2, conn, b1->edges };
        b2->edges = new Edge{ b1, conn, b2->edges };
    } // if
} // Graph::addEdge


void Graph::removeEdge( const string& code1, const string& code2 ) {
    if ( nodes ) {
        Node *b1 = nodes->Node::findNode( code1 );
        Node *b2 = nodes->Node::findNode( code2 );

        if ( b1->edges ) b1->edges = b1->edges->remove( b2 );
        if ( b2->edges ) b2->edges = b2->edges->remove( b1 );
    } // if
} // Graph::removeEdge


bool Graph::operator==( const Graph& g ) const {
    if ( !nodes && !g.nodes ) return true;
    
    // is every node in self in g2?
    if ( nodes && !( nodes->inGraph( g ) ) ) return false;
    
    // is every node in g2 in self?
    if ( g.nodes && !( g.nodes->inGraph( *this ) ) ) return false;
    
    return true;
} // Graph::operator==


Graph& Graph::operator=( const Graph& g ) {
    if ( this == &g ) return *this;

    deleteGraph();
    name = g.name;
    nodes = copyNodes( g.nodes );
    return *this;
} // Graph::operator=


Graph& Graph::operator=( Graph&& g ) {
    if ( this == &g ) return *this;

    deleteGraph();
    nodes = g.nodes;
    name = std::move(g.name);
    g.nodes = nullptr;
    return *this;
} // Graph::operator=


Graph::Node* Graph::copyNodes( Node* src ) const {
    if ( !src ) return nullptr;

    Node* copy = new Node{ *src };
    copy->edges = src->edges ? src->edges->copyList( copy, src ) : nullptr;
    return copy;
}


bool Graph::search( Graph::Edge* path, Graph::Node* dest, Graph::Node* source, const bool printall ) {
    Graph::Node* last = path->connectsTo;   
    Graph::Edge* edges = last->edges;

    // look at extensions to existing path
    while ( edges ) {
        
        // ignore extension if it leads to a cycle
        if ( path->find( edges->connectsTo->b ) ) {
            edges = edges->next;
            continue;
        } // if
        
        // found a path
        if ( edges->connectsTo == source ) {
            cout << "\t" << *edges;
            Graph::Edge* e = path;
            while ( e ) {
                cout << " " << *e;
                e = e->next;
            } // while
            cout << endl;
            
            if ( !printall ) return true;
        } // if
        
        edges = edges->next;
    } // while
    
    // otherwise, recurse by extending the current path with each adjacent edge, and continue the search
    edges = last->edges;
    while ( edges ) {
        
        // ignore extension if it leads to a cycle or a reported path
        if ( path->find( edges->connectsTo->b ) || edges->connectsTo == source ) {
            edges = edges->next;
            continue;
        } // if
        
        path = new Graph::Edge{ edges->connectsTo, edges->connType, path };
        bool done = search( path, dest, source, printall );
        
        Graph::Edge *fodder = path;
        path = path->next;
        fodder->next = nullptr; // unlink before freeing
        delete fodder;
        
        if ( done && !printall ) return true;
        
        edges = edges->next;
    } // while
    
    return false;
} // Graph::search


void Graph::printPaths( const string& code1, const string& code2, const bool printall ) const {
    if ( nodes ) {        
        Node *source = nodes->findNode( code1 );
        Node *dest = nodes->findNode( code2 );       
        if ( source && dest ) {           
            if ( source == dest ) {
                cout << "\t" << source->getCode() << endl;
                if ( !printall ) {
                    cout << endl;
                    return;
                } // if
            } // if
            
            if ( source->edges && dest->edges ) {
                Edge* path = new Edge{ dest, BAD_CONNECTOR, nullptr };
                search( path, dest, source, printall );
                delete path;
            } // if
        } // if        
        cout << endl;
    } // if
} // Graph::printPaths

// Node methods
Graph::Node::Node( Building* b ) : 
    b{b}, edges{nullptr}, left{nullptr}, right{nullptr} 
{}

// Recursively copy all of the Graph's nodes and not the edges, yet. Edges need
// to be copied from Graph level of BST to account for buildings being in new
// Node objects. 
Graph::Node::Node( const Node& n ) : 
    b{n.b}, edges{nullptr},
    left{ n.left ? new Node{*n.left} : nullptr },
    right{ n.right ? new Node{*n.right} : nullptr }
{}

Graph::Node::Node( Node&& n ) :
    b{n.b}, edges{n.edges}, left{n.left}, right{n.right}
{
    n.left = n.right = nullptr;
    n.edges = nullptr;
}

Graph::Node::~Node() {
    // if anybody refers to this node by an edge, get rid of the edge
    if ( edges ) edges->deleteEdges( this );
    delete edges;
    delete left;
    delete right;
} // Graph::Node::~Node

string Graph::Node::getCode() const { return b->getCode(); }

void Graph::Node::insert( Building *newb ) {
    if ( b->getCode() == newb->getCode() ) return;

    if ( newb->getCode() < b->getCode() ) {
        if ( left ) left->insert( newb );
        else left = new Node{ newb };
    } else {
        if ( right ) right->insert( newb );
        else right = new Node{ newb };
    } // if
} // Graph::Node::insert


Graph::Node* Graph::Node::findNode( const string& code ) {
    if ( b->getCode() == code ) return this;
    if ( b->getCode() > code ) {
        if ( left ) return left->findNode( code );
        else return nullptr;
    } else {
        if ( right ) return right->findNode( code );
        else return nullptr;
    } // if
} // Graph::Node::findNode


bool Graph::Node::inGraph( const Graph& g2 ) const {
    if ( !g2.nodes ) return false;   
    Node* remote = g2.nodes->findNode( getCode() );    
    if ( !remote ) return false;   
    if ( b != remote->b ) return false;  
    if ( edges && remote->edges ) {
        if ( *edges != *(remote->edges) ) return false;
    } else if ( edges || remote->edges ) return false;
    if ( right && !( right->inGraph( g2 ) ) ) return false;   
    if ( left && !( left->inGraph( g2 ) ) ) return false;  
    return true;
} // Graph::Node::inGraph



// inorder print to console
void Graph::Node::print( ostream& out ) const {
    if ( left ) left->print( out );

    out << *b << endl;
    
    Edge* curr = edges;
    if ( curr ) {
        out << "\tConnects to: " << *curr;
        while ( curr->next ) {
            curr = curr->next;
            out << ", " << *curr;
        } // while
        out << endl;
    } // if
    out << endl;
    
    if ( right ) right->print( out );
} // Graph::Node::print


// Edge methods
Graph::Edge::Edge( Node *n, Connector c, Edge *e ) : 
    connectsTo{n}, connType{c}, next{e} 
{}


Graph::Edge::Edge( Edge&& e ) : 
    connectsTo{e.connectsTo}, connType{e.connType}, next{e.next} 
{
    e.next = nullptr;
    e.connectsTo = nullptr;
    e.connType = BAD_CONNECTOR;
}


Graph::Edge::~Edge() { delete next; }


Graph::Edge* Graph::Edge::remove( Node* b ) {
    Edge* parent = nullptr;
    Edge* curr = this;
    
    while ( curr ) {
        if ( curr->connectsTo == b ) {
            if ( !parent ) {
                Edge* ret = curr->next;
                curr->next = nullptr; // unlink from rest
                delete curr;
                return ret;
            } else {
                parent->next = curr->next;
                curr->next = nullptr; // unlink from rest
                delete curr;
                return this;
           } // if
        } // if
        parent = curr;
        curr = curr->next;
    } // while 
    
    return this;
} // Graph::Edge::remove


const Graph::Edge* Graph::Edge::find( Building* b ) const {
    if ( connectsTo->b == b ) return this;  
    if ( next ) return next->find( b );   
    return nullptr;
} // Graph::Edge::find


void Graph::Edge::deleteEdges( Node* source ) {
    if ( next ) next->deleteEdges( source );
        
    // remove corresponding link in connectsTo's edge list
    Graph::Node* remote = connectsTo;
    if ( remote && remote->edges ) 
        remote->edges = remote->edges->remove( source );
} // Graph::Edge::deleteEdges


Graph::Edge* Graph::Edge::copyList( Node* newg, Node* oldg ) const {
    Edge* copy = nullptr;
    
    if ( next ) 
        copy = new Edge{ newg->findNode( connectsTo->getCode() ), 
            connType, next->copyList( newg, oldg ) };
    else
        copy = new Edge{ newg->findNode( connectsTo->getCode() ), 
            connType, nullptr };
    
    return copy;
} // Graph::Edge::copyList


bool Graph::Edge::inEdges( const Edge& e2 ) const {   
    const Edge* remote = e2.find( connectsTo->b );   
    if ( !remote ) return false;  
    if ( connType != remote->connType ) return false;    
    if ( next && !( next->inEdges ( e2 ) ) ) return false;  
    return true;
} // Graph::Edge::inEdges

bool Graph::Edge::operator==( const Edge& e2 ) const {  
    // is every edge in self in e2?
    if ( !( this->inEdges( e2 ) ) ) return false;
    
    // is every edge in e2 in self?
    if ( !( e2.inEdges( *this ) ) ) return false;
    
    return true;
} // Graph::Edge::operator==


bool Graph::Edge::operator!=( const Edge& e2 ) const {
    return ( !( *this == e2 ) );
} // Graph::Edge::operator!=

ostream& operator<<( ostream& out, const Graph::Edge& e ) {
    out << e.connectsTo->getCode();
    if ( e.connType != Graph::BAD_CONNECTOR )
        out << " (" << Graph::ConnectorStr[ e.connType ] << ")";
    return out;
} // operator<<

ostream& operator<<( ostream& out, const Graph& graph ) {
    out << "--- " << graph.getName() << "---\n";
    if ( graph.nodes ) graph.nodes->print( out );    
    return out;
} // operator<<
