// Declares two pointers of type (Racer*), one pointing to a Hare object and one to a Tortoise object,
// and runs a race between them. The program will then read a positive integer from standard input
// that specifies the number of units, N, that the race will last. The race lasts until one of the
// racers has covered N units of distance. Your main program should run a loop that keeps calling
// the tick method of each Racer, stopping when one of them reaches N units of distance. Print out
// "Tie" if they both reach N units of distance in the same time; otherwise print out either
// "Hare" or "Tortoise" to indicate the winner.


import racer;
import tortoise;
import hare;
import <iostream>;
using namespace std;

int main() {

    Racer *hare = new Hare();
    Racer *tortoise = new Tortoise();
    unsigned N;

    cin >> N;

    while (hare->getDistance() < N && tortoise->getDistance() < N) {
        hare->tick();
        tortoise->tick();
    }

    if (hare->getDistance() >= N && tortoise->getDistance() >= N) {
        cout << "Tie" << endl;
    } else if (hare->getDistance() >= N) {
        cout << "Hare" << endl;
    } else {
        cout << "Tortoise" << endl;
    }

    delete hare;
    delete tortoise;
}
