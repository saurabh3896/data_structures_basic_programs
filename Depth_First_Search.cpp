#include <iostream>
#include <cstdlib>
using namespace std;
#define SIZE 20

class ver{
public:
  int flag;                                   //flag to mark the current node and flag is set to 0 if the node is unmarked
  int info;
  class ver *next;
  ver();
};
class ver *vertex_start[SIZE];

ver::ver(){
  flag = 0;
}

struct node{
  int data;
  struct node *next;
};
struct node *start;

class stack{
public:
  void push(int input);
  bool isEmpty();
  void pop();
  void display();
  int viewtop();
  void rec(int output_array[], int tot_vertices, class ver *traverse);
  stack();
};
class stack mystack;

stack::stack(){                               //constructor to intialize the start pointer to NULL(every in the array of structs) and flag = 0 i.e. the node is unmarked
  start = NULL;
  cout << "Stack Initialized" << endl;
}

void stack::push(int input){
  int insert_data;
  struct node* ptr;
  ptr = new (struct node);
  if(start == NULL){
    ptr -> data = input;
    ptr -> next = NULL;
    start = ptr;
  }
  else{
    struct node* temp;
    temp = start;
    ptr -> data = input;
    ptr -> next = NULL;
    while(temp -> next != NULL){
      temp = temp -> next;
    }
    temp -> next = ptr;
  }
  //cout << "Data inserted Successfully" << endl;
}

bool stack::isEmpty(){
  if(start == NULL){
    return true;
  }
  else{
    return false;
  }
}

int *flag_array;

void stack::pop(){
  struct node *ptr, *prev;
  if(start == NULL){
    cout << "Stack Empty...Nothing to pop" << endl;
    return;
  }
  prev = NULL;
  ptr = start;
  while(ptr -> next != NULL){
    prev = ptr;
    ptr = ptr -> next;
  }
  if(prev == NULL){
    start = ptr -> next;
    delete ptr;
  }
  else{
    prev -> next = ptr -> next;
    delete ptr;
  }
  //cout << "Data popped Successfully" << endl;
}

int stack::viewtop(){
  if(start == NULL){
    cout << "Stack Empty" << endl;
    return -1;
  }
  struct node *ptr = start;
  while(ptr != NULL){
    ptr = ptr -> next;
  }
  return ptr -> data;
}

void stack::display(){
  struct node *ptr = start;
  if(ptr == NULL){
    cout << "Stack Empty !" << endl;
    return;
  }
  while(ptr != NULL){
    cout << ptr -> data << " -> ";
    ptr = ptr -> next;
  }
  cout << "End of Stack" << endl;
}


void stack::rec(int output_array[], int n, ver* traverse){
  int i, counter = 0;
  while(mystack.isEmpty() != 1){
    mystack.pop();
    output_array[counter] = traverse -> info;
    cout << output_array[counter] << " Value hai be" << endl;
    counter++;
    while(traverse -> next != NULL){
      if(flag_array[(traverse -> next -> info) - 1] == 0){
        traverse = traverse -> next;
        flag_array[traverse -> info - 1] = 1;
        mystack.push(traverse -> info);
        for(i = 0;i < n;i++){
          if(vertex_start[i] -> info == traverse -> info){
            traverse = vertex_start[i];
            flag_array[traverse -> info - 1] = 1;
          }
          else{
            ;
          }
          rec(output_array, n, traverse);
        }
      }
      else{
        traverse = traverse -> next;
        if(traverse -> next == NULL){
          return;
        }
      }
    }
  }
}

int main(){
  int i, j, k, n, size, neighbour, counter = 0;
  int output_array[50];
  cout << "Enter the no. of vertices in the tree : ";
  cin >> n;
  int array[n];
  flag_array = new int[n];                                                   //array declaration with size = input given by user
  for(i = 0;i < n;i++){
    flag_array[i] = 0;
  }
  for(i = 0;i < n;i++){
    vertex_start[i] = new (class ver);
    class ver *tempnode = new (class ver);
    tempnode -> info = i + 1;
    vertex_start[i] = tempnode;
    cout << vertex_start[i] -> info;
  }
  for(i = 0;i < n;i++){
    cout << "Enter the number of neighbours of vertex " << i + 1 << " : ";
    cin >> size;
    if(size > n - 1){
      cout << "Invalid Cases" << endl;
      return 0;
    }
    for(j = 0;j < size;j++){
      cout << "Enter neighbour number " << j + 1 << " : ";
      cin >> neighbour;
      class ver *temp, *ptr;
      temp = new (class ver);
      ptr = vertex_start[i];
      temp -> info = neighbour;
      while(ptr -> next != NULL){
        ptr = ptr -> next;
      }
      ptr -> next = temp;
    }
  }
  class ver *traverse = new (class ver);
  traverse = vertex_start[0];
  flag_array[traverse -> info - 1] = 1;
  mystack.push(traverse -> info);
  mystack.rec(output_array, n, traverse);
  return 0;
}
