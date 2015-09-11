#include <iostream>
#include <cstdlib>
#define SIZE 20

using namespace std;

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

class queue{
public:
  void add(int input);
  void pop();
  void display();
  bool isEmpty();
  void rec(int output_array[], int tot_vertices, class ver *traverse);
  queue();
};
class queue Q;

queue::queue(){
  start = NULL;
  cout << "Queue Initialized" << endl;
}

void queue::add(int input){
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

void queue::pop(){
  struct node *ptr = start, *prev = NULL;
  if(ptr == NULL){
    cout << "Queue Empty...Nothing to pop" << endl;
    return;
  }
  start = ptr -> next;
  delete ptr;
  //cout << "Data popped Successfully" << endl;
}

bool queue::isEmpty(){
  if(start == NULL){
    return true;
  }
  else{
    return false;
  }
}

void queue::display(){
  struct node *ptr = start;
  if(ptr == NULL){
    cout << "Queue Empty" << endl;
    return;
  }
  while(ptr != NULL){
    cout << ptr -> data << " -> ";
    ptr = ptr -> next;
  }
  cout << "End of Queue" << endl;
}

int *flag_array;

void queue::rec(int output_array[], int n, ver* traverse){
  class ver *swap;
  int tell = 0;
  int i, counter = 0;
  while(Q.isEmpty() != 1){
    for(i = 0;i < n;i++){
      if(vertex_start[i] -> info == start -> data){
        traverse = vertex_start[i];
        flag_array[traverse -> info - 1] = 1;
      }
      else{
        ;
      }
    }
    output_array[counter] = start -> data;
    cout << output_array[counter] << " Value hai be" << endl;
    counter++;
    Q.pop();
    while(traverse -> next != NULL){
      if(flag_array[(traverse -> next -> info) - 1] == 0){
        traverse = traverse -> next;
        flag_array[traverse -> info - 1] = 1;
        Q.add(traverse -> info);
      }
      else{
        traverse = traverse -> next;
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
  Q.add(traverse -> info);
  Q.rec(output_array, n, traverse);
  /*for(k = 0;k < counter;k++){
    cout << output_array[k] << " -> ";
  }
  cout << "End Of Array" << endl;*/
  return 0;
}
