#include <iostream>
#include <cstdlib>
using namespace std;

struct parent{                                                       //declaring struct parent to store the height and parent of each vertex
  int leader;
  int height;
};

struct spanning{                                                     //declaring struct spanning to create an object for an edge, that stores the weight of the edge and its start and end vertices
  int weight;
  int vertex[2];                                                     //declaring an array of size two to store the end and start vertex of the edge
};

void merger(struct spanning arr[], int start, int mid, int end){     //merger function to sort and merger the subarrays
  int i, j, k;
  int len1 = mid - start + 1;                                        //defining lengths of the two subarrays
  int len2 =  end - mid;
  struct spanning L[len1], R[len2];                                  //declaring two temporary subarrays and copying the respective objects into them for sorting

  for(i = 0; i < len1; i++){
    L[i] = arr[start + i];
  }
  for(j = 0; j < len2; j++){
    R[j] = arr[mid + 1+ j];
  }
  i = 0;
  j = 0;
  k = start;
  while (i < len1 && j < len2){                                      //comparing the elements and putting the smaller values into the original array passed in the function
    if (L[i].weight <= R[j].weight){
      arr[k] = L[i];
      i++;
    }
    else{
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < len1){                                                  //putting the remaining elements into the original array
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < len2){
    arr[k] = R[j];
    j++;
    k++;
  }
}

void sorter(struct spanning arr[], int start, int end){
  if (start < end){
    int mid = start + (end - start)/2;                                //calling sorter function two times recursively and finally merge the two sorted subarrays
    sorter(arr, start, mid);
    sorter(arr, mid + 1, end);
    merger(arr, start, mid, end);
  }
}

int tell_parent(struct parent *array, int node){
  return array[node - 1].leader;
}

int tell_parentheight(struct parent *array, int node){
  return array[node - 1].height;
}

int main(){
  int i, j, no_vertex, no_edges, check_counter = 0;
  cout << "Enter the no. of vertices : ";                             //asking the user to input the number of vertices
  cin >> no_vertex;
  struct parent p[no_vertex];                                         //declaring array of struct parent to store the parent and height of each vertex respectively
  for(i = 0;i < no_vertex;i++){                                       //storing the vertex and its parent(i.e. the vertex itself initially) in the struct
    p[i].leader = i + 1;
    p[i].height = 0;
  }
  cout << "Enter the no. of edges : ";                                //asking the user to enter the no. of edges
  cin >> no_edges;
  if(no_edges < no_vertex - 1){
    cout << "Invalid Input.Try Again" << endl;
    return 0;
  }
  struct spanning edge[no_edges];                                     //declaring an array of edges, i.e. an array of the struct objects
  for(i = 0;i < no_edges;i++){
      cout << "Enter the weight of the edge number " << i + 1 << " : ";
      cin >> edge[i].weight;                                          //asking user to input the weight of the edge
      if(edge[i].weight <= 0){
        cout << "Length not Valid" << endl;
        cout << "Enter the weight of the edge number, again " << i + 1 << " : ";
        cin >> edge[i].weight;
      }
      cout << "Enter the vertices of the edge : " << endl;
      for(j = 0;j < 2;j++){
        cout << "Vertex no. " << j + 1 << " : ";                      //storing the start and end vertices at respectively first and second(last) position of the vertexarray
        cin >> edge[i].vertex[j];
      }
  }
  cout << endl;
  cout << "/*********************************************************/" << endl;
  cout << "/******************Minimum Spanning Tree******************/" << endl;
  cout << "/*********************************************************/" << endl;

  sorter(edge, 0, no_edges - 1);                                     //calling the sorter function to sort the weights of edges in ascending order

  for(i = 0;i < no_edges;i++){                                       //loop running across the edges, if parent is not same, compare the heights
    if(p[edge[i].vertex[1] - 1].leader != p[edge[i].vertex[0] - 1].leader){
      if(p[edge[i].vertex[1] - 1].height == p[edge[i].vertex[0] - 1].height){
        p[edge[i].vertex[1] - 1].leader = p[edge[i].vertex[0] - 1].leader;
        p[edge[i].vertex[0] - 1].height++;                           //if both heights are same, make any one's parent the another's and increase the overall height by one
        p[edge[i].vertex[1] - 1].height++;
      }                                                              //otherwise make the parent of the one with greater height the other one's parent
      else if(p[edge[i].vertex[1] - 1].height < p[edge[i].vertex[0] - 1].height){
        p[edge[i].vertex[1] - 1].leader = p[edge[i].vertex[0] - 1].leader;
      }
      else if(p[edge[i].vertex[1] - 1].height > p[edge[i].vertex[0] - 1].height){
        p[edge[i].vertex[0] - 1].leader = p[edge[i].vertex[1] - 1].leader;
      }
      else{
        ;
      }
      cout << "Weight : " << edge[i].weight << endl << "Vertices : " << "(" << edge[i].vertex[0] << ", " << edge[i].vertex[1] << ")" << endl;
      check_counter++;
    }
    else if(p[edge[i].vertex[1] - 1].leader == p[edge[i].vertex[0] - 1].leader){
      cout << "Edge discarded !" << endl;                            //if parent same, don't take union, i.e., discard the edge
    }
    else{
      cout << "Edge discarded !" << endl;
    }
  }
  cout << endl;
  if(check_counter != no_vertex - 1){
    cout << "Spanning Tree doesn't Exist !" << endl;                 //if no spanning tree 
    cout << endl;
  }
  return 0;
}
