import <iostream>;
import <fstream>;
import <string>;
import <vector>;
using namespace std;

class Observer;
class Subject {
  vector<Observer*> observers;

 public:
  void attach(Observer *o) { observers.emplace_back(o); }
  void detach(Observer *o) {
    for (auto it = observers.begin(); it != observers.end();) {
      if (*it == o) it = observers.erase(it);
      else ++it;
    }
  }
  void notifyObservers();
  virtual ~Subject() = 0;
};

Subject::~Subject() {}

class NewsOutlet: public Subject {
  string name;
  ifstream source;
  string headline;
 public:
  NewsOutlet(const string &name, const string &sourceName):
    name{name}, source{sourceName} {}
  string getName() const { return name; }
  // getNews:  return statement asks for the result of converting source
  // to bool.  True indicates success, false indicates failure, i.e., there
  // is no more news.
  bool getNews() { getline(source, headline); return bool{source}; }
  string getState() const { return headline; }
};

class Observer {
 public:
  virtual void notify(Subject *whoFrom) = 0;
  virtual ~Observer() {}
};

// Information on the "inline" keyword can be found at https://www.geeksforgeeks.org/inline-functions-cpp/
inline void Subject::notifyObservers() { for (auto o : observers) o->notify(this); }

class InformedCitizen: public Observer {
  string interest;  // The topic of interest
  vector<NewsOutlet*> sources;  // Observed news sources

public:
  // Constructor to initialize the interest
  InformedCitizen(const string &interest): interest{interest} {}

  // Attach a news source
  void addNewsSource(NewsOutlet *source) {
    sources.emplace_back(source);
    source->attach(this);
  }

  // Notify method: called when a news outlet publishes a headline
  void notify(Subject *whoFrom) override {
    NewsOutlet *source = dynamic_cast<NewsOutlet*>(whoFrom);
    if (source) {
      string headline = source->getState();
      if (headline.find(interest) != string::npos) {
        cout << "Heard about " << interest << " from " << source->getName() << endl;
        cout << "Headline was " << headline << endl;
      }
    }
  }
};

int main() {
  NewsOutlet tv{"TV", "tv.txt"}, socialMedia{"Social Media", "social.txt"};

  InformedCitizen ic{"science"};
  ic.addNewsSource(&tv);
  ic.addNewsSource(&socialMedia);

  bool tvDone = false, socialMediaDone = false;
  while(!tvDone && !socialMediaDone) {
    tvDone = !tv.getNews();
    socialMediaDone = !socialMedia.getNews();

    if (!tvDone) tv.notifyObservers();
    if (!socialMediaDone) socialMedia.notifyObservers();
  }
}
