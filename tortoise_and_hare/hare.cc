export module hare;
import racer;

export
class Hare : public Racer {
    unsigned tickCount;

  public:
    Hare();
    void tick() override;
};
