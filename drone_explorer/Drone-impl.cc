module drone;
import <iostream>;
import <compare>;
import position;
using namespace std;

Drone::Drone(): cur{Position{0,0}}, dir{Direction::NORTH}, numSteps{0} {}

Drone::~Drone() {}

void Drone::forward(int steps) {
    if (dir == Direction::NORTH) { 
        cur += Position{0, steps};
    } else if (dir == Direction::EAST) { 
        cur += Position{steps, 0};
    } else if (dir == Direction::SOUTH) { 
        cur += Position{0, -steps};
    } else if (dir == Direction::WEST) {
        cur += Position{-steps, 0};
    } // if
    numSteps += steps;
} // Drone::forward

void Drone::backward(int steps) {
    if (dir == Direction::NORTH) {
        cur -= Position{0, steps};
    } else if (dir == Direction::EAST) {
        cur -= Position{steps, 0};
    } else if (dir == Direction::SOUTH) {
        cur -= Position{0, -steps};
    } else if (dir == Direction::WEST) {
        cur -= Position{-steps, 0};
    } // if
    numSteps += steps;
} // Drone::backward

void Drone::left() {
    int tmpdir = static_cast<int>(dir);
    tmpdir += 3;
    tmpdir %= 4;
    dir = static_cast<Direction>(tmpdir);
}

void Drone::right() {
    int tmpdir = static_cast<int>(dir);
    tmpdir += 1;
    tmpdir %= 4;
    dir = static_cast<Direction>(tmpdir);
}

Position Drone::current() const { return cur; }
Direction Drone::direction() const { return dir; }
int Drone::totalDistance() const { return numSteps; }

std::strong_ordering operator<=>(const Drone& lhs, const Drone& rhs) {
    if (auto cmp = lhs.current() <=> rhs.current(); cmp != 0) return cmp;
    return lhs.direction() <=> rhs.direction();
}

std::ostream &operator<<(std::ostream &out, const Drone &drone) {
  out << "[Current position: " << drone.current() << ", facing " << drone.direction() << ']';
  return out;
}
