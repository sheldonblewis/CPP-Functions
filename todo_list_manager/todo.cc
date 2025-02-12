// print: Prints the current task to the standard output.
// add desc: Creates a new task with description specified by the argument, adds it as a child of the current task, and makes it the new current task.
// delete: Deletes the current task, removes it from its parent, and makes its parent the new current task.
// parent: Sets the parent of the current task as the new current task.
// up: Sets the topmost task (<document>) as the current task.
// desc desc: Sets the description attribute of the current task to desc.
// done: Sets the done attribute of the current task to true.
// undone: Sets the done attribute of the current task to false.
// find desc: Finds the first task that is a child of the current task and has the specified description. If such a task is found, it is set as the current task. Otherwise, it prints an error message.
// findId: id Finds the first task that is a child of the current task and has the specified id. If such a task is found, it is set as the current task. Otherwise, it prints an error message.
// cut: Removes the current task from its parent and moves it to the program’s internal clipboard. Sets its parent task as the current task.
// copy: Copies the current task to the program’s internal clipboard.
// paste: Adds a new child to the current task, whose contents are a copy of the task currently in the clipboard, and updates the pointers of the child and current task accordingly.
// quit: Quits the program.


export module todo;
import <iostream>;
import <string>;

export class Task {
    std::string description;  // the description of the Task
    int id;                   // the id attribute of the Task
    bool done;                // the done status of the Task
    Task *parent;             // pointer to the parent Task (or nullptr for the root ToDo Task, which does not have a parent)
    Task **children;          // array of children Task pointers
    int childrenLength;       // current number of children Tasks

    
  public:
    // Normal constructor
    Task(const std::string &description);
    Task();
    // Copy constructor
    Task(const Task &other);
    // Move constructor
    Task(Task &&other);
    // Copy assignment operator
    Task &operator=(const Task &other);
    // Move assignment operator
    Task &operator=(Task &&other);
    // Destructor
    ~Task();

    // Returns the value of the id field
    const int &getId() const;
    // Sets the value of the id field
    void setId(const int &_id);
    // Returns the value of the value field
    const std::string &getDescription() const;
    // Sets the value of the value field
    void setDescription(const std::string &_desc);
    // Returns the value of the parent field
    Task *getParent() const;
    // Sets the value of the parent field
    void setParent(Task *_parent);
    // Returns the value of the done field
    const bool getDone() const;
    // Sets the value of the done field
    void setDone(const bool &_done);
    // Returns the value of the childrenLength field
    const int getLength() const;

    // Prints this Task to out in the following format:
    // [] 1. Task description
    //      [] 2. Children 1
    //      [] ...
    // Note that the indentLevel starts at 0 for the first Task,
    // so, the first Task is printed without any trailing spaces.
    // For each children level, increase the indentLevel by 1.
    // For each indentLevel, add two spaces to the beginning of the line
    // If the id or value attributes are empty (""), do not print them.
    // If this Task does not have children, don't print anything for the ...children line.
    void print(std::ostream &out, int indentLevel = 0) const;

    // Adds other to the children array.
    void addChild(Task *other);
    // Removes other from the children array.
    // If other is not in the array, does nothing.
    // (Does NOT delete other).
    void removeChild(Task *other);
    // Returns the first Task in the children array whose description is equal to the supplied parameter.
	  // If no such Task is found, returns nullptr.
    Task *findChild(std::string &description);
    // Returns the first Task in the children array whose id is equal to the supplied parameter.
	  // If no such Task is found, returns nullptr.
    Task *findChildId(int &id); 
};

// Prints the Task to out by calling its print() method.
export std::ostream &operator<<(std::ostream &out, const Task &Task);


export class List {
    Task *root;
    Task *cur;
    Task *clip;
    void printCurrent();
  public:
    List();
    ~List();
    void print();                             // tests Task::print
    void addChild(std::string option);        // tests Task::addChild
    void deleteCur();                         // tests Task::removeChild
    void parent();                            // tests Task::getParent
    void up();                                // goes back to the Document level
    void setDescription(std::string option);  // tests Task::setDescription
    void setDone(bool done);                  // tests Task::setDone
    void findChild(std::string option);       // tests Task::findChild
    void findChildId(int option);             // tests Task::findChildId
    void cut();                               // moves current task to internal clipboard (tests move operations)
    void copy();                              // copies current task to internal clipboard (tests copy operations)
    void paste();                             // adds task from internal clipboard as a new child
};
