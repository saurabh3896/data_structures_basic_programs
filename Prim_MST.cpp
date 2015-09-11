#include <iostream>
#include <cstdlib>
using namespace std;

int *flag_array;                                          //declaring flag array to keep track of the marked vertices

struct spanning{                                          //declaring struct spanning to create an object for an edge, that stores the weight of the edge and its start and end vertices
  int weight;
  int vertex[2];                                          //declaring an array of size two to store the end and start vertex of the edge
};

/******************************************************************************/
int size_counter = -1;                                    //setting the current size of the heap to be -1
struct spanning heap_array[20];                           //making a heap array for storing the edges of the data type "struct spanning"
/***********************Heap members declared Globally**************************/

void add(struct spanning object){                         //add() function to add the edges into the heap
  size_counter++;
  heap_array[size_counter] = object;
}

void min_heapify(int count){                              //min_heapify() to heapify each time an edge is added
  struct spanning hold;
  int temp;
  temp = count;
  while(heap_array[temp].weight < heap_array[(temp - 1)/2].weight){
    hold = heap_array[temp];                              //swapping till parent < child
    heap_array[temp] = heap_array[(temp - 1)/2];
    heap_array[(temp - 1)/2] = hold;
    temp = (temp - 1)/2;
  }
}

void del_min(){
  int i;
  struct spanning hold;
  hold = heap_array[0];
  heap_array[0] = heap_array[size_counter];              //swapping first edge with last and decreasing the size counter
  heap_array[size_counter] = hold;
  size_counter = size_counter - 1;
  for(i = 0;i <= size_counter;i++){                      //min_heapify() for each edge
    min_heapify(i);
  }
}

int main(){
  int no_of_vertices, no_of_edges, i, j, k, check_counter = 0;
  cout << "Enter the number of vertices : ";             //asking the user to input the number of vertices
  cin >> no_of_vertices;
  int adj_matrix[no_of_vertices][15];
  for(i = 0;i < no_of_vertices;i++){
    for(j = 0;j < 15;j++){
      adj_matrix[i][j] = 0;                              //initializing the adjacency-matrix storing each vertex's neighbours into each of the multiple rows
    }
  }
  flag_array = new int[no_of_vertices];
  for(i = 0;i < no_of_vertices;i++){
    flag_array[i] = 0;                                   //setting each vertex unmarked by marking its corresponding flag_array index = 0
  }
  cout << "Enter the number of edges : ";                //asking the user to enter the no. of edges
  cin >> no_of_edges;
  if(no_of_edges < no_of_vertices - 1){
    cout << "Invalid Input.Try Again" << endl;
    return 0;
  }
  /****************************************************************************/
  struct spanning edge[no_of_edges];                     //declaring an array of structs to store the weights and end, start vertices of an edge
  /****************************************************************************/
  for(i = 0;i < no_of_edges;i++){
    cout << "Enter the weight of the edge number " << i + 1 << " : ";
    cin >> edge[i].weight;                               //asking user to input the weight of the edge
    if(edge[i].weight <= 0){
      cout << "Length not Valid" << endl;
      cout << "Enter the weight of the edge number, again " << i + 1 << " : ";
      cin >> edge[i].weight;
    }
    cout << "Enter the vertices of the edge : " << endl;
    for(j = 0;j < 2;j++){
      cout << "Vertex no. " << j + 1 << " : ";
      cin >> edge[i].vertex[j];                          //storing the start and end vertices at respectively first and second(last) position of the vertexarray
    }
  }
  for(i = 0;i < no_of_vertices;i++){                     //filling the adjacency-matrix by keeping the neighbours of each vertex in array[vertex - 1][i]
    int k = 0;
    for(j = 0;j < no_of_edges;j++){
      if(edge[j].vertex[0] == i + 1){
        adj_matrix[i][k] = edge[j].vertex[1];
        k++;
      }
      else if(edge[j].vertex[1] == i + 1){
        adj_matrix[i][k] = edge[j].vertex[0];
        k++;
      }
    }
  }

  cout << endl;
  cout << "/*********************************************************/" << endl;
  cout << "/******************Minimum Spanning Tree******************/" << endl;
  cout << "/*********************************************************/" << endl;

  int temp = edge[0].vertex[0];                         //pushing the first edge with starting point as edge[0].start vertex
  int count = 0;
  struct spanning tree[30];                             //declaring an array to store the resultant edges
  int index = 0;                                        //an index variable to store the current count of the edges in the array of structs
  while(count < no_of_vertices){                        //while loop with condition that count increments till the no. of vertices
    count++;
    flag_array[temp - 1] = 1;                           //mark the starting vertex of the pushed edge
    j = 0;
      while(adj_matrix[temp - 1][j] != 0){              //traversing the adjacency matrix and pushing all the edges with end vertices as unmarked neighbours of the current start vertex(temp)
        if(flag_array[adj_matrix[temp - 1][j] - 1] == 0){
          for(k = 0;k < no_of_edges;k++){
            if(edge[k].vertex[0] == temp && edge[k].vertex[1] == adj_matrix[temp - 1][j]){//finding the edge with given end vertex
              if(flag_array[edge[k].vertex[1] - 1] == 0){//push only if unmarked(i.e. the flag is set to zero)
                add(edge[k]);
                if(heap_array[size_counter].weight == heap_array[0].weight){
                  struct spanning swap;                  //swapping and making minimum of heap to the freshly inserted edge if it's weight is identical to the weight of the already pushed edge
                  swap = heap_array[size_counter];
                  heap_array[size_counter] = heap_array[0];
                  heap_array[0] = swap;
                }
                min_heapify(size_counter);               //min-heapifying the heap
              }
            }
            else if(edge[k].vertex[1] == temp && edge[k].vertex[0] == adj_matrix[temp - 1][j]){//vice-versa case
              if(flag_array[edge[k].vertex[0] - 1] == 0){
                add(edge[k]);
                if(heap_array[size_counter].weight == heap_array[0].weight){
                  struct spanning swap;
                  swap = heap_array[size_counter];
                  heap_array[size_counter] = heap_array[0];
                  heap_array[0] = swap;
                }
                min_heapify(size_counter);              //min-heapifying the heap
              }
            }
          }
        }
        j++;                                            //iterator in inner while incremented to proceed the next neighbour in the adjacency list
      }
    if(heap_array[0].vertex[0] == temp){
      temp = heap_array[0].vertex[1];                   //now repeating the same procedure with end vertex of the edge of minimum weight i.e., the top edge's end vertex
    }
    else if(heap_array[0].vertex[1] == temp){
      temp = heap_array[0].vertex[0];
    }
    while(flag_array[heap_array[0].vertex[0] - 1] == 1 && flag_array[heap_array[0].vertex[1] - 1] == 1){
      del_min();                                        //deleting the edge if both the vertices are marked to avoid the formation of a cycle
    }
    tree[index] = heap_array[0];                        //storing the edge in the resultant array
    index++;
    cout << "Weight : " << heap_array[0].weight << endl << "Vertices : " << "(" << heap_array[0].vertex[0] << ", " << heap_array[0].vertex[1] << ")" << endl;
    del_min();                                          //"extract_min"
  }
  cout << endl;
  cout << "MinimumSpanningTree" << endl;
  cout << endl;
  for(i = 0;i < no_of_vertices - 1;i++){
    check_counter++;
    cout << "Weight : " << tree[i].weight << endl << "Vertices : " << "(" << tree[i].vertex[0] << ", " << tree[i].vertex[1] << ")" << endl;
    //cout << tree[i].weight << tree[i].vertex[0] << tree[i].vertex[1] << endl;
  }
  if(tree[no_of_vertices - 2].weight == 0 && tree[no_of_vertices - 2].vertex[0] == 0 && tree[no_of_vertices - 2].vertex[1] == 0){
    cout << "No Spanning Tree !" << endl;               //case if no spanning tree
    cout << endl;
  }
  return 0;
}
