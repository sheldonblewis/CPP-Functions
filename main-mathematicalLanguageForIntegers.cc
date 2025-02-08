// to compile:
// g++ -std=c++20 -Wall -fmodules-ts -c integerLanguage.cc
// g++ -std=c++20 -Wall -fmodules-ts -c integerLanguage-impl.cc
// g++ -std=c++20 -Wall -fmodules-ts -o mathematicalLanguageForIntegers main-mathematicalLanguageForIntegers.cc integerLanguage.o integerLanguage-impl.o

import intset;
import <iostream>;
using namespace std;

// Valid commands: n,  p <ind>, & <ind1> <ind2>, | <ind1> <ind2>, 
//                 = <ind1> <ind2>, s <ind1> <ind2>, c <ind1> <elem>,
//                 a <ind1> <elem>, r <ind1> <elem>, d <ind1>
int main() { 
    IntSet sets[5];
    char c;
    int lhs, rhs;

    while ( cin >> c ) {        
        switch( c ) {
            case 'n': // Reads in values for IntSet at lhs (clears previous data, if any).
                cin >> lhs;
                sets[lhs].clearAll();
                std::cin >> sets[lhs];
                break;
         
            case 'p': // Prints IntSet at lhs.
                cin >> lhs;
                cout << sets[lhs] << endl;
                break;

            case '&': // Prints intersection of lhs and rhs.       
                cin >> lhs >> rhs; 
                cout << (sets[lhs] & sets[rhs]) << endl;
                break;

            case '|': // Prints union of lhs and rhs.  
                cin >> lhs >> rhs;
                cout << ( sets[lhs] | sets[rhs] ) <<endl;
                break;

            case '=': // Prints "equal" if lhs == rhs, otherwise "not equal".    
                cin >> lhs >> rhs;
                cout << ( sets[lhs] == sets[rhs]? "equal" : "not equal" ) << endl;
                break;

            case 's': // Prints "subset" if rhs is a subset of lhs, otherwise "not subset".
                cin >> lhs >> rhs;
                cout << ( sets[lhs].isSubset( sets[rhs] )? "subset" : "not subset" ) << endl;
                break;

            case 'c': // Prints "true" if lhs contains element rhs, "false" otherwise. 
                cin >> lhs >> rhs;
                cout << ( sets[lhs].contains( rhs )? "true" : "false" ) << endl;
                break;

            case 'a': // Add elem rhs to set lhs.       
                cin >> lhs >> rhs;
                sets[lhs].add( rhs );
                break;

            case 'r': // Remove elem rhs from set lhs.          
                cin >> lhs >> rhs;
                sets[lhs].remove( rhs );
                break;

            case 'd': // Clears all elements from set lhs.
                cin >> lhs;
                sets[lhs].clearAll();
                break;
        } // switch
    } // while
} // main
