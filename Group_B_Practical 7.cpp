/* A Dictionary stores keywords and its meanings.Provide facility for adding new keywords, deleting keywords, 
updating values of any entry.Provide facility to display whole data sorted in ascending / descending order. 
Also find how many maximum comparisons may require for finding any keyword. Use Binary search tree for 
implementation.*/

/*
Name : Aarushi Taori
Class : SEB
Roll no. : 75
*/

#include<iostream>
#include<string>
using namespace std;


//Binary Search Tree Node
class node
{
    public:
        string word;
        string meaning;
        node *left;
        node *right;
        
        node()
        {
            left=NULL;
            right=NULL;
        }
};

//Stack
class stack
{
    private:
        node *stacks[50];
        int top,MaxSize;
    
    public:

        stack()
        {
            for(int i=0;i<50;i++)
            {
                stacks[i]=new node;
            }

            top=-1;
            MaxSize=50;
        }

        int isEmpty()
        {
            if(top==-1)
            {
                return 1;
            }
            return 0;
        }

        void push(node *newNode)
        {
            if(top!=MaxSize-1)
            {
                stacks[++top]=newNode;
            }

        }

        node* pop()
        {
            if(!isEmpty())
            {
                node *temp=stacks[top--];
                return temp;
            }
        }
};


//Binary Search Tree
class binarySearchTree
{
    public:
        node *root;        
        int count;
        binarySearchTree()
        {
            root=NULL;
        }
        
        
        void create();
        void insert();
        node *search(string x);
        void inOrder(node *root);
        void inOrderNon();
        void descending(node *root);
        void descendingNon();
        void update(string wordUpdate,string updatedMeaning);
        void NumberComparsions(string key);
        
};


//Creation of BST
void binarySearchTree::create()
{
    cout<<"Creating Root Node : "<<endl;
    root =new node;
    root->left=root->right=NULL;
    cout<<"Enter Word for Root Node : ";
    cin>>root->word;
    cout<<"Enter its meaning : ";
    cin>>root->meaning;
}

//Inserting a Node in BST
void binarySearchTree::insert()
{
    node *temp,*p;
    if(root==NULL)
    {
        create();
        return;
    }
    
    //Allocate new node to be inserted 
    p= new node();
    p->left=p->right=NULL;
    cout<<"Enter Data : ";
    cin>>p->word;
    cout<<"Enter its meaning : ";
    cin>>p->meaning;
    
    
    //Inserting Node in the tree
    temp=root;
    while(temp!=NULL)
    {
        if(p->word<temp->word)
        {
            //Given data is else than data value in temp node----Hence, It is the left Child of temp
            if(temp->left==NULL)
            {
                temp->left=p;
                break;
            }
            else
            {
                temp=temp->left;
            }
        }
        
        else if(p->word>temp->word)
        {
            //Given data is more than data value in temp node----Hence, It is the right Child of temp
            if(temp->right==NULL)
            {
                temp->right=p;
                break;
            }
            else
            {
                temp=temp->right;
            }
            
        }
        
        else
        {
            //Given Data is equal to the data value in temp node
            cout<<"Node already inserted !!"<<endl;
            break;
        }
    }
}


//Searching a Node in BST
node *binarySearchTree::search(string x)
{
    node *temp=root;
    count=0;
    if(temp==NULL)
    {
        cout<<"Binary Search Tree is empty !!"<<endl;
    }
    
    while(temp!=NULL)
    {
        if(temp->word==x)
        {
            return temp;
        }
        
        else if(x<temp->word)
        {
            temp=temp->left;
        }
        
        else
        {
            temp=temp->right;
        }
        count++;    
    }
    
    if(temp==NULL)
    {
        return NULL;
    }

}

//In Order Recursive
void binarySearchTree::inOrder(node *root)
{
    if(root!=NULL)
    {
        inOrder(root->left);
        cout<<root->word<<":"<<root->meaning<<endl;
        inOrder(root->right);
    }
}

//In Order Non-Recursive
void binarySearchTree::inOrderNon()
{
    stack s1;
    node *temp=root;
    do
    {
        while(temp!=NULL)
        {
            s1.push(temp);
            temp=temp->left;
        }
        
        if(s1.isEmpty())
        {
            break;
        }

        temp=s1.pop();
        cout<<temp->word<<":"<<temp->meaning<<endl;
        temp=temp->right;

    } while (1);
    
}


//Descending Recursive
void binarySearchTree::descending(node *root)
{
    if(root!=NULL)
    {
        descending(root->right);
        cout<<root->word<<":"<<root->meaning<<endl;
        descending(root->left);
    }
}

//Descending Non-Recursive
void binarySearchTree::descendingNon()
{
    stack s1;
    node *temp=root;
    do
    {
        while(temp!=NULL)
        {
            s1.push(temp);
            temp=temp->right;
        }
        
        if(s1.isEmpty())
        {
            break;
        }

        temp=s1.pop();
        cout<<temp->word<<":"<<temp->meaning<<endl;
        temp=temp->left;

    } while (1);
    
}

void binarySearchTree::update(string wordUpdate,string updatedMeaning)
{
    node *temp=search(wordUpdate);
    if(temp!=NULL)
    {
        temp->meaning=updatedMeaning;
        cout<<"Word's Meaning Updated Sucessfully !!"<<endl;
    }
    else
    {
       cout<<"Node is not Found in the Binary Search Tree !!"<<endl;
    }
    
}

void binarySearchTree::NumberComparsions(string key)
{
    node *temp=search(key);
    cout<<"Number of Comparisons to search "<<key<<" are : "<<count<<endl;
}

int main()
{
    binarySearchTree bst;
    int ch;
    char con[3];
    string key,wordUpdate,newMeaning;
    node *temp;
    
    do
    {
        cout<<"---------------------------------------------------------------------------"<<endl;
        cout<<"\t\t\tMENU"<<endl;
        cout<<"1.) Insert a Node \n2.) Ascending Order \n3.) Descending Order \n4.) Update a keyword's meaning"<<endl;
        cout<<"5.) Search a Node \n6.) Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>ch;
        cout<<"---------------------------------------------------------------------------"<<endl;
        
        switch(ch)
        {
            case 1: bst.insert();
                    break;
                    
            case 2: cout<<"\nRecursive Ascending Order is : "<<endl;
                    bst.inOrder(bst.root);
                    cout<<"\nNon-Recursive Ascending Order is : "<<endl;
                    bst.inOrderNon();
                    break;
                    
             case 3: cout<<"\nRecursive Descending Order is : "<<endl;
                    bst.descending(bst.root);
                    cout<<"\nNon-Recursive Descending is : "<<endl;
                    bst.descendingNon();
                    break;
                    
            case 4: cout<<"Enter the word to update : ";
                    cin>>wordUpdate;
                    cout<<"Enter new meaning : ";
                    cin>>newMeaning;
                    bst.update(wordUpdate,newMeaning);
                    break;
                    
            case 5: cout<<"Enter the word to search : ";
                    cin>>key;
                    temp=bst.search(key);
                    if(temp!=NULL)
                    {
                        cout<<"Node is Found in the Binary Search Tree !!"<<endl;
                        cout<<"Word : "<<temp->word<<endl;
                        cout<<"Meaning : "<<temp->meaning<<endl;
                    }
                    else
                    {
                         cout<<"Node is not Found in the Binary Search Tree !!"<<endl;
                    }
                    bst.NumberComparsions(key);
                    break;
                    
             case 6: break;

            default: cout<<"Wrong Input!! Enter number b/w 1 and 6"<<endl;
                     break;
        }
        
    }while(ch!=6);
   
    return 0;
}
