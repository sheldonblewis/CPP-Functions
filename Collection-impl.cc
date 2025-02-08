module collection;
import bcode;
import building;
import <iostream>;
import <string>;
using namespace std;

ostream& operator<<( ostream& out, const Collection& tree ) {
    if ( tree.root ) tree.root->print( out );
    return out;
}

Collection::Collection() : root{nullptr} {}

Collection::~Collection() {
    if ( root ) {
        delete root;
        root = nullptr;
    } // if
} // Collection::~Collection

void Collection::insert( const string& code, const string& name ) {
    if ( !root ) {
        root = new Node{ code, name };
        return;
    } // if
    root->insert( code, name );
} // Collection::insert

void Collection::remove( const string& code ) {
    if ( !root ) return;
    
    // find node
    Node *fodder = root;
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
    if ( !fodder->left  && !fodder->right ) {
        if ( !parent ) root = nullptr;
        else if ( parent->left == fodder ) parent->left = nullptr;
        else parent->right = nullptr;
        delete fodder;
        return;
    } // if
    
    // fodder has one right child
    if ( !fodder->left ) {
        if ( !parent ) root = root->right;
        else if ( parent->left == fodder ) parent->left = fodder->right;
        else parent->right = fodder->right;
        fodder->right = nullptr; // unlink from rest
        delete fodder;
        return;
    } // if
    
    // fodder had one left child
    if ( !fodder->right ) {
        if ( !parent ) root = root->left;
        else if ( parent->left == fodder ) parent->left = fodder->left;
        else parent->right = fodder->left;
        fodder->left = nullptr; // unlink from rest
        delete fodder;
        return;
    } // if
    
    // fodder has two children
    if ( !parent ) root = root->left;
    else if ( parent->left == fodder ) parent->left = fodder->left;
    else parent->right = fodder->left;
    
    Node* maxleft = fodder->left;
    while ( maxleft->right )
        maxleft = maxleft->right;
    maxleft->right = fodder->right;
    fodder->left = nullptr; // unlink from rest
    fodder->right = nullptr;
    delete fodder;
    return;
} // Collection::remove


Building* Collection::findBuilding( const string& code ) const {
    if ( root ) return root->findBuilding( code );    
    return nullptr;
} // Collection::findBuilding


// Node operations
Collection::Node::Node( const string& code, const string& name ) : 
    b{ new Building{ BCode{code}, name } }, left{nullptr}, right{nullptr} 
{}

Collection::Node::~Node() { 
    delete b; 
    delete right; 
    delete left;
} // Collection::Node::~Node

string Collection::Node::getCode() const { return b->getCode(); }

void Collection::Node::insert( const string& code, const string& name ) {
    if ( b->getCode() == code ) return;

    if ( b->getCode() > code ) {
        if ( left ) left->insert( code, name );
        else left = new Node{ code, name };
    } else {
        if ( right ) right->insert( code, name );
        else right = new Node{ code, name };
    } // if
} // Collection::Node::insert


Building* Collection::Node::findBuilding( const string& code ) const {
    if ( b->getCode() == code ) return b;
    
    if ( b->getCode() > code ) {
        if ( left ) return left->findBuilding( code );
    } else {
        if ( right ) return right->findBuilding( code );
    } // if
    return nullptr;
} // Collection::Node::findBuilding


void Collection::Node::print( ostream& out ) const {
    if ( left ) left->print( out );
    out << *(b) << endl;
    if ( right ) right->print( out );
} // Collection::Node::print
