export module list;
import <iostream>;

export class List {
    struct Node {
        int data;
        Node *next;
    };
    Node *theList;
    int length;

 public:
    class Shuffleator {
        Node *firstHalfPtr;
        Node *secondHalfPtr;
        bool fromFirstHalf;
        int count;
        int listLength;
        bool isEnd;

        Shuffleator(Node* start, int listLength, bool isEnd = false);

    public:
        int operator*() const;
        Shuffleator& operator++();
        bool operator!=(const Shuffleator &other) const;

        friend class List;
    };

    List();
    ~List();
    void addToFront(int value);
    Shuffleator begin() const;
    Shuffleator end() const;
};

export std::ostream& operator<<(std::ostream& out, const List& lst);
