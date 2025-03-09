module seqit;
import <iostream>;

// Constructor
SeqIt::SeqIt(int start, int (*f)(int)) : index{start}, func{f} {}

// Dereference operator
int SeqIt::operator*() const {
    return func(index);
}

SeqIt &SeqIt::operator++() {
    ++index;
    return *this;
}

bool SeqIt::operator!=(const SeqIt &other) const {
    return index != other.index || func != other.func;
}
