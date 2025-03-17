export module allcaps;
import textprocessor;
import <iostream>;
import <string>;

export class AllCaps: public TextProcessor {
    TextProcessor *component;
    public:
    // Constructor. The parameter comp holds the previously constructed pipeline.
    AllCaps(TextProcessor *comp) : component(comp) {}

    // Pass the new input source down the pipeline.
    void setSource(std::istream *inp) {
        component->setSource(inp);
    }

    // Convert any lower-case letters in the word into upper-case letters.
    std::string getWord() override {
        std::string word = component->getWord();
        for (char &ch : word) {
            if (ch >= 'a' && ch <= 'z') {
                ch = std::toupper(ch);
            }
        }
        return word;
    }

    // When deleted, ensure deletion of the encapsulated component.
    ~AllCaps() override {
        delete component;
    }
};
