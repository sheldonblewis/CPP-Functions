module list;
import <iostream>;

List::Shuffleator::Shuffleator(Node* start, int listLength, bool isEnd)
    : firstHalfPtr(start), secondHalfPtr(start), fromFirstHalf(true), count(0), listLength(listLength) {
    for (int i = 0; i < listLength / 2; ++i) {
        secondHalfPtr = secondHalfPtr->next;
    }
    if (isEnd) {
        firstHalfPtr = nullptr;
        secondHalfPtr = nullptr;
        count = listLength;
    }
}

int List::Shuffleator::operator*() const {
    if (fromFirstHalf && firstHalfPtr) return firstHalfPtr->data;
    if (!fromFirstHalf && secondHalfPtr) return secondHalfPtr->data;
    return 0;
}

List::Shuffleator& List::Shuffleator::operator++() {
    if (count >= listLength) {
        firstHalfPtr = nullptr;
        secondHalfPtr = nullptr;
        return *this;
    }
    if (fromFirstHalf) {
        if (firstHalfPtr) firstHalfPtr = firstHalfPtr->next;
    } else {
        if (secondHalfPtr) secondHalfPtr = secondHalfPtr->next;
    }
    fromFirstHalf = !fromFirstHalf;
    count++;
    return *this;
}

bool List::Shuffleator::operator!=(const List::Shuffleator &other) const {
    return count != other.count;
}

List::Shuffleator List::begin() const {
    return Shuffleator(theList, length);
}

List::Shuffleator List::end() const {
    return Shuffleator(theList, length, true);
}

std::ostream& operator<<(std::ostream& out, const List& lst) {
    for (List::Shuffleator it = lst.begin(); it != lst.end(); ++it)
        out << *it << ' ';
    return out;
}

List::List() : theList{nullptr}, length{0} {}
List::~List() { delete theList; }

void List::addToFront(int value) {
    theList = new Node{value, theList};
    ++length;
}
