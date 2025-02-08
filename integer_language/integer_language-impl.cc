module intset;
import <iostream>;
using namespace std;

IntSet::IntSet() : elements{nullptr}, size{0}, capacity{0} {}

IntSet::~IntSet() { delete[] elements; }

void IntSet::clearAll() {
    delete[] elements;
    elements = nullptr;
    size = 0;
    capacity = 0;
}

void IntSet::expandCapacity() {
    int newCapacity = (capacity == 0) ? 5 : capacity * 2;
    int* newElements = new int[newCapacity];

    for (int i = 0; i < size; ++i) {
        newElements[i] = elements[i];
    }

    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

IntSet IntSet::operator|( const IntSet &other ) const {
    IntSet result;

    // add all elements from this set
    for (int i = 0; i < size; ++i) {
        result.add(elements[i]);
    }

    // add elements from other set if not already present
    for (int i = 0; i < other.size; ++i) {
        result.add(other.elements[i]);
    }

    return result;
}

IntSet IntSet::operator&( const IntSet &other ) const {
    IntSet result;

    // add elements that are present in both sets
    for (int i = 0; i < size; ++i) {
        if (other.contains(elements[i])) {
            result.add(elements[i]);
        }
    }

    return result;
}

bool IntSet::operator==( const IntSet &other ) const {
    if (size != other.size) return false;

    // ensure all elements match (order doesn't matter)
    for (int i = 0; i < size; ++i) {
        if (!other.contains(elements[i])) return false;
    }

    return true;
}

bool IntSet::isSubset( const IntSet &s ) const {
    for (int i = 0; i < size; ++i) {
        if (!s.contains(elements[i])) return false;
    }
    return true;
}

bool IntSet::contains( int e ) const {
    for (int i = 0; i < size; ++i) {
        if (elements[i] == e) return true;
    }
    return false;
}

void IntSet::add( int e ) {
    if (contains(e)) return;  // avoid duplicates
    if (size == capacity) expandCapacity();
    elements[size++] = e;
}

void IntSet::remove( int e ) {
    for (int i = 0; i < size; ++i) {
        if (elements[i] == e) {
            elements[i] = elements[--size];  // replace with last element
            return;
        }
    }
}

istream& operator>>( istream& in, IntSet& is ) {
    is.clearAll();

    int value;
    while (in >> value) {
        is.add(value);
    }

    // clear any non-integer input character and recover stream state
    in.clear();
    in.ignore(1000000, '\n');
    return in;
}

ostream& operator<<( ostream& out, const IntSet& is ) {
    // simple selection sort implementation for sorting elements
    for (int i = 0; i < is.size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < is.size; ++j) {
            if (is.elements[j] < is.elements[minIndex]) {
                minIndex = j;
            }
        }
        // swap the elements
        if (minIndex != i) {
            int temp = is.elements[i];
            is.elements[i] = is.elements[minIndex];
            is.elements[minIndex] = temp;
        }
    }

    // print the sorted elements
    out << "(";
    if (is.size > 0) {
        out << is.elements[0];
    }
    for (int i = 1; i < is.size; ++i) {
        out << ", " << is.elements[i];
    }
    out << ")";
    return out;
}
