export module position;
import <iostream>;
import <compare>;
import <string>;

export enum class Direction {NORTH = 0, EAST, SOUTH, WEST};
// Note: Use the compiler-provided operator<=> for Direction.

// Outputs the string that is equivalent to the enumerated type's value.
export std::ostream &operator<<(std::ostream& out, const Direction& dir);


export class Position {
    int ew, ns;
  public:
    Position(int ew = 0, int ns = 0);

    // Adds rhs.ew to this position's ew and rhs.ns to this position's ns.
    Position& operator+=(const Position& rhs);

    // Subtracts rhs.ew from this position's ew and rhs.ns from this position's ns.
    Position& operator-=(const Position& rhs);

    int getEW() const;
    int getNS() const;

};

// Returns std::strong_ordering::equal if lhs == rhs. Checks x-coordinate first, then
// y-coordinate. Performs minimal number of checks.
export std::strong_ordering operator<=>(const Position& lhs, const Position& rhs);

// Prints the current values of the position to out in the format: (ew,ns)
export std::ostream &operator<<(std::ostream& out, const Position& pos);
