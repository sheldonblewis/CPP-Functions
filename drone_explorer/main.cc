import <iostream>;
import <string>;
import <compare>;
import position;
import drone;
using namespace std;

static const int MAX_NUM_DRONES = 5;

int main() {
    Drone d[MAX_NUM_DRONES];
    Drone* curDrone = nullptr;
    char c;
    int i, j;
    while (cin >> c) {
        switch(c) {
            case 's':
                cin >> i;
                curDrone = &d[i];
                break;
            case 'f':
                cin >> i;
                curDrone->forward(i);
                break;
            case 'b':
                cin >> i;
                curDrone->backward(i);
                break;
            case 'l':
                curDrone->left();
                break;
            case 'r':
                curDrone->right();
                break;
            case 'p':
                cout << *curDrone << endl;
                break;
            case 't':
                cout << curDrone->totalDistance() << endl;
                break;
            case 'c': 
                {
                    cin >> i >> j;
                    auto result = d[i] <=> d[j];
                    cout << d[i] << " ";
                    if (result == 0) cout << "==";
                    else if (result < 0) cout << "<";
                    else cout << ">";
                    cout << " " << d[j] << endl;
                    break;
                }
        } // switch
    } // while
} // main
