#include <stdlib.h>
#include <iostream>

using namespace std;

// member functions declaration
void insertionSort(int arr[], int length);

// main function
int main()
{
	int array[6] = {5, 1, 6, 2, 4, 3};

	for(int i=0; i<6; i++){
		cout << array[i] << " ";
	}
	cout << "\n...................\n" << endl;

	insertionSort(array, 6);
	cout << "Sorted Array: ";
	
	for(int i=0; i<6; i++){
		cout << array[i] << " ";
	}
	return 0;
}

void insertionSort(int arr[], int length)
{
	int i, j, key;
	for (i = 1; i < length; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;

		cout << "key: " << key << endl;
		for(int itr=0; itr<length; itr++){
			cout << arr[itr] << " ";
		}
		cout << endl;
	}
}

