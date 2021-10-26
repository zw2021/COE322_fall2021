#include <iostream>
#include <memory>
#include <vector>
using namespace std;

/*
 * HELPFUL SOURCE:
 * https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
 *
 * Authors
 * Nick Delurgio npd429
 * Pavan Shukla pas3488
 * Zoelle Wong zfw65
 * */

class Node {
 private:
  int datavalue{0};
  shared_ptr<Node> tail_ptr{nullptr}; 
public:
  Node *next;
  int data;
  Node() {};
  Node(int value): datavalue(value) {};
  void set_tail( shared_ptr<Node> tailvalue ) {
    tail_ptr = tailvalue;
  };
  int list_length() {
    if (tail_ptr==nullptr)
      return 1;
    else 
      return 1 + tail_ptr->list_length();
  };
  int value() { return datavalue; };
  bool has_next() {return tail_ptr!=nullptr; };
  void print(bool i_am_first = true){
      if(i_am_first){ // optional argument
            cout << "<< " ;
      }
      cout << datavalue;
      if (has_next()){
          cout << ",";
          tail_ptr -> print(false);
      }else{
          cout << ">>\n";
      }
      };

  int Sort(shared_ptr<Node> newtail){
      Node* cur; // current node
      Node* tail; // tail node

    if (tail_ptr == nullptr){
        // base case; first node is larger
          set_tail(newtail);
   }

   else if((tail_ptr >= cur) & (tail_ptr <= tail)){
       // case when node is in between current and tail
        tail_ptr -> Sort(newtail);
   }
   else{
       // case when node is greater than the tail
       tail_ptr -> append(newtail);
   };
  }

  int append(shared_ptr<Node> newtail){
       if (tail_ptr == nullptr){
          set_tail(newtail);
       }
       else{
          tail_ptr -> append(newtail);
       }
  }
  // head of list is always 0. numbers you're inserting is 0
  // numbers you're inserting is more than the current.
  // always in the case
  // case 1; NO TAIL - append
  // case 2: between current and next insert
  // case 3: more than next then insert tail


// value of the current one and value of the tail pointer
// base case, no tail just insert node
// current is a tail, look at info of current, info of tail does it go in between?
// current and tail info, more than just insert node after tail  - recursive step
};

int main() {
  auto
    first = make_shared<Node>(23),
    second = make_shared<Node>(45),
    third = make_shared<Node>(32);

  first->append(second);
  first -> append(third);
  cout << "List length: "
       << first->list_length() << endl;
  first->print();
  return 0;
}

// first node has the lowest value!!!