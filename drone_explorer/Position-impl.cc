module position;
import <iostream>;
import <compare>;
import <string>;
using namespace std;

ostream& operator<<(std::ostream& out, const Direction& dir) {
    static const string strValues[] = {"North", "East", "South", "West"};
    out << strValues[static_cast<int>(dir)];
    return out;
}

Position::Position(int ew, int ns): ew{ew}, ns{ns} {}

Position & Position::operator+=(const Position& rhs) {
    ew += rhs.ew;
    ns += rhs.ns;
    return *this;
}

Position & Position::operator-=(const Position& rhs) {
    ew -= rhs.ew;
    ns -= rhs.ns;
    return *this;
}

int Position::getEW() const { return ew; }
int Position::getNS() const { return ns; }

std::strong_ordering operator<=>(const Position& lhs, const Position& rhs) {
    if (auto cmp = lhs.getEW() <=> rhs.getEW(); cmp != 0) return cmp;
    return lhs.getNS() <=> rhs.getNS();
}

std::ostream &operator<<(std::ostream& out, const Position& pos) {
    out << "(" << pos.getEW() << "," << pos.getNS() << ")";
    return out;
}
