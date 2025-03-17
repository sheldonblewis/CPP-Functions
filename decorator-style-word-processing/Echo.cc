export module echo;
import <iostream>;
import <string>;
import textprocessor;

// Used to obtain the next word from the current input stream and pass it back up the pipeline. Takes the role of the ConcreteComponent class from the UML class model for the Decorator design pattern. It is the only class that reads in input from an input stream.

export class Echo: public TextProcessor {
    std::istream *source;  // current input stream

  public:
    Echo(); // default ctor

    // Change the input stream source to the new one passed in as parameter "inp".
    void setSource( std::istream *inp ) override;

    // Returns the next word from the input stream. Length of the returned string must be > 0 
    // unless the EOF exception has been raised.
    std::string getWord() override;
};

