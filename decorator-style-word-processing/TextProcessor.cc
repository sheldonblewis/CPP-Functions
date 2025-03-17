export module textprocessor;
import <iostream>;
import <string>;

// The abstract base class for the Decorator design pattern. Takes the role of the Component class
// from the UML class model for the Decorator design pattern. Provides the interface to implement.

export class TextProcessor {
  public:
    // Passes the new input stream to use down the pipeline to the concrete component, Echo.
    virtual void setSource( std::istream *inp ) = 0;

    // Used to pass a request for another input word down the pipeline to the concrete component,
    // Echo. Returns a (possibly modified) word back up the pipeline to the main program, which
    // outputs it. Length of the returned string must be > 0 unless the EOF exception has been raised.
    virtual std::string getWord() = 0;

    // Destructor.
    virtual ~TextProcessor();
};
