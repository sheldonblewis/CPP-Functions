export module doublewords;
import textprocessor;
import <iostream>;
import <string>;

export class DoubleWords: public TextProcessor {
    TextProcessor *component;
    bool duplicate; // flag to indicate if we should return the previous word
    std::string lastWord;
    public:
        // Constructor initializes the underlying component.
        DoubleWords(TextProcessor *comp) : component(comp), duplicate(false), lastWord("") {}

    void setSource(std::istream *inp) override {
        component->setSource(inp);
    }

    // Alternate between returning a new word from the pipeline and duplicating it.
    std::string getWord() override {
        if (duplicate) {
            duplicate = false;
            return lastWord;
        } else {
            lastWord = component->getWord();
            duplicate = true;
            return lastWord;
        }
    }

    ~DoubleWords() override {
        delete component;
    }
};
