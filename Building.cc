export module building;
import bcode;

import <iostream>;
import <string>;

//============================================================
// Building ADT
// Buildings cannot be copied or moved so make those private operations
// and disable them.
//============================================================

export class Building {
  public:
    Building( const BCode code, const std::string& name);
    std::string getCode() const;
    void setCode( const std::string& code );
    std::string getName() const;
    void setName( const std::string& name );
  private:
    Building& operator=( const Building& ) = delete;
    Building& operator=( Building&& ) = delete;
    Building( const Building& ) = delete;
    Building( Building&& ) = delete;

    BCode code;
    std::string name;
};

// Comparison operator is used in storing Buildings in a Collection.
export bool operator<( const Building& b1, const Building& b2 );

export std::istream& operator>>( std::istream& in, Building* b );
export std::ostream& operator<<( std::ostream& out, const Building& b );
