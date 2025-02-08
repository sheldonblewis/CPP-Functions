module building;
import bcode;
import <iostream>;
import <string>;
using namespace std;

Building::Building( const BCode code, const string& name) : 
    code{code}, name{name} {}
string Building::getCode() const { return code.getCode(); }
void Building::setCode( const string& c ) { code.setCode( c ); }
string Building::getName() const { return name; }
void Building::setName( const string& n ) { name = n; }

bool operator<( const Building& b1, const Building& b2 ) {
    if ( b1.getCode() < b2.getCode() ) return true;
    return false;
}

istream& operator>>( istream& in, Building* b ) {
    string code;
    string name;
    string name2;
    
    in >> code >> name;
    getline( in, name2 );
    b = new Building{ BCode{code},  name+name2 };
    
    return in;
} // operator>>

ostream& operator<<( ostream& out, const Building& b ) {
    out << b.getCode() << "\t" << b.getName();
    return out;
} // operator<<
