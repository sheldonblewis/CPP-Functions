export module intset;
import <iostream>;

export struct IntSet {
    int* elements;     // pointer to dynamically allocated array of elements in the set
    int size;          // number of elements currently in the set
    int capacity;      // current capacity of the array (doubles if exceeded)

    IntSet();                                      // Constructor
    ~IntSet();                                     // Destructor
    void clearAll();                               // Resets set to be empty.
    IntSet operator|( const IntSet &other ) const; // Set union.
    IntSet operator&( const IntSet &other ) const; // Set intersection.
    bool operator==( const IntSet &other ) const;  // Set equality.
    bool isSubset( const IntSet &s ) const;        // True if s is a subset of *this.
    bool contains( int e ) const;                  // True if *this contains e.
    void add( int e );                             // Add e to this set.
    void remove( int e );                          // Remove e from this set.
    
    void expandCapacity();                         // expands array capacity if needed
};

// Input operator for IntSet.
// Continuously read int values from stdin and add to the passed IntSet. 
// Function stops when input contains a non-int value. Discard the first
// non-int character.
export std::istream& operator>>( std::istream& in, IntSet& is );

// Output operator for IntSet.
// Surrounds the values with parentheses, puts a comma between each value, 
// and outputs them in ascending order.
export std::ostream& operator<<( std::ostream& out, const IntSet& is );
