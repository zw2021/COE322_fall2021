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
      cout << datavalue << ", ";
      if (has_next()){
          tail_ptr -> print(false);
          cout << ">>\n" ;
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

    /* Given a reference (pointer to pointer)
to the head of a list and an int, inserts
a new node on the front of the list. */
void push(Node** head_ref, int new_data)
{
    /* 1. allocate node */
    Node* new_node = new Node();

    /* 2. put in the data */
    new_node->data = new_data;

    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);

    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Given a node prev_node, insert a new node after the given
prev_node */
void insertAfter(Node* prev_node, int new_data)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
        cout<<"The given previous node cannot be NULL";
        return;
    }

    /* 2. allocate new node */
    Node* new_node = new Node();

    /* 3. put in the data */
    new_node->data = new_data;

    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;
}

/* Given a reference (pointer to pointer) to the head
of a list and an int, appends a new node at the end */
void append(int new_data)
{
    Node** head_ref = NULL;
    /* 1. allocate node */
    Node* new_node = new Node();

    Node *last = *head_ref; /* used in step 5*/

    /* 2. put in the data */
    new_node->data = new_data;

    /* 3. This new node is going to be
    the last node, so make next of
    it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty,
    then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
    {
        last = last->next;
    }

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

// This function prints contents of
// linked list starting from head
void printList(Node *node)
{
    while (node != NULL)
    {
        cout<<" "<<node->data;
        node = node->next;
    }
}
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