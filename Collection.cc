export module collection;
import building;
import <iostream>;
import <string>;

//===================================================================
// Building Collection - BS Tree (of Buildings )
// The Collection cannot be copied or moved so make them private operations
// and disable them.
//===================================================================
export class Collection {

    // Internal node used to implement the binary search tree of Buildings,
    // organized by BCode.
    struct Node {
        Building* b;
        Node* left;
        Node* right;
        Node( const std::string& code, const std::string& name );
        ~Node();
        std::string getCode() const;
        void insert( const std::string& code, const std::string& name );
        Building* findBuilding( const std::string& code ) const;
        void print( std::ostream& out ) const;
        //void deleteAll();
    };

public:
    Collection();
    ~Collection();
    void insert( const std::string& code, const std::string& name );
    void remove( const std::string& code );
    Building* findBuilding( const std::string& code ) const;
    //void deleteAll();
    friend std::ostream& operator<< ( std::ostream& out, const Collection& c );

private:
    Collection( const Collection& ) = delete;
    Collection( Collection&& ) = delete;
    Collection& operator=( const Collection& ) = delete;
    Collection& operator=( Collection&& ) = delete;

    Node* root; // root of the BST
};

export std::ostream& operator<<( std::ostream& out, const Collection& tree );
