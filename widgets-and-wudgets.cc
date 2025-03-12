import <iostream>;
import <string>;
import <utility>;
using namespace std;

class Widget {
 protected:
  string name;
 public:
  virtual void identify() const {
    cout << "I am a widget!  My name is " << name << "!" << endl;
  }
  Widget(const string &name): name{name} {}
  Widget(const Widget &other) : name{other.name} {
    cout << "I am a widget being copied!" << endl;
  }
  Widget(Widget &&other) noexcept : name{std::move(other.name)} {
    cout << "I am a widget being moved!" << endl;
    other.name = "";
  }
  virtual ~Widget() {};
};

class Wudget: public Widget {
 protected:
  string nickname;
 public:
  void identify() const override {
    cout << "I am a wudget!  My name is " << name << "!  My nickname is " << nickname << "!" << endl;
  }
  Wudget(const string &name, const string &nickname): Widget{name}, nickname{nickname} {}
  Wudget(const Wudget &other) : Widget{other}, nickname{other.nickname} {
    cout << "I am a wudget being copied!" << endl;
  }
  Wudget(Wudget &&other) noexcept : Widget{std::move(other)}, nickname{std::move(other.nickname)} {
    cout << "I am a wudget being moved!" << endl;
    other.nickname = "";
  }
};

class WidgetGathering {
  Widget chiefWidget;
  Wudget chiefWudget;
  int numAttendees;
  Widget **attendees;

 public:
  WidgetGathering(const string &chiefWidgetName, const string &chiefWudgetName,
                  const string &nickname, int numAttendees):
    chiefWidget{chiefWidgetName},
    chiefWudget{chiefWudgetName, nickname},
    numAttendees{numAttendees},
    attendees{new Widget*[numAttendees]} {
    for (int i=0; i < numAttendees; ++i) {
      cout << "Widget or wudget?" << endl;
      string which;
      cin >> which;
      if (which == "widget") {
        string name;
        cout << "Name?" << endl;
        cin >> name;
        attendees[i] = new Widget{name};
      }
      else { // wudget
        string name, nickname;
        cout << "Name and nickname?" << endl;
        cin >> name >> nickname;
        attendees[i] = new Wudget{name, nickname};
      }
    }
  }
  WidgetGathering(const WidgetGathering &other) : chiefWidget{other.chiefWidget}, chiefWudget{other.chiefWudget}, numAttendees{other.numAttendees} {
    cout << "Copying the gathering:" << endl;
    attendees = new Widget *[numAttendees];
    for (int i = 0; i < numAttendees; ++i) {
      if (dynamic_cast<Wudget *>(other.attendees[i])) {
        attendees[i] = new Wudget{*dynamic_cast<Wudget *>(other.attendees[i])};
      } else {
        attendees[i] = new Widget{*other.attendees[i]};
      }
    }
  }
  WidgetGathering(WidgetGathering &&other) noexcept : chiefWidget{std::move(other.chiefWidget)}, chiefWudget{std::move(other.chiefWudget)}, numAttendees{other.numAttendees}, attendees{other.attendees} {
    cout << "Moving the gathering" << endl;
    other.numAttendees = 0;
    other.attendees = nullptr;
  }
  void identify() const {
    cout << "Chief widget:" << endl;
    chiefWidget.identify();
    cout << "Chief wudget:" << endl;
    chiefWudget.identify();
    cout << "Attendees:" << endl;
    for (int i = 0; i < numAttendees; ++i) {
      attendees[i]->identify();
    }
  }
  ~WidgetGathering() {
    for (int i = 0; i < numAttendees; ++i) {
      delete attendees[i];
    }
    delete [] attendees;
  }
};

int main() {
  string chiefWidgetName, chiefWudgetName, nickname;
  cout << "Chief widget name?" << endl;
  cin >> chiefWidgetName;
  cout << "Chief wudget name and nickname?" << endl;
  cin >> chiefWudgetName >> nickname;
  int n = 0;
  cout << "Number of attendees?" << endl;
  cin >> n;
  WidgetGathering wg{chiefWidgetName, chiefWudgetName, nickname, n};

  cout << "The gathering:" << endl;
  wg.identify();

  cout << "Copying the gathering:" << endl;
  WidgetGathering wg2 = wg;

  cout << "The copied gathering:" << endl;
  wg2.identify();

  cout << "Moving the gathering" << endl;
  WidgetGathering wg3 = std::move(wg);

  cout << "The moved gathering:" << endl;
  wg3.identify();

  cout << "The moved-from gathering:" << endl;
  wg.identify();
}
