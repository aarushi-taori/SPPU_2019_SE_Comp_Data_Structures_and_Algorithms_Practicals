/* Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with/without replacement.
Data : Set of (key,value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique. Standard Operations : Insert(key,value), Find(key), Delete(key)
*/

#include<iostream>
#include<string.h>
using namespace std;

class node
{

    public: 
        string word;
        string meaning;
        node* next;
    
    
        node()
            {
                next=NULL;
            }

};

class dictionary
{
    node *arr[26];
    
    public:
    
        dictionary()
        {
            for(int i=0;i<25;i++)
            {
                arr[i]=new node;
                arr[i]=NULL;
            }
        }
        
        int hash(string word);
        void Insert(string key, string value);
        string Find(string key);
        void Delete(string key);
        void Display();
};

int dictionary::hash(string word)
{
    return (int(toupper(word[0])-65));
}

void dictionary::Insert(string key, string value)
{ 
    node* temp,*newData;
    int index,i,n;
  
    newData=new node;
    newData->word=key;
    newData->meaning=value;
   
    index=hash(key);
    
    if(arr[index]==NULL)
    {
        arr[index]=newData;
    }
    else
    {
        for(temp=arr[index];temp->next!=NULL;temp=temp->next);
        temp->next=newData;
    }
    cout<<"Data Inserted Successfully !!"<<endl;
}

string dictionary::Find(string key)
{
    node *temp;
    int index,flag=0;
    index=hash(key);
    temp=arr[index];
    while(temp!=NULL)
    {
        if(temp->word==key)
        {
            flag=1;
            return temp->meaning;
        }
        temp=temp->next;
    }
    return "NULL";

}

void dictionary::Delete(string key)
{
    node *curr,*temp;
    int index,flag=0;

    index=hash(key);
    temp=arr[index];

    if(temp==NULL)
    {
       cout<<"Key not found !!"<<endl;
       return;
    }
    else if(temp->word==key)
    {
        arr[index]=temp->next;
        delete temp;
        return;
    }
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->next->word==key)
            {
                curr=temp->next;
                temp->next=temp->next->next;
                delete (curr);
                return;
            }
            temp=temp->next;
        }
        cout<<"Key not found !!"<<endl;
        return;
    }
}

void dictionary::Display() 
{
    for (int i = 0; i < 26; i++) 
    {
        node *temp = arr[i];
        cout << "Bucket " << i << ": ";
        while (temp != NULL) 
        {
            cout << "(" << temp->word << "," << temp->meaning << ")";
            temp = temp->next;
        }
        cout << endl;
    }
}


int main()
{   
    dictionary arrayDict;
    int ch;
    string word,meaning;

    do
    {
        cout<<"-----------------------------------------------------------------------------------------"<<endl;
        cout<<"\t\tMENU"<<endl;
        cout<<"1. Display Dictionary\n2. Insert Word in Dictionary\n3. Search Word in Dictionary\n4. Remove Word from Dtcionary\n5. Exit "<<endl;
        cout<<"------------------------------------------------------------------------------------------"<<endl;
        cout<<"Enter your choice : ";
        cin>>ch;

        switch(ch)
        {
            case 1: cout<<"Displaying Dictionary : "<<endl;
                arrayDict.Display();
                    break;

            case 2: cout<<"Enter the Word to Insert : ";
                    cin>>word;
                    cout<<"Enter its Meaning : ";
                    cin>>meaning;
                    arrayDict.Insert(word,meaning);
                    break;

            case 3: cout<<"Enter the word to search : ";
                    cin>>word;
                    meaning=arrayDict.Find(word);
                    if(meaning=="NULL")
                    {
                        cout<<"Word not found !!"<<endl;
                    }
                    else
                    {
                        cout<<"WORD : "<<word<<"\tMEANING : "<<meaning<<endl;
                    }
                    break;


            case 4: cout<<"Enter the word to delete : ";
                    cin>>word;
                    arrayDict.Delete(word);
                    break;

            case 5: exit(0);
            default: cout<<"Wrong Input !! ... Enter a choice from 1 to 5"<<endl;
                     break;

        }
    } while (ch!=5);
    
    return 0;
}

