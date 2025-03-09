export module drone;
import <iostream>;
import <compare>;
import position;

export class Drone {
    Position cur; // current position
    Direction dir;  // direction facing
    int numSteps; // total number of steps walked by the drone
  public:
    // Initializes a drone in the position (0,0)
    Drone();
    ~Drone();

    // Moves the drone forward by the number of steps in the current direction.
    // Number of steps must be a positive number.
    void forward(int steps = 1);

    // Moves the drone backward by the number of steps in the current direction.
    // Number of steps must be a positive number.
    void backward(int steps = 1);

    // Turns the drone 90 degrees leftwards.
    void left();

    // Turns the drone 90 degrees rightwards.
    void right();

    // Returns the current position  
    Position current() const;

    // Returns the current direction
    Direction direction() const;

    // Returns the total number of steps walked by the drone
    int totalDistance() const;
};

// Returns std::strong_ordering::equal if lhs == rhs. Checks x-coordinate first, then
// y-coordinate, then direction facing. Performs minimal number of checks.
export std::strong_ordering operator<=>(const Drone& lhs, const Drone& rhs);

// Prints the current status of the drone to out in the format:
//     Current position: (ew,ns), facing <direction>
// where <direction> is North, East, South, or West.
export std::ostream &operator<<(std::ostream &out, const Drone &drone);
