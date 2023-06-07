/*Implement the Heap Sort/Shell Sort algorithm implemented in Java demonstrating heap/shell data structure 
with modularity of programming language*/

import java.util.Scanner;

public class Assign1 {

    //Printing Array
    public void printArray(int dataArray[],int lenArray)
    {
        for(int i=0;i<lenArray;i++)
        {
            System.out.print(dataArray[i]+"\t");
        }
    }

    //Shell Sort
    public void shellSort(int dataArray[],int lenArray)
    {
        Assign1 st=new Assign1();
        int gap,temp,flag,i,j=1;
        gap=lenArray/2;
        while(gap>0)
        {
		    do
		    {
			    flag=0;
			    for(i=0;i<lenArray-gap;i++)
			    {
				    if(dataArray[i]>dataArray[i+gap])
				    {
					    temp=dataArray[i];
					    dataArray[i]=dataArray[i+gap];
					    dataArray[i+gap]=temp;
					    flag=1;
				    }
				}
		    }while(flag==1);
		    System.out.println("\nPass "+j+" : ");
		    j++;
		    st.printArray(dataArray,lenArray);
		    gap/=2;
	    }
	}


    //Heap Sort
    public void heapSort(int dataArray[],int lenArray)
    {
        int n = lenArray;
        Assign1 pt=new Assign1();

        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(dataArray, n, i);

        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; i--) {
            // Move current root to the end
            int temp = dataArray[0];
            dataArray[0] = dataArray[i];
            dataArray[i] = temp;

            // Heapify the reduced heap
            heapify(dataArray, i, 0);

            System.out.println("\nPass "+ (n-i)+ " : " );
            pt.printArray(dataArray, lenArray);

        }
    }

    //Heapify
    private static void heapify(int dataArray[], int n, int i) {
        int largest = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < n && dataArray[leftChild] > dataArray[largest])
            largest = leftChild;

        if (rightChild < n && dataArray[rightChild] > dataArray[largest])
            largest = rightChild;

        if (largest != i) {
            // Swap the largest element with the root
            int temp = dataArray[i];
            dataArray[i] = dataArray[largest];
            dataArray[largest] = temp;

            // Recursively heapify the affected sub-tree
            heapify(dataArray, n, largest);
        }
    }

    //Main Function
    public static void main(String argc[])
    {
        int ch;
        Scanner obj=new Scanner(System.in);
        Assign1 s=new Assign1();

        do
        {
            System.out.println("\n-----------------------------------------------------");
            System.out.println("\tMENU");
            System.out.println("1. Shell Sort\n2. Heap Sort\n3. Exit");
            System.out.print("Enter your choice : ");
            ch=obj.nextInt();
            System.out.println("-----------------------------------------------------");
            
            if(ch==3)
            {
                System.out.println("Exiting...");
                break;
            }

            //Creation and Initialization
            int lenArray,i;
            System.out.println("Enter Size of Array : ");
            lenArray=obj.nextInt();
            int dataArray[]=new int[lenArray];
        
            //Data Input
            System.out.println("Enter Elements to sort :");
            for(i=0;i<lenArray;i++)
            {
                dataArray[i]=obj.nextInt();
            }

            System.out.println("--------------------------------------------------------");
            System.out.println("Data before Sorting : ");
            s.printArray(dataArray,lenArray);

            switch(ch)
            {
                case 1: s.shellSort(dataArray,lenArray);
                        System.out.println("\nData after Sorting : ");
                        s.printArray(dataArray,lenArray);
                        break;

                case 2: s.heapSort(dataArray,lenArray);
                        System.out.println("\nData after Sorting : ");
                        s.printArray(dataArray,lenArray);
                        break;

                default: System.out.println("Wrong Input");
                         break;
            }
            
        }while(ch!=3);

        obj.close();

    }
    
}

// OUTPUT 
/*
-----------------------------------------------------
        MENU
1. Shell Sort
2. Heap Sort
3. Exit
Enter your choice : 1
-----------------------------------------------------
Enter Size of Array : 
5
Enter Elements to sort :
98
23
78
1
52
-----------------------------------------------------
Data before Sorting :
98      23      78      1       52
Pass 1 :
52      1       78      23      98
Pass 2 :
1       23      52      78      98
Data after Sorting :
1       23      52      78      98
-----------------------------------------------------
        MENU
1. Shell Sort
2. Heap Sort
3. Exit
Enter your choice : 3
-----------------------------------------------------
Exiting...
*/
