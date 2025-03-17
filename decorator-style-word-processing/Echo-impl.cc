module echo;
import <iostream>;
import <string>;
import textprocessor;

Echo::Echo(): source{nullptr} {}

void Echo::setSource( std::istream *in ) { source = in; }

std::string Echo::getWord() {
    std::string s;
    *source >> s;
    return s;
}
