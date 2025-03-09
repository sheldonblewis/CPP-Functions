import <iostream>;
import list;
using namespace std;


int main() {
    const size_t MAX_NUM_LISTS = 3;
    const size_t MAX_NUM_ITERATORS = 5;
   
    List lists[MAX_NUM_LISTS];
    List::Shuffleator *iters[MAX_NUM_ITERATORS]{nullptr}; 
        
    char command;
    size_t index1, index2;
    int value;

    while ( cin >> command ) {
        switch( command ) {
        case 'c': 
            { 
                cin >> index1 >> index2;
                delete iters[index2];
                iters[index2] = new List::Shuffleator{lists[index1].begin()};
            }
            break;

        case 'e': 
            { 
                cin >> index1 >> index2;
                delete iters[index2];
                iters[index2] = new List::Shuffleator{lists[index1].end()};
            }
            break;

        case 'a': 
            {
                cin >> index1 >> value;
                lists[index1].addToFront( value );
            }
            break;

        case 'g': 
            {
                cin >> index1;
                cout << *(*iters[index1]) << endl;
            }
            break;

        case '+': 
            {
                cin >> index1;
                ++(*iters[index1]);
            }
            break;

        case '=': 
            {
                cin >> index1 >> index2;
                cout << boolalpha << !(*iters[index1] != *iters[index2]) << endl;
            }
            break;

        case 'p': 
            {
                cin >> index1;
                cout << lists[index1] << endl;
            }
            break;

        } // switch
    } // while

    for (size_t i = 0; i < MAX_NUM_ITERATORS; ++i ) delete iters[i];
} // main
