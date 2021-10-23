//
// Created by huang on 10/21/2021.
//

#include <iostream>
#include <memory>
using namespace std;

class Node {
    private:
        int datavalue{0};
        shared_ptr<Node> tail_ptr{nullptr};

    public:
        int data;
        Node* next;

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
            return 0;
        }
};
/* merge sort that splits a list in half, sorts it, then merges it */
// merge 2 sorted lists
Node* mergeSortedLists(Node* list1, Node* list2){
    Node* result = NULL;

    // base case - if there's nothing in side lists 1 and 2
    if (list1 == NULL) // list 1 is empty, so return list 2
        return list2;
    else if (list2 = NULL)
        return list1; // list 2 is empty, so return list 1

    // merge lists 1 and 2 recursively
    if (list1 -> data <= list2 -> data){
        result = list1;
        result-> next = mergeSortedLists(list1->next, list2);
    }else{
        result = list2;
        result-> next = mergeSortedLists(list1, list2->next);
    }
    return result;
}

// split list into 2 lists
void splitList(Node* source, Node** front, Node** back){
    Node* p1;
    Node* p2;
    p2 = source;
    p1 = source -> next;

    // p1 is incremented twice and p2 is incremented once
    while(p1 != NULL){
        p1 = p1->next;
        if(p1 != NULL){
            p1 = p2->next;
            p1 = p1->next;
        }
    }

    // p2 is at midpoint
    *front = source;
    *back = p2-> next;
    p2->next = NULL;

}

// merge sort
void mergeSort(Node** thread){
    Node* head = *thread;
    Node* p1;
    Node* p2;
    // base case
    if((head == NULL) || (head-> next == NULL)){
        return;
    }
    // split list
        splitList(head, &p1, &p2);
    // sort lists
        mergeSort(&p1);
        mergeSort(&p2);
    // sorted list
        *thread = mergeSortedLists(p1, p2);

}
// Printing List.
void printList(Node* tnode){
    while (tnode != NULL) {
    cout << tnode->data << " ";
    tnode = tnode->next;
    }
}

// Push function for inserting nodes in the list.
void push(Node** thread, int new_data){
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = (*thread);
    (*thread) = new_node;
}

int main() {
auto
    first = make_shared<Node>(23),
    second = make_shared<Node>(45),
    third = make_shared<Node>(32);

    first->append(second);
    first -> append(third);
    cout << "List length: "
    << first->list_length() << endl;

    // Empty list
    Node* res = NULL;
    Node* MyList = NULL;

    // List: 10->4->15->1->2->12->54
    push(&MyList, 54);
    push(&MyList, 12);
    push(&MyList, 2);
    push(&MyList, 1);
    push(&MyList, 15);
    push(&MyList, 4);
    push(&MyList, 10);

cout << "Unsorted Linked List: ";
printList(MyList);
cout << "\n";

mergeSort(&MyList);

cout << "Sorted Linked List: ";
printList(MyList);

return 0;
}

// first node has the lowest value!!!