import <iostream>;
import <iomanip>;
import seqit;
using namespace std;

int fib( int n ) {
    return n <= 2 ? 1 : fib( n-1 ) + fib( n-2 );
}

int pow2( int n ) {
    return n == 0 ? 1 : 2 * pow2( n-1 );
}

void printRange( SeqIt & begin, SeqIt & end ) {
    while ( begin != end ) {
        cout << *begin << " ";
        ++begin; 
    }
    cout << endl;
}

int main() {
    int (*foo)(int);
    foo = fib;
    SeqIt myStart{ 5, foo };
    SeqIt myEnd{ 10, foo };
    printRange( myStart, myEnd );
    myStart = SeqIt{ 0, pow2 };
    myEnd = SeqIt{ 10, pow2 };
    printRange( myStart, myEnd );

    // Iterator comparisons:
    cout << boolalpha << ( SeqIt{5, fib} != SeqIt{5, fib} ) << endl;
    cout << boolalpha << ( SeqIt{5, fib} != SeqIt{5, pow2} ) << endl;
    cout << boolalpha << ( SeqIt{10, fib} != SeqIt{5, fib} ) << endl;
} // main
