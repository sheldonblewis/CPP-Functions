module bcode;
import <iostream>;
import <string>;
using namespace std;

// Assume BCode starts with a capital letter and is of length <= 3,
// consisting of capital letters and digits.
BCode::BCode( const string& code ) : code{code} {}
string BCode::getCode() const { return code; }
void BCode::setCode( const string& c ) { code = c; }

bool operator<( const BCode& bc1, const BCode bc2 ) { return bc1.getCode() < bc2.getCode(); }
bool operator==( const BCode& bc1, const BCode& bc2 ) { return !( bc1 < bc2 ) && !( bc2 < bc1 ); }
bool operator!=( const BCode& bc1, const BCode& bc2 ) { return !( bc1 == bc2 ); }
bool operator<=( const BCode& bc1, const BCode& bc2 ) { return bc1<bc2 || bc1==bc2; }
bool operator>( const BCode& bc1, const BCode& bc2 ) { return !( bc1 <= bc2 ); }
bool operator>=( const BCode& bc1, const BCode& bc2 ) { return !( bc1 < bc2 ); }

istream& operator>>( istream& in, BCode& bcode ) {
    string code;   
    in >> code;
    if ( !in.fail() ) bcode = BCode{ code };   
    return in;
}

ostream& operator<<( ostream& out, const BCode& bcode ) {
    out << bcode.getCode();
    return out;
}
