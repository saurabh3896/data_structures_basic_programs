#include <iostream>
#include <cstdlib>
#define SIZE 100

using namespace std;

class heap{                       //class declaration
  int heap_array[SIZE];
  int size_counter;
public:
  heap();
  int get_size(){                 //function to return the current size of the heap
    return size_counter;
  }
  void add(int insert_data);      //functions to add, heapigy and sort the numbers
  void heapify(int count);
  void heap_sort();
  void display();
};
class heap H1;

heap::heap(){                     //constructor to initialize the array's elements and size_counter = -1
  int i;
  for(i = 0;i < SIZE;i++){
    heap_array[i] = 0;
  }
  size_counter = -1;
}

void heap::add(int insert_data){
  /*if(heap_array[0] == 0){
    size_counter++;
    heap_array[size_counter] = insert_data;
    return;
  }*/
  size_counter++;
  heap_array[size_counter] = insert_data;
}

void heap::heap_sort(){
  int i,j, swap, temp, hold;
  for (i = size_counter;i > 0;i--){   //loop from array[n] to array[2]
		swap = heap_array[i] ;            //swapping the last and first element of the help_array and reducing the size_counter by 1
		heap_array[i] = heap_array[0] ;
		heap_array[0] = swap;
    temp = i - 1;                     //setting temp equal to temporary size_counter - 1 and initiating while loop to insert numbers in order
    for(j=temp;j>0;j--){
        heapify(j);                   //calling heapify function to sort the elements after decreasing size by 1
    }
  }
}

void heap::display(){                 //helper function to print the elements of the "help_array"
  int i;
	for (i = 0;i <= size_counter;i++){
		cout << heap_array[i] << " -> ";
  }
	cout << "End of Array" << endl ;
}

void heap::heapify(int count){
  int temp, hold;
  temp = count;
  while(heap_array[temp] > heap_array[(temp - 1)/2]){
      hold = heap_array[temp];
      heap_array[temp] = heap_array[(temp - 1)/2];
      heap_array[(temp - 1)/2] = hold;
      temp = (temp - 1)/2;
  }
}

int main(){
  cout << "**********************HEAP-SORT IMPLENTATION**********************" << endl;
  int i, n;
  cout << "Enter the size of the array : ";       //taking user input about the size and elements of the array
  cin >> n;
  if(n < 0){
    cout << "Size can't be negative" << endl;     //size can't be negative
    return 0;
  }
  int input[n];
  for(i = 0;i < n;i++){
    cout << "Enter element " << i << " : ";        //taking input about the array elements and adding directly into the heap
    cin >> input[i];
    H1.add(input[i]);
    H1.heapify(H1.get_size());                     //heapifying the elements one by one insertion
  }
  H1.display();                                    //display before sorting
  cout << "***********************************************************" << endl;
  cout << "**********************After sorting************************" << endl;
  cout << "***********************************************************" << endl;
  H1.heap_sort();
  H1.display();                                    //display after sorting
  return 0;
}
