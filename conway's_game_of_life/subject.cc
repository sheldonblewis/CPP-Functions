#include "subject.h"
#include "observer.h"
#include <vector>
#include <algorithm>

void Subject::attach( Observer *o ) { observers.emplace_back(o); }

void Subject::notifyObservers() {
    for ( auto &ob : observers ) ob->notify( *this );
} // Subject::notifyObservers

std::string Subject::getObserverNames() {
    std::string nameList{};
    std::vector<std::string> names{};
    for ( auto &ob : observers ) names.emplace_back( ob->getName() );
    std::sort( names.begin(), names.end() );
    for ( auto n: names ) if ( n.size() > 0 ) nameList += n + " ";
    return nameList;
} // Subject::getObserverNames
