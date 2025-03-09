module racer;

Racer::Racer() : distance{0} {}
unsigned Racer::getDistance() const {
    return distance;
}
void Racer::incDistance( unsigned inc ) {
    distance += inc;
}
