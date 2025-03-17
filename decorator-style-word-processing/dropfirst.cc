export module dropfirst;
import textprocessor;
import <iostream>;
import <string>;

export class DropFirst: public TextProcessor {
    TextProcessor *component;
    int n;
    public:
        // Constructor takes the inner text processor and the number of characters to drop.
        DropFirst(TextProcessor *comp, int num) : component(comp), n(num) {}

    void setSource(std::istream *inp) override {
        component->setSource(inp);
    }

    // Skip words that are too short. When a word is long enough, return the substring that omits the first n characters.
    std::string getWord() override {
        while (true) {
            std::string word = component->getWord();
            if (static_cast<int>(word.size()) > n) {
                return word.substr(n);
                // Otherwise, discard this word and try again.
            }
        }
    }
    
    ~DropFirst() override {
        delete component;
    }
};
