export module count;
import textprocessor;
import <iostream>;
import <string>;

export class Count: public TextProcessor {
    TextProcessor *component;
    char target;
    int counter;
    public:
        // Constructor takes the inner pipeline and the target character.
        Count(TextProcessor *comp, char t) : component(comp), target(t), counter(1) {}

    void setSource(std::istream *inp) override {
        component->setSource(inp);
    }

    // Replace each occurrence of target in the word with the counter (which may be more than one digit).
    std::string getWord() override {
        std::string word = component->getWord();
        std::string result;
        for (char ch : word) {
            if (ch == target) {
                result += std::to_string(counter);
                counter++;
            } else {
                result.push_back(ch);
            }
        }
        return result;
    }

    ~Count() override {
        delete component;
    }
};
