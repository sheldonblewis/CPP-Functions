export module seqit;
import <iostream>;

export class SeqIt {
    int index;
    int (*func)(int);
    
  public:
    SeqIt(int start, int (*f)(int));
    int operator*() const;
    SeqIt &operator++();
    bool operator!=(const SeqIt &other) const;
};
