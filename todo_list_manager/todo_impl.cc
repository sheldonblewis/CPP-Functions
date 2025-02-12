module todo;
import <utility>;
using namespace std;

/* === Task class === */
const int childrenCapacity = 5;
int nextId = 0;  // global variable counting created Task

Task::Task(const std::string &description): 
  description{description}, id{nextId++}, done{false}, parent{nullptr}, 
  children{new Task*[childrenCapacity]}, childrenLength{0} 
{}

Task::Task(): 
  description{""}, id{0}, done{false}, parent{nullptr}, 
  children{new Task*[childrenCapacity]}, childrenLength{0} 
{}

/* --- Big 5 operations --- */

Task::Task(const Task &other) 
    : description{other.description}, id{other.id}, done{other.done}, parent{nullptr}, 
        children{new Task*[childrenCapacity]}, childrenLength{other.childrenLength} {

    // deep copy of children
    for (int i = 0; i < childrenLength; ++i) {
        children[i] = new Task{*other.children[i]};
        children[i]->parent = this;
    }
}

Task::Task(Task &&other) 
    : description{std::move(other.description)}, id{other.id}, done{other.done}, parent{other.parent}, 
        children{other.children}, childrenLength{other.childrenLength} {
    
    // nullify the moved object's children array to avoid double deletion
    other.children = nullptr;
    other.childrenLength = 0;
}

Task &Task::operator=(const Task &other) {
    if (this == &other) return *this; // self-assignment check

    // clean
    for (int i = 0; i < childrenLength; ++i) {
        delete children[i];
    }
    delete[] children;

    // copy
    description = other.description;
    id = other.id;
    done = other.done;
    parent = nullptr;
    childrenLength = other.childrenLength;

    // allocate new array and deep copy children
    children = new Task*[childrenCapacity];
    for (int i = 0; i < childrenLength; ++i) {
        children[i] = new Task{*other.children[i]};
        children[i]->parent = this;
    }

    return *this;
}

Task &Task::operator=(Task &&other) {
    if (this == &other) return *this; // self-assignment check

    // clean
    for (int i = 0; i < childrenLength; ++i) {
        delete children[i];
    }
    delete[] children;

    // move
    description = std::move(other.description);
    id = other.id;
    done = other.done;
    parent = other.parent;
    children = other.children;
    childrenLength = other.childrenLength;

    // nullify moved object
    other.children = nullptr;
    other.childrenLength = 0;

    return *this;
}

Task::~Task() {
    for (int i = 0; i < childrenLength; ++i) {
        delete children[i];
    }
    delete [] children;
}


/* --- Accessor and mutator methods --- */

const std::string &Task::getDescription() const {
    return description;
}

void Task::setDescription(const std::string &_desc) {
    description = _desc;
}

const int &Task::getId() const {
    return id;
}

void Task::setId(const int &_id) {
    id = _id;
}

const bool Task::getDone() const {
    return done;
}

void Task::setDone(const bool &_done) {
    done = _done;
}

Task *Task::getParent() const {
    return parent;
}

void Task::setParent(Task *_parent) {
    parent = _parent;
}

const int Task::getLength() const {
    return childrenLength;
}

void Task::print(std::ostream &out, int identLevel) const {
    for (int i = 0; i < identLevel; ++i) {
        out << "  ";
    }
    if (id != 0) {
        out << this->id << ". [";
        if (this->getDone()) out << 'X';
        out << "] " << this->description << std::endl;
    } else {
        out << this->description << std::endl;
    }
    for (int i = 0; i < childrenLength; ++i) {
        children[i]->print(out, identLevel + 1);
    }
    
}

/* --- Operations with children --- */

void Task::addChild(Task *other) {
    children[childrenLength] = other;
    ++childrenLength;
}

void Task::removeChild(Task *other) {
    for (int i = 0; i < childrenLength; ++i) {
        if (children[i] == other) {
            for (int j = i; j < childrenLength-1; ++j) {
                children[j] = children[j+1];
            }
            children[childrenLength-1] = nullptr;
            --childrenLength;
            break;
        }
    }
}

Task *Task::findChild(std::string &description) {
    for (int i = 0; i < childrenLength; ++i) {
        if (children[i]->getDescription() == description) {
            return *(children+i);
        }
    }
    return nullptr;
}

Task *Task::findChildId(int &id) {
    for (int i = 0; i < childrenLength; ++i) {
        if (children[i]->getId() == id) {
            return *(children+i);
        }
    }
    return nullptr;
}

/* === Task output operator === */

std::ostream &operator<<(std::ostream &out, const Task &task) {
    task.print(out);
    return out;
}



List::List(): root{new Task{"ToDo"}}, cur{root}, clip{nullptr} {}

List::~List() {
    delete clip;
    delete root;
}

void List::printCurrent() {
    cout << "Task \"" << cur->getDescription() << "\" is now the current task." << endl;
}

void List::print() {
    cout << *cur;
}

void List::addChild(string description) {
    if (cur->getLength() != childrenCapacity) {
        Task *newTask = new Task{description};
        newTask->setParent(cur);
        cur->addChild(newTask);
        cur = newTask;
        printCurrent();
    } else {
        std::cout << "No room for new tasks!" << std::endl;
    }
}

void List::deleteCur() {
    if (cur == root) {
        cerr << "List cannot be removed." << endl;
        return;
    }
    Task *tmp = cur;
    cur = tmp->getParent();
    cur->removeChild(tmp);
    delete tmp;
    printCurrent();
}

void List::parent() {
    if (cur->getParent() == nullptr) {
        cerr << "Current task is already the upper level task." << endl;
        return;
    }
    cur = cur->getParent();
    printCurrent();
}

void List::up() {
    cur = root;
    printCurrent();
}

void List::setDescription(string option) {
    cur->setDescription(option);
    cout << "Task " << cur->getId() << " description set to \"" << option << "\"." << endl;
}

void List::setDone(bool done) {
    cur->setDone(done);
    if (done) {
        cout << "Task \"" << cur->getDescription() << "\" is done!" << endl;
    } else {
        cout << "Task \"" << cur->getDescription() << "\" is not done!" << endl;
    }
}

void List::findChild(string option) {
    Task *tmp = cur->findChild(option);
    if (tmp == nullptr) {
        cerr << "Task \"" << option << "\" not found." << endl;
        return;
    }
    cur = tmp;
    printCurrent();
}

void List::findChildId(int option) {
    Task *tmp = cur->findChildId(option);
    if (tmp == nullptr) {
        cerr << "Task with id " << option << " not found." << endl;
        return;
    }
    cur = tmp;
    printCurrent();
}

void List::cut() {
    if (cur == root) {
        cerr << "List cannot be cut." << endl;
        return;
    }
    // remove task from parent
    Task *parent = cur->getParent();
    parent->removeChild(cur);
    if (clip == nullptr) {
        // using move constructor
        clip = new Task{std::move(*cur)};
    } else {
        // using move assignment operator
        *clip = std::move(*cur);
    }
    // delete original task
    delete cur;
    cur = parent;
    cout << "Task \"" << clip->getDescription() << "\" is now in the clipboard." << endl;
    printCurrent();
}

void List::copy() {
    if (cur == root) {
        cerr << "List cannot be copied." << endl;
        return;
    }
    // copy task to clipboard
    if (clip == nullptr) {
        // using copy constructor
        clip = new Task{*cur};
    } else {
        // using copy assignment operator
        *clip = *cur;
    }
    cout << "Task \"" << clip->getDescription() << "\" is now in the clipboard." << endl;
}

void List::paste() {
    if (clip == nullptr) {
        cerr << "The clipboard is empty." << endl;
        return;
    } else if (cur->getLength() != childrenCapacity) {
        // copy task from clipboard as a new child of the current task
        Task *newTask = new Task{*clip};  // using copy constructor
        newTask->setParent(cur);
        cur->addChild(newTask);
        cur = newTask;
        printCurrent();
    } else {
        std::cout << "No room for new tasks!" << std::endl;
    }  
}
