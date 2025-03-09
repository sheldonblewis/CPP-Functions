export module sparseRow;
import <iostream>;
import <utility>;
using std::size_t;

export class SparseRow {
  public:
    SparseRow( size_t numElements );
    SparseRow( const SparseRow& other );
    SparseRow( SparseRow&& other );
    virtual ~SparseRow();
    void set( size_t index, int value );
    int get( size_t index ) const;
    size_t getNumElements() const;

    // Requires that the two sparse rows have the same number of elements.
    // It is unspecified behaviour otherwise.
    SparseRow operator+( const SparseRow& other ) const;

  private:

    struct Node {
        size_t index;
        int value;
        Node* next;
        Node( size_t index, int value, Node* next = nullptr );
        Node( const Node& other );
        Node( Node&& other );
        ~Node();
    };

    Node* find( size_t index ) const; 
    
    Node* first, *last;
    size_t numElements;

  public:

    class Iterator {
        friend class SparseRow;
        Node* current;
        size_t position;
        size_t numElements;

        Iterator(Node* start, size_t pos, size_t total);
      public:
        bool operator!=( const Iterator& other ) const;
        int operator*() const;
        Iterator& operator++();
    };

    Iterator begin() const;
    Iterator end() const;
};

export std::ostream& operator<<( std::ostream& out, const SparseRow& row );
