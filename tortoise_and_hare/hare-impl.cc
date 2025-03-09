module hare;

Hare::Hare() : tickCount{0} {}
void Hare::tick() {
    ++tickCount;
    if (tickCount <= 10) {
        incDistance(2);
    } else if (tickCount > 40) {
        incDistance(2);
    }
}
