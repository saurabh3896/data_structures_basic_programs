#include <iostream>
#include <cstdlib>

using namespace std;

class treenode{           //class declaration
  int height;
  treenode *root;         //member variables include parent, leftchild and rightchild pointer to a node....each node is a tree
  treenode *parent;
  treenode *left_child;
  treenode *right_child;
public:
  treenode(){                           //constructor for initializing parent, leftchild and rightchild
    root = parent = left_child = right_child = NULL;
    cout << "Tree Initialized" << endl;
  }
  void insert(int insert_data);

  treenode *get_root(){                 //function to return root pointer
    return root;
  }

  treenode *search(int search_data);    //function to return pointer with height == searchdata
  void Delete(int del_data);            //function to delete node with provided data
  void print_tree(treenode *ptr);
};
class treenode TREE;                    //object declaration

void treenode::insert(int insert_data){
  treenode *current;
  treenode *node = new treenode;
  node -> height = insert_data;
  node -> parent = NULL;
  node -> left_child = NULL;
  node -> right_child = NULL;
  if(root == NULL){                         //if tree is empty
    root = node;
    return;
  }
  if(search(insert_data) == NULL){
    current = root;
  while(1){
    if(insert_data < current -> height){    //if data is less than current's height
      if(current -> left_child != NULL){    //if current has a leftchild
        parent = current;
        current = current -> left_child;
      }
      else
        break;
    }
    else{
      if(current -> right_child != NULL){   //if current has a rightchild(else case)
        parent = current;
        current = current -> right_child;
      }
      else
        break;
    }
  }
  node -> parent = current;                 //setting the parent pointer of node to current
  if(insert_data < current -> height){      //checking whether current was left or right child of its parent
    current -> left_child = node;
  }
  else{
    current -> right_child = node;
  }
  node -> left_child = NULL;
  node -> right_child = NULL;
  cout << "Data inserted successfully !" << endl;
  }
}

void treenode::print_tree(treenode *ptr){   //function to print the tree according to postorder traversal
  treenode *current;
  current = ptr;
  if(current == NULL){                      //if tree is empty then return
    cout << "Tree Empty !" << endl;
    return;
  }
  print_tree(current -> left_child);
  print_tree(current -> right_child);
  cout << current -> height << " -> ";
  cout << "End of Tree !" << endl;
  }

treenode* treenode::search(int search_data){    //function to return treenode ptr with searchdata
  treenode *current = root;
  if(current == NULL){                          //if tree is empty
    cout << "Tree Empty" << endl;
    return NULL;
  }
  while(current != NULL){                       //while to traverse to desired pointer depending on whether its data is lesser or greater than its parent's data
    if(search_data == current -> height){
      cout << "Found" << endl;
      return current;
    }
    else if(search_data > current -> height){
      current = current -> right_child;
    }
    else{
      current = current -> left_child;
    }
  }
  cout << "Data not found !" << endl;
  return NULL;
}

void treenode::Delete(int del_data){
  treenode *current;
  current = search(del_data);                   //function requires the pointer with the data to be deleted returned by search function
  cout << current -> height;
  if(search(del_data) == NULL){
    cout << "Data not found !" << endl;
    return;
  }
  if((current -> left_child == NULL) && (current -> right_child == NULL)){
    if(current == root){                                //if pointer has both children NULL and is root
      root = NULL;
    }
    else{
      if(current == current -> parent -> left_child){   //if its left child
        current -> parent -> left_child = NULL;
      }
      else{
        current -> parent -> right_child = NULL;        //if its right child
      }
      current -> parent = NULL;
    }
    delete current;                                     //free memory associated with current pointer
  }
  else if((current -> right_child != NULL) && (current -> left_child == NULL)){   //if rightchild is not NULL but left child is NULL
    current -> right_child -> parent = current -> parent;
    if(current == root){                                                          //if current is root
      root = current -> right_child;
    }
    else{
      if(current == current -> parent -> left_child){
        current -> parent -> left_child = current -> right_child;
      }
      else{
        current -> parent -> right_child = current -> right_child;
      }
    }
    current -> parent = NULL;
    current -> left_child = NULL;
    current -> right_child = NULL;
    delete current;
  }
  else if((current -> left_child != NULL) && (current -> right_child == NULL)){   //if leftchild is not NULL but right child is NULL
    current -> left_child -> parent = current -> parent;
    if(current == root){                                                          //if current is root pointer
      root = current -> left_child;
    }
    else{
      if(current == current -> parent -> left_child){                             //if current is leftchild of its parent
        current -> parent -> left_child = current -> left_child;
      }
      else{
        current -> parent -> right_child = current -> left_child;                  //else case
      }
      current -> parent = NULL;                                                    //breaking all links with other pointers
      current -> left_child = NULL;
      current -> right_child = NULL;
      delete current;                                               //freeing memory associated with current pointer
    }
  }
  else{                                                             //if both rightchild and leftchild are not NULL
    treenode *ptr;
    ptr = current -> left_child;
    while(ptr -> right_child != NULL){                              //traversing pointer to the rightmost child of the left child of the current pointer
      ptr = ptr -> right_child;
    }
    current -> height = ptr -> height;
    if(ptr -> left_child != NULL){                                  //if ptr has leftchild
      ptr -> left_child -> parent = ptr -> parent;
      if(ptr == current -> left_child){                             //if ptr didnt traverse to its right
        current -> left_child = ptr -> left_child;
      }
      else{
        ptr -> parent -> right_child = ptr -> left_child;
      }
    }
    else{                                                           //if ptr has both children NULL since rightchild is already NULL
      if(ptr == current -> left_child){
        current -> left_child = NULL;
      }
      else{
        ptr -> parent -> right_child = NULL;
      }
    }
    ptr -> parent = NULL;
    ptr -> left_child = NULL;
    ptr -> right_child = NULL;
    delete ptr;                                                     //freeing memory associated with the ptr pointer
    }
  }

int main(){
  int choice, insert_data, search_data, del_data;
  while(1){
    cout << "1.Enter 1 to insert data into the binary search tree.\n2.Enter 2 to search data into the tree.\n3.Enter 3 to display the binary search tree.\n4.Enter 4 to delete an element from the binary search tree.\n5.Enter 5 to exit.\n";
    cout << "Enter the choice : ";                                  //user prompt
    cin >> choice;
    switch(choice){                                                 //switch case
      case 1: cout << "Enter the data to be inserted into the tree : ";
              cin >> insert_data;
              TREE.insert(insert_data);
              break;
      case 2: cout << "Enter the element to be searched : ";
              cin >> search_data;
              TREE.search(search_data);
              break;
      case 3: TREE.print_tree(TREE.get_root());
              break;
      case 4: cout << "Enter the data to be deleted from the binary search tree : ";
              cin >> del_data;
              TREE.Delete(del_data);
              break;
      default:cout << "Very poor choice of words...." << endl;
              exit(0);
    }
  }
  return 0;
}
