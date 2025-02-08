export module bcode;

import <iostream>;
import <string>;

//================================================
// BCode ADT
// Building codes could be duplicated on different campuses
// so copying and moving are possible. Leverage std::string
// move and copy operations applied by default compiler
// implementations
//================================================
export class BCode {
  public:
    BCode( const std::string& code );
    BCode( const BCode& obc ) = default;
    BCode( BCode&& obc ) = default;
    BCode& operator=( const BCode& obc ) = default;
    BCode& operator=( BCode&& obc ) = default;
    std::string getCode() const;
    void setCode( const std::string& newCode );
  private:
    std::string code;
};

// Comparison operators are used in storing Buildings in a Collection.
export bool operator<( const BCode& bc1, const BCode bc2 );
export bool operator==( const BCode& bc1, const BCode& bc2 );
export bool operator!=( const BCode& bc1, const BCode& bc2 );
export bool operator<=( const BCode& bc1, const BCode& bc2 );
export bool operator>( const BCode& bc1, const BCode& bc2 );
export bool operator>=( const BCode& bc1, const BCode& bc2 );

export std::istream& operator>>( std::istream& in, BCode& bcode );
export std::ostream& operator<<( std::ostream& out, const BCode& bcode );

