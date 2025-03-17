import <iostream>;
import <fstream>;
import <sstream>;
import <string>;
import textprocessor;
import echo;
import doublewords;
import dropfirst;
import allcaps;
import count;

using namespace std;


int main() {
    istream *in = nullptr;

    // Turns on the raising of exceptions when the fail or the eof bit get set for std::cin.
    cin.exceptions( ios::failbit|ios::eofbit );
    string s;

    try {
        // Process each command from std::cin until we run out.
        while ( getline( cin, s ) ) {
            // Declare these outside the try-catch block so that they're available after the catch.
            TextProcessor *tp = nullptr;

            istringstream iss{s};
            iss.exceptions( ios::failbit ); // raise exception if fails
            string fname;
            iss >> fname;
            if ( fname == "stdin" ) { 
                in = &cin; 
            } else {
                in = new ifstream{ fname };
                if ( in->fail() ) {
                    std::cerr << "Unable to open file " << fname << std::endl;
                    delete in;
                    in = nullptr;
                    break;
                } // if
            } // if

            // Turns on the raising of exceptions when the fail or the eof bit get set for "in".
            in->exceptions( ios::failbit | ios::eofbit );

            // Pipeline starts with the concrete component, an Echo object instance.
            tp = new Echo{};

            // Build up the pipeline of decoration objects, adding each one to the front of the pipeline in turn. Stop when the istringstream runs out of input.
            try {
                string dec;
                while ( iss >> dec ) {
                    if ( dec == "dropfirst" ) {
                        int n;
                        iss >> n;
                        tp = new DropFirst(tp, n);
                    } else if ( dec == "doublewords" ) {
                        tp = new DoubleWords(tp);
                    } else if ( dec == "allcaps" ) {
                        tp = new AllCaps(tp);
                    } else if ( dec == "count" ) {
                        string param;
                        iss >> param;
                        char c = param[0];
                        tp = new Count(tp, c);
                    } // if
                } // while
            } catch (ios::failure&) {} 

            // Pass the input source down the pipeline to the concrete component.
            tp->setSource( in );

            // Process the input from the new source until we run out. Number each line as we go.
            try {
                string word;
                int lineNum = 1;
                while (true) {
                    word = tp->getWord();
                    cout << lineNum++ << ":\t" << word << endl;
                } // while
            } catch (ios::failure&) {}
                 
            if (in != &cin) delete in;
            delete tp; // clean up the pipeline

        } // while
    } catch (ios::failure&) {}
} // main
