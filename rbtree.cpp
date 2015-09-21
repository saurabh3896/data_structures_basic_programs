#include <iostream>
#include <cstdlib>
using namespace std;

class red_black_node{
public:
  int *data;                                                //int *data declaration
  char color;                                               //char color having  'r' or 'b' color(R -> red and B -> Black)
  red_black_node *left_child;
  red_black_node *right_child;                              //declaring left_child, right_child and parent node to a red_black_node
  red_black_node *parent;
  red_black_node(){
    //null declaration as a sentinel node
    data = NULL;
    data = new (int);
    left_child = right_child = parent = NULL;               //constructor to Initialize the left_child, right_child amd parent pointer
  }
};

class red_black_tree{
public:
  red_black_node *root;                                     //declaring root pointer
  red_black_tree();                                         //constructor
  void insert(int *data);                                   //insert function
  red_black_node *search(int data, red_black_node *input);  //search function
  void print_tree(red_black_node *ptr);                     //print function
  void left_rotate(red_black_node *ptr);                    //left rotate function
  void right_rotate(red_black_node *ptr);                   //right rotate function
  void del(int del_data);
};
class red_black_tree T;

red_black_tree::red_black_tree(){
  root = new (class red_black_node);
  root = NULL;                                              //Initializing root = NULL
  cout << "red_black_tree Initialized !" << endl;
}

void red_black_tree::print_tree(red_black_node *ptr){       //function to print the tree according to postorder traversal
  red_black_node *current;
  current = ptr;                                            //setting current pointer the provided ptr pointer as arguments in the function(root for complete print)
  if(current == NULL){                                      //if tree is empty then return
    return;
  }
  print_tree(current -> left_child);                        //inorder traversal(recursively for left, right and print root's data)
  print_tree(current -> right_child);
  cout << *(current -> data) << " -> Color : " << current -> color << endl;
}

void red_black_tree::left_rotate(red_black_node *ptr){
  red_black_node *temp;
  temp = new (class red_black_node);                        //memory allocation
  temp = ptr -> right_child;                                //making temp == right_child
  ptr -> right_child = temp -> left_child;                  //now, setting right_child of ptr(input ptr) to the left child of temp
  if(temp -> left_child != NULL){
    temp -> left_child -> parent = ptr;                     //setting temp's left_child's parent if it is not NULL
  }
  temp -> parent = ptr -> parent;                           //setting temp's parent to the input ptr's parent
  if(ptr -> parent == NULL){
    T.root = temp;                                          //if(input ptr was root), then temp = root
  }
  else{
    if(ptr == ptr -> parent -> left_child){
      ptr -> parent -> left_child = temp;                   //if ptr was its parent's left child, then setting left child to temp
    }
    else{
      ptr -> parent -> right_child = temp;                  //vice-versa
    }
  }
  temp -> left_child = ptr;                                 //setting temp's left_child to ptr
  ptr -> parent = temp;                                     //setting ptr's parent to temp
}

void red_black_tree::right_rotate(red_black_node *ptr){     //opposite to left_rotate case
  red_black_node *temp = new (class red_black_node);
  temp = ptr -> left_child;
  ptr -> left_child = temp -> right_child;                  //now, setting left_child of ptr(input ptr) to the right_child of temp
  if(temp -> right_child != NULL){                          //setting temp's right_child's parent if it is not NULL
    temp -> right_child -> parent = ptr;
  }
  temp -> parent = ptr -> parent;                           //setting temp's parent to the input ptr's parent
  if(ptr -> parent == NULL){
    T.root = temp;                                          //if(input ptr was root), then temp = root
  }
  else{
    if(ptr == ptr -> parent -> left_child){                 //if ptr was its parent's left child, then setting left child to temp
      ptr -> parent -> left_child = temp;
    }
    else{                                                   //vice-versa
      ptr -> parent -> right_child = temp;
    }
  }
  temp -> right_child = ptr;                                //setting temp's right_child to ptr
  ptr -> parent = temp;                                     //setting ptr's parent to temp
}

void red_black_tree::insert(int *input){
  red_black_node *ptr;
  ptr = new (class red_black_node);                         //memory allocation to the newly declared pointer
  //ptr -> data = new (int);                                //memory allocation to the data pointer
  *(ptr -> data) = *input;                                  //setting ptr's *data equal to *input(arguments in the insert function)
  if(T.root == NULL){
    ptr -> color = 'B';                                     //if root == NULL, then set root = ptr with color = 'BLACK'
    ptr -> parent = NULL;
    T.root = ptr;
    cout << "Root Added !" << endl;
    return;                                                 //return after setting root = newly inserted node(ptr)
  }
  if(search(*input, T.root) != NULL){                       //insert only if the search returns NULL, i.e. , no duplicates in the tree must be there
    cout << "Data Already Present !" << endl;
    return;                                                 //return without inserting again
  }
  red_black_node *temp;
  temp = new (class red_black_node);
  temp = T.root;                                            //Initializing newly declared pointer to root and traversing to left or right child in case input > || < temp -> input
  while(1){
    if(*input < *(temp -> data)){
      if(temp -> left_child != NULL){
        temp = temp -> left_child;                          //if *input < *(temp -> data)
      }
      else{
        break;                                              //break from the infinite while loop if NULL pointer ahead
        }
      }
    else{
      if(temp -> right_child != NULL){
        temp = temp -> right_child;                         //if *input > *(temp -> data)
      }
      else{
        break;                                              //break from the infinite while loop if NULL pointer ahead
      }
    }
  }
  ptr -> parent = temp;                                     //setting parent of ptr as the lastmost node in the above traversal
  if(*input < *(temp -> data)){
    temp -> left_child = ptr;                               //if(*input > *(temp -> data)) : temp -> right_child = ptr, else : temp -> left_child = ptr
  }
  else{
    temp -> right_child = ptr;
  }
  ptr -> color = 'R';                                       //setting the color of the newly inserted node to red color always
  while(ptr != T.root && ptr -> parent -> color == 'R'){    //while till x is not root or x's parent is red(color)
    if(ptr -> parent == ptr -> parent -> parent -> left_child){
      red_black_node* temp;                                 //case when ptr's parent is left child of its (ptr's parent's)  parent
      temp = new (class red_black_node);
      temp = ptr -> parent -> parent -> right_child;        //setting the sibling of ptr's parent to temp(and making cases)
      if(temp != NULL){                                     //if temp is NOT NULL
        if(temp -> color == 'R'){                           //if it is red
          ptr -> parent -> color = 'B';
          temp -> color = 'B';                              //set the uncle to black
          ptr -> parent -> parent -> color = 'R';           //setting colors to approppriate values
          ptr = ptr -> parent -> parent;                    //upsetting ptr to its parent's parent
        }
        else{                                               //uncle if black
          if(ptr == ptr -> parent -> right_child){
            ptr = ptr -> parent;
            T.left_rotate(ptr -> parent -> parent);         //left-rotate if ptr is right_child only(after setting ptr to its parent)
          }
          ptr -> parent -> color = 'B';                     //in all other cases, set its parent to B, its parent to R and right_rotate
          ptr -> parent -> parent -> color = 'R';
          T.right_rotate(ptr -> parent -> parent);
        }
      }
      else{                                                 //case if uncle is a sentinel - node, i.e., a NULL node(color black)
        if(ptr == ptr -> parent -> right_child){
          ptr = ptr -> parent;                              //left-rotate if ptr is right_child only(after setting ptr to its parent)
          T.left_rotate(ptr -> parent -> parent);
        }
        ptr -> parent -> color = 'B';
        ptr -> parent -> parent -> color = 'R';
        T.right_rotate(ptr -> parent -> parent);            //in all other cases, set its parent to B, its parent to R and right_rotate
      }
    }
    else{                                                   //if ptr's parent is the right_child of its(ptr's parent's) parent
      red_black_node *temp;
      temp = new (class red_black_node);
      temp = ptr -> parent -> parent -> left_child;         //setting the other sibling(left_child of ptr -> parent -> parent) to temp
      if(temp != NULL){                                     //if temp is not NULL
        if(ptr -> parent -> parent -> left_child -> color == 'R'){
          ptr -> parent -> color = 'B';                     //if temp is RED
          temp -> color = 'B';                              //set uncle to black
          ptr -> parent -> parent -> color = 'R';           //ptr -> parent -> color = B, ptr -> parent -> parent -> color = R
          ptr = ptr -> parent -> parent;                    //upshift ptr to ptr -> parent -> parent
        }
        else{                                               //uncle is already black
          if(ptr == ptr -> parent -> left_child){
            ptr = ptr -> parent;                            //if ptr is left_child of its parent, upshift and right_rotate it
            T.right_rotate(ptr);
          }
          else{
            ptr -> parent -> color = 'B';                   //other wise, parent -> color = B, parent -> parent -> color = R and left_rotate the ptr
            ptr -> parent -> parent -> color = 'R';
            T.left_rotate(ptr);
          }
        }
      }
      else{                                                 //if the temp(sibling of ptr -> parent, here left_child) is NULL, i.e. is a sentinel - node
        if(ptr == ptr -> parent -> left_child){
          ptr = ptr -> parent;                              //upshift and right_rotate
          T.right_rotate(ptr -> parent -> parent);
        }
        ptr -> parent -> color = 'B';                       //set the color of the parent of the ptr to Black
        ptr -> parent -> parent -> color = 'R';             //other wise set color to approppriate as above and left_rotate
        T.left_rotate(ptr -> parent -> parent);
      }
    }
  }
  if(ptr == T.root){
    ptr -> color = 'B';                                     //while breaks either due to x being root or x -> parent -> color = B, but here only first one changes property i.e., color of root
  }                                                         //set the root to black again
  cout << "Data Inserted successfully !" << endl;
}

red_black_node *red_black_tree::search(int search_data, red_black_node *input){
  red_black_node *ptr;                                      //function to return red_black_node ptr with searchdata
  ptr = input;
  if(ptr == NULL){                                          //if ptr == NULL, no match found, return NULL
    cout << "Not Found !" << endl;
    return NULL;
  }
  else{
    if(search_data == *(ptr -> data)){                      //if searchdata found, report the corresponding ptr
      cout << "Found !" << endl;
      return ptr;
    }
    else if(search_data > *(ptr -> data)){
      search(search_data, input -> right_child);            //if less, recursively call for left child or vice-versa
    }
    else{
      search(search_data, input -> left_child);             //recursive call
    }
  }
  cout << "Data not Found !" << endl;
  return NULL;
}

void red_black_tree::del(int del_data){
    red_black_node *temp;
    temp = search(del_data, T.root);
    if(temp == NULL){
      cout << "Element Not Found !" << endl;
      return;
    }
    else{
      if(temp -> left_child == NULL && temp -> right_child == NULL){
        if(temp == root){
          root = NULL;
        }
        else{
          if(temp == temp -> parent -> left_child){
            temp -> parent -> left_child = NULL;
          }
          else if(temp == temp -> parent -> right_child){
            temp -> parent -> right_child = NULL;
          }
          else if(temp == root){
            root = NULL;
          }
          temp -> parent = NULL;
          delete temp;
        }
      }
      else if((temp -> left_child == NULL) && (temp -> right_child != NULL)){
        if(temp == root){
          root -> right_child = NULL;
        }
        else{
          temp -> right_child -> parent = temp -> parent;
          if(temp == temp -> parent -> right_child){
            temp -> parent -> right_child = temp -> right_child;
          }
          else{
            temp -> parent -> left_child = temp -> right_child;
          }
        }
        temp -> left_child = NULL;
        temp -> right_child = NULL;
        temp -> parent = NULL;
        delete temp;
      }
      else if((temp -> left_child != NULL) && (temp -> right_child == NULL)){
        if(temp == root){
          root -> left_child = NULL;
        }
        else{
          temp -> left_child -> parent = temp -> parent;
          if(temp == temp -> parent -> right_child){
            temp -> parent -> right_child = temp -> left_child;
          }
          else{
            temp -> parent -> left_child = temp -> left_child;
          }
        }
        temp -> left_child = NULL;
        temp -> right_child = NULL;
        temp -> parent = NULL;
        delete temp;
      }
      else if(temp -> left_child != NULL && temp -> right_child != NULL){
        red_black_node *p = temp -> left_child;
        while(p -> right_child != NULL){
          p = p -> right_child;
        }
        temp -> data = p -> data;
        if(p -> left_child != NULL){
          p -> left_child -> parent = p -> parent;
          if(p == p -> parent -> left_child){
            temp -> left_child = p -> left_child;
          }
          else{
            temp -> right_child = p -> right_child;
          }
        }
        else{
          if(p == temp -> left_child){
            temp -> left_child = NULL;
          }
          else{
            temp -> right_child = NULL;
          }
        }
        delete p;
      }
    }
  }


int main(){
  int insert_data, choice, search_data, del_data;
  while(1){
    cout << "1.Enter 1 to insert into the red_black_tree.\n2.Enter 2 to search data into the tree.\n3.Display.\n4.Enter 4 to delete.\n5.Enter anything to exit.\n";
    cout << "Enter the choice : ";                          //user prompt
    cin >> choice;
    switch(choice){                                         //switch case
      case 1: cout << "Enter the data you want to insert into the tree : ";
              cin >> insert_data;
              T.insert(&insert_data);                       //pass by reference
              break;
      case 2: cout << "Enter the element you want to search into the tree : ";
              cin >> search_data;                           //search any element in the red_black_tree
              T.search(search_data, T.root);
              break;
      case 3: T.print_tree(T.root);                         //print the given tree in inorder traversal way
              break;
      case 4: cout << "Enter the element to be deleted : ";
              cin >> del_data;
              T.del(del_data);
              break;
      default:cout << "Exiting..... " << endl;
              exit(0);
    }
  }
  return 0;
}
