/*Consider the telephone book database of N clients.Make use of a hash table implementation to quickly look up
a client's  telephone number. Make use of two collision handling techniques and compare them using number of 
comparisons required to find a set of telephone numbers*/



#include<iostream>
#include<string.h>
using namespace std;
#define maxSize 25

class clientTelephoneBook
{
    public:
        string names[maxSize];
        long int phoneNumbers[maxSize];

        clientTelephoneBook()
        {
            for(int i=0;i<maxSize;i++)
            {
                names[i]="0";
                phoneNumbers[i]=-999;
            }

        }

        int hashFunction(string key);
        int hashFunction2(string key);
        void insert(int probingType,string name,long int number);
        void display();
        int search(int probingType,string key);

        int linearProbingWithoutReplacement(string key,long int num);
        int linearProbingWithReplace(string key,long int num);
        int quadraticProbing(string key,long int num);
        int doubleHashing(string key,long int num);

};

int clientTelephoneBook::hashFunction(string key)
{
    int totalHashValue=0;
    for(char ch:key)
    {
        totalHashValue+=ch;
    }
    return (totalHashValue%maxSize);
}

int clientTelephoneBook::hashFunction2(string key)
{
    int totalHashValue=0;
    for(char ch:key)
    {
        totalHashValue+=ch;
    }

    return 19-(totalHashValue%19);
}

void clientTelephoneBook::insert(int probingType,string name, long int number)
{
    int index;
    switch (probingType)
    {
    case 1: index=linearProbingWithoutReplacement(name,number);
            break;

    case 2: index=linearProbingWithReplace(name,number);
            break;

    case 3: index=quadraticProbing(name,number);
            break;

    case 4: index=doubleHashing(name,number);
            break;
    }

    if(index!=-1)
    {
        names[index]=name;
        phoneNumbers[index]=number;
        cout<<"Record Inserted Succesfully"<<endl;
    }
    else
    {
        cout<<"Overflow Condition"<<endl;
    }
}

void clientTelephoneBook::display()
{
    for(int i=0;i<maxSize;i++)
    {
        if(phoneNumbers[i]!=-999)
        {
            cout<<names[i]<<" : "<<phoneNumbers[i]<<endl;
        }
    }
}

int clientTelephoneBook::search(int probingType,string key)
{
    int comparisons = 0;
    int probingIndex = hashFunction(key);
    int hashIndex2;

    switch (probingType)
    {
    case 1: // Linear Probing Without Replacement
        while (phoneNumbers[probingIndex] != -999 && names[probingIndex] != key && comparisons < maxSize)
        {
            probingIndex = (probingIndex + 1) % maxSize;
            comparisons++;
        }
        break;

    case 2: // Linear Probing With Replacement
        while (phoneNumbers[probingIndex] != -999 && names[probingIndex] != key && comparisons < maxSize)
        {
            probingIndex = (probingIndex + 1) % maxSize;
            comparisons++;
        }
        break;

    case 3: // Quadratic Probing
        for (int i = 0; i < maxSize; i++)
        {
            probingIndex = (probingIndex + i * i) % maxSize;
            comparisons++;
            if (phoneNumbers[probingIndex] == -999 || names[probingIndex] == key)
                break;
        }
        break;

    case 4: // Double Hashing
        hashIndex2 = hashFunction2(key);
        while (phoneNumbers[probingIndex] != -999 && names[probingIndex] != key && comparisons < maxSize)
        {
            probingIndex = (probingIndex + hashIndex2) % maxSize;
            comparisons++;
        }
        break;

    default:
        cout << "Invalid probing type." << endl;
        return -1;
    }

    if (phoneNumbers[probingIndex] != -999 && names[probingIndex] == key)
        return probingIndex; // Found the record

    return -1; // Record not found
}

int clientTelephoneBook::linearProbingWithoutReplacement(string key,long int num)
{
    int probingIndex=hashFunction(key);
    if(phoneNumbers[probingIndex]==-999)
    {
        return probingIndex;
    }
    else
    {
        for(int i=probingIndex+1;i!=probingIndex;i=(i+1)%maxSize)
        {
            if(phoneNumbers[i]=-999)
            {
                return i;
            }
        }
    }
    return -1; //Overflow condition
}

int clientTelephoneBook::linearProbingWithReplace(string key,long int num)
{
    string prevName;
    long int prevNum;
    int selectedIndex;
    int probingIndex=hashFunction(key);
    if(phoneNumbers[probingIndex]==-999)
    {
        return probingIndex;
    }
    else
    {
        if(hashFunction(names[probingIndex])!=probingIndex)
        {
            prevName=names[probingIndex];
            prevNum=phoneNumbers[probingIndex];
            selectedIndex=probingIndex;
            key=prevName;
            num=prevNum;

        }
        for(int i=probingIndex+1;i!=probingIndex;i=(i+1)%maxSize)
        {
            if(phoneNumbers[i]=-999)
            {
                names[i]=key;
                phoneNumbers[i]=num;
                return selectedIndex;
            }
        }
    }
    return -1;  //Overflow Condition
}

int clientTelephoneBook::quadraticProbing(string key,long int num)
{
    int probingIndex=hashFunction(key);
    for(int i=0;i%maxSize!=probingIndex;i++)
    {
        probingIndex=(probingIndex+i*i)%maxSize;
        if(phoneNumbers[probingIndex]==-999)
        {
            return probingIndex;
        }
    }
    return -1;  //Overflow Condition

}

int clientTelephoneBook::doubleHashing(string key,long int num)
{
    int probingIndex=hashFunction(key);

    for(int i=0;i%maxSize!=probingIndex;i++)
    {
        probingIndex = (probingIndex + i * hashFunction2(key)) % maxSize;
        if(phoneNumbers[probingIndex]==-999)
        {
            return probingIndex;
        }
    }
    return -1;  //Table Overflow
}


int main()
{
    clientTelephoneBook tb;
    int ch,probingType,flag;
    string toSearchName,newName;
    long int newNumber;

    cout<<"1. Linear Probing Without Replacement\n2. Linear Probing With Replacement"<<endl;
    cout<<"3. Quadratic Probing\n4. Double Hashing"<<endl;
    cout<<"Enter Probing Type to be used : ";
    cin>>probingType;

    do
    {
        cout<<"\n\tMENU"<<endl;
        cout<<"1. Insert Client Record\n2. Display all Client Records\n3. Search Client Record\n4. Exit"<<endl;
        cout<<"Enter your choice : "<<endl;
        cin>>ch;
        cout<<"-------------------------------------"<<endl;

        switch(ch)
        {
            case 1: cout<<"Enter the Name to Insert : ";
                    cin>>newName;
                    cout<<"Enter Phone Number : ";
                    cin>>newNumber;
                    tb.insert(probingType,newName,newNumber);
                    break;

            case 2: cout<<"Displaying All Client Records : "<<endl;
                    tb.display();
                    break;

            case 3 : cout<<"Enter the Name to Search : ";
                     cin>>toSearchName;
                     flag=tb.search(probingType,toSearchName);
                    if(flag!=-1)
                    {
                        cout<<"Record Found"<<endl;
                        cout<<tb.names[flag]<<" : "<<tb.phoneNumbers[flag]<<endl;
                    }
                    else
                    {
                        cout<<"Record Not Found"<<endl;
                    }
                    break;
            
            case 4: break;

            default: cout<<"Wrong Input"<<endl;

        }
    } while (ch!=4);
    
    return 0;
}


//OUTPUT
/*
1. Linear Probing Without Replacement
2. Linear Probing With Replacement
3. Quadratic Probing
4. Double Hashing
Enter Probing Type to be used : 1

        MENU
1. Insert Client Record
2. Display all Client Records
3. Search Client Record
4. Exit
Enter your choice : 
1
-------------------------------------
Enter the Name to Insert : ABC
Enter Phone Number : 1234567
Record Inserted Succesfully

        MENU
1. Insert Client Record
2. Display all Client Records
3. Search Client Record
4. Exit
Enter your choice : 
1
-------------------------------------
Enter the Name to Insert : ACB
Enter Phone Number : 234567
Record Inserted Succesfully

        MENU
1. Insert Client Record
2. Display all Client Records
3. Search Client Record
4. Exit
Enter your choice :
1
-------------------------------------
Enter the Name to Insert : XYZ
Enter Phone Number : 9837463
Record Inserted Succesfully

        MENU
1. Insert Client Record
2. Display all Client Records
3. Search Client Record
4. Exit
Enter your choice :
2
-------------------------------------
Displaying All Client Records :
XYZ : 9837463
ABC : 1234567
ACB : 234567

        MENU
1. Insert Client Record
2. Display all Client Records
3. Search Client Record
4. Exit
Enter your choice :
3
-------------------------------------
Enter the Name to Search : XYZ
Record Found
XYZ : 9837463

        MENU
1. Insert Client Record
2. Display all Client Records
3. Search Client Record
4. Exit
Enter your choice :
3
-------------------------------------
Enter the Name to Search : MNO
Record Not Found

        MENU
1. Insert Client Record
2. Display all Client Records
3. Search Client Record
4. Exit
Enter your choice :
4
-------------------------------------
*/