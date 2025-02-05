import <iostream>;
using namespace std;


struct Node {
  int value;
  Node *left = nullptr;
  Node *right = nullptr;
  int level;
  
  Node (int *leafValues, int level);
  ~Node();
};


int maximin(Node &node);
int minimax(Node &node);


int main(){
  int leafValues[8] = {-5, 7, -9, 2, -3, 4, 8, 1};
  Node *root = new Node{leafValues, 0};
  root->value = minimax(*root);
  cout << root->value << endl;
  delete root;
  return 0;
}


int leafIndex = 0;

Node::Node(int * leafValues, int level) : level{level} {
  if ( this->level < 3 ){
    this->left = new Node{leafValues, (this->level + 1)};
    this->right = new Node{leafValues, (this->level + 1)};
  } else {
    this->value = leafValues[leafIndex++];
  }
}

int minimax(Node &node) {
  if (node.left == nullptr && node.right == nullptr) {
    return node.value;
  }
  int leftEval = maximin(*node.left);
  int rightEval = maximin(*node.right);

  //Assign result of max evaluation
  node.value = max(leftEval, rightEval);
  return node.value;
}

int maximin(Node &node) {
  if (node.left == nullptr && node.right == nullptr) {
    return node.value;
  }
  int leftEval = minimax(*node.left);
  int rightEval = minimax(*node.right);

  //Assign result of min evaluation
  node.value = min(leftEval, rightEval);
  return node.value;
}

Node::~Node() {
	delete this->left;
	delete this->right;
}
