export module racer;

export
class Racer {
    unsigned int distance;
  public:
    Racer();
    unsigned getDistance() const;
    virtual void tick() = 0;
    void incDistance(unsigned inc);
};
