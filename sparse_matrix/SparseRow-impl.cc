module sparseRow;

SparseRow::SparseRow( size_t numElements ) :
    first{nullptr}, last{nullptr}, numElements{numElements} {}
SparseRow::~SparseRow() { delete first; }

SparseRow::SparseRow( const SparseRow& other ) :
    first{other.first == nullptr? nullptr : new Node{*other.first} },
    last{nullptr},
    numElements{other.numElements}
{
    if ( other.last != nullptr ) {
        Node * tmp = first;
        while ( tmp->next != nullptr ) tmp = tmp->next;
        last = tmp;
    } // if
} // SparseRow::SparseRow

SparseRow::SparseRow( SparseRow&& other ) :
    first{other.first}, last{other.last}, numElements{other.numElements}
{ other.first = other.last = nullptr; }

size_t SparseRow::getNumElements() const { return numElements; }

void SparseRow::set( size_t index, int value ) {
    Node* ptr = find( index );
    if ( !ptr && value == 0 ) return;
    if ( ptr && value == 0 ) {
        if ( first == last && first == ptr ) {
            first = last = nullptr;
        } else if ( first != last && first == ptr ) {
            first = first->next;
        } else if ( first != last ) {
            Node* curr = first->next;
            Node* prev = first; 
            for (; curr != ptr; curr = curr->next, prev = prev->next );
            if ( last == ptr ) {
                last = prev;
                prev->next = nullptr;      
            } else {
                prev->next = curr->next;
            } // if
        } // if
        ptr->next = nullptr; 
        delete ptr;
        return;
    } // if
    
    if ( ptr ) {
        ptr->value = value;
        return;
    } // if

    Node* tmp = new Node{ index, value };
    if ( first == last && first == nullptr ) {
        first = last = tmp;
    } else {
        if ( index < first->index ) { 
            tmp->next = first;
            first = tmp;
        } else if ( last->index < index ) { 
            last->next = tmp;
            last = tmp;
        } else { 
            Node* curr = first->next;
            Node* prev = first; 
            while ( true ) {
                if ( index < curr->index ) {
                    tmp->next = curr;
                    prev->next = tmp;
                    break;
                } // if
                prev = curr;
                curr = curr->next;
            } // while
        } // if
    } // if
} // SparseRow::set

SparseRow::Node* SparseRow::find( size_t index ) const {
    for ( Node * ptr = first; ptr != nullptr; ptr = ptr->next ) {
        if ( ptr->index == index ) return ptr;
    } // for
    return nullptr;   
} // SparseRow::find

int SparseRow::get( size_t index ) const {
    if ( first == nullptr && last == nullptr ) return 0;
    if ( index < first->index || index > last->index ) return 0;
    Node *ptr = find( index );
    return ( ptr ? ptr->value : 0);
} // SparseRow::get

SparseRow SparseRow::operator+( const SparseRow& other ) const {
    if (numElements != other.numElements ) return SparseRow{0};
    SparseRow sp{numElements};
    SparseRow::Iterator it1 = begin(), it2 = other.begin();
    size_t idx = 0;
    while ( it1 != end() && it2 != other.end() ) {
        sp.set( idx++, *it1 + *it2 );
        ++it1;
        ++it2;
    } // while

    return sp;
} // SparseRow::operator+

SparseRow::Node::Node( size_t index, int value, Node* next ) :
    index{index}, value{value}, next{next} 
    {}

SparseRow::Node::Node( const Node& other ) :
    index{other.index}, value{other.value},
    next{other.next == nullptr? nullptr : new Node{*other.next}}
    {}

SparseRow::Node::Node( Node&& other ) :
    index{other.index}, value{other.value}, next{other.next}
    { other.next = nullptr; }

SparseRow::Node::~Node() { delete next; }

SparseRow::Iterator::Iterator(Node* start, size_t pos, size_t total) 
    : current{start}, position{pos}, numElements{total} {} // SparseRow::Iterator::Iterator

bool SparseRow::Iterator::operator!=( const Iterator& other ) const {
    return position != other.position;
} // SparseRow::Iterator::operator!=

int SparseRow::Iterator::operator*() const {
    return (current && current->index == position) ? current->value : 0;
} // SparseRow::Iterator::operator*

SparseRow::Iterator& SparseRow::Iterator::operator++() {
    ++position;
    if (current && current->index < position) {
        current = current->next;
    }
    return *this;
} // SparseRow::Iterator::operator++

SparseRow::Iterator SparseRow::begin() const {
    return Iterator(first, 0, numElements);
}

SparseRow::Iterator SparseRow::end() const {
    return Iterator(nullptr, numElements, numElements);
}

std::ostream& operator<<( std::ostream& out, const SparseRow& row ) {
    size_t numElements = row.getNumElements();
    size_t ctr = 1;
    out << "[ ";
    for ( auto elem: row ) {
        out << elem;
        if ( ctr < numElements ) out << ", ";
        ++ctr;
    } // for
    out << " ]";
    return out;
} // operator<<
