/*Read the marks obtained by the students of second year in an online examination of a particular subject.
Find out maximum and minimum marks obtained in that subject. Use heap data structure. Analyze the algorithm.*/

#include <iostream>

// Function to heapify the array
void heapify(int arr[], int n, int i) {
    int largest = i;         // Initialize largest as root
    int left = 2 * i + 1;    // Left child position
    int right = 2 * i + 2;   // Right child position

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void findMinMaxMarks(int marks[], int n) {
    // Heapify the array
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(marks, n, i);

    int maxMarks = marks[0];       // Maximum marks
    int minMarks = marks[n];   // Minimum marks

    std::cout << "Maximum marks obtained: " << maxMarks << std::endl;
    std::cout << "Minimum marks obtained: " << minMarks << std::endl;
}

int main() {

    int marks[6];
    int n=6;

    for(int i=0;i<6;i++)
    {
        std::cin>>marks[i];
    }

    findMinMaxMarks(marks, n);

    return 0;
}
