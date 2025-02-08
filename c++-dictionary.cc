import <iostream>;
import <string>;
using namespace std;

struct Tuple {
    int key;
    std::string value;
};

struct DArray {
    int size;      // number of elements the array currently holds
    int capacity;  // number of elements the array could hold, given current
                   // memory allocation to contents
    Tuple *contents;
};

DArray readDArray() {
    DArray arr{0, 0, nullptr};

    while (true) {
        Tuple t;

        if (!(cin >> t.key)) {
            cin.clear();
            cin.ignore(1000000, '\n');
            break;
        }
        
        if (!(cin >> t.value)) {
            cin.clear();
            cin.ignore(1000000, '\n');
            break;
        }

        if (arr.size == arr.capacity) {
            int newCapacity = arr.capacity == 0 ? 5 : arr.capacity * 2;
            
            Tuple* newContents = new Tuple[newCapacity];

            for (int i = 0; i < arr.size; ++i) {
                newContents[i] = arr.contents[i];
            }

            delete[] arr.contents;
            arr.contents = newContents;
            arr.capacity = newCapacity;
        }

        arr.contents[arr.size++] = t;
    }

    return arr;
}

void addToDArray( DArray &arr ) {
    while (true) {
        Tuple t;

        if (!(cin >> t.key)) {
            cin.clear();
            cin.ignore(1000000, '\n');
            break;
        }

        if (!(cin >> t.value)) {
            cin.clear();
            cin.ignore(1000000, '\n');
            break;
        }

        if (arr.size == arr.capacity) {
            int newCapacity = arr.capacity == 0 ? 5 : arr.capacity * 2;
            
            Tuple* newContents = new Tuple[newCapacity];

            for (int i = 0; i < arr.size; ++i) {
                newContents[i] = arr.contents[i];
            }

            delete[] arr.contents;
            arr.contents = newContents;
            arr.capacity = newCapacity;
        }

        arr.contents[arr.size++] = t;
    }
}

void printDArray( const DArray &arr ) {
    if (arr.size == 0) {
        return;
    }

    cout << "(" << arr.contents[0].key << "," << arr.contents[0].value << ")";
    for (int i = 1; i < arr.size; ++i) {
        cout << " (" << arr.contents[i].key << "," << arr.contents[i].value << ")";
    }
    cout << endl;
}

// Valid commands are: r, +, p, or q. Each of the first 3 commands also takes a character argument
// used to specify which of the DArray objects is affected.

int main() { // Test harness for DArray functions.
    DArray a[4]{0,0,nullptr};

    while( true ) {
        char command, which;

        // Note: print prompt to stderr, so it doesn't clutter up the .out files.
        cerr << "Command?" << endl; 
        cin >> command;  // Reads r, +, p, or q
        if ( cin.eof() || command == 'q' ) break;
        cin >> which; // Reads a, b, c, or d.
        int index = which - 'a';

        switch( command ) {
            case 'r':
                delete [] a[index].contents;
                a[index] = {0,0,nullptr}; 
                a[index] = readDArray();
                break;
            case '+':
                addToDArray(a[index]);
                break;
            case 'p':
                printDArray(a[index]);
                cout << "Capacity: " << a[index].capacity << endl;
                break;
        } // switch
    } // while

    for ( int i = 0; i < 4; ++i ) delete [] a[i].contents;
    return 0;
} // main
