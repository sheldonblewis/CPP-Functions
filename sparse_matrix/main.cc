import sparseRow;
import <iostream>;
using namespace std;

int main() {
    const size_t MAX_SPARSE_ROWS = 5;
    SparseRow* rows[MAX_SPARSE_ROWS]{nullptr};
    char command;
    size_t index1, index2, numElems;
    int value;

    while ( cin >> command ) {
        switch( command ) {
        case 'c': 
            { 
                cin >> index1 >> numElems;
                delete rows[index1];
                rows[index1] = new SparseRow{numElems};
            }
            break;

        case 'i': 
            {
                cin >> index1 >> index2 >> value;
                rows[index1]->set( index2, value );
            }
            break;

        case 'g': 
            {
                cin >> index1 >> index2;
                cout << rows[index1]->get( index2 ) << endl;
            }
            break;

        case 'p': 
            {
                cin >> index1;
                cout << *rows[index1] << endl;
            }
            break;

        case '+': 
            {
                cin >> index1 >> index2;
                cout << (*rows[index1] + *rows[index2]) << endl;
            }
            break;

        } // switch
    } // while

    for ( size_t i = 0; i < MAX_SPARSE_ROWS; ++i ) delete rows[i];
} // main
