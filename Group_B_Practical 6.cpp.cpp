/* Beginning with an empty binary search tree, Construct a binary search tree by inserting the values in the order given. After constructing a binary tree - 
i.) Insert a new node,
ii.) Find the number of nodes in longest path from root,
iii.) Minimum Data Value found in the tree,
iv.) Change a tree so that the roles of the left and right pointers are swapped at every node,
v.) Search a value
*/

#include<iostream>
using namespace std;


//Binary Search Tree Node
class node
{
    public:
        int data;
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

//Queue
class queue
{
    private:
        node *queues[50];
        int rear,front,maxSize,size;

    public:
        queue()
        {
            for(int i=0;i<50;i++)
            {
                queues[i]=new node;
            }
            front=rear=-1;
            maxSize=50;
            size=0;
        }

        int isEmpty()
        {
            if(front==rear)
            {
                return 1;
            }
        return 0;
        }
        
        
        int isFull()
        {
            if(rear==maxSize-1)
            {
                return 1;
            }
            return 0;
        }

        void Add(node *newNode)
        {
            if(!isFull())
            {
                queues[++rear]=newNode;
                size++;
            }
        }

        node *Del()
        {
            if(!isEmpty())
            {
                size--;
                node *temp=queues[++front];
                return temp;
            }
        }
};


//Binary Search Tree
class binarySearchTree
{
    public:
        node *root;        
    
        binarySearchTree()
        {
            root=NULL;
        }
        
        
        void create();
        void insert();
        void search(int key);
        void inOrder(node *root);
        void inOrderNon();
        void preOrder(node *root);
        void preOrderNon();
        void postOrder(node *root);
        void postOrderNon();
        void DFS();
        void BFS();
        int treeHeight(node *root);
        int minValue(node *root);
        int maxValue(node *root);
        void MirrorTree(node *root);
        
};


//Creation of BST
void binarySearchTree::create()
{
    cout<<"Creating Root Node : "<<endl;
    root =new node;
    root->left=root->right=NULL;
    cout<<"Enter Data for Root Node : ";
    cin>>root->data;
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
    cin>>p->data;
    
    
    //Inserting Node in the tree
    temp=root;
    while(temp!=NULL)
    {
        if(p->data<temp->data)
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
        
        else if(p->data>temp->data)
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
void binarySearchTree::search(int x)
{
    node *temp=root;
    int count=0;
    if(temp==NULL)
    {
        cout<<"Binary Search Tree is empty !!"<<endl;
    }
    
    while(temp!=NULL)
    {
        if(temp->data==x)
        {
            cout<<"Node is Found in the Binary Search Tree !!"<<endl;
            break;
        }
        
        else if(x<temp->data)
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
        cout<<"Node is not Found in the Binary Search Tree !!"<<endl;
    }

}

//In Order Recursive
void binarySearchTree::inOrder(node *root)
{
    if(root!=NULL)
    {
        inOrder(root->left);
        cout<<root->data<<"\t";
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
        cout<<temp->data<<"\t";
        temp=temp->right;

    } while (1);
    
}

//Pre Order Recursive
void binarySearchTree::preOrder(node *root)
{
    if(root!=NULL)
    {
        cout<<root->data<<"\t";
        preOrder(root->left);
        preOrder(root->right);
    }
}

//Pre Order Non-Recursive
void binarySearchTree::preOrderNon()
{
    stack s1;
    node *temp=root;
    while(1)
    {
        while(temp!=NULL)
        {
            cout<<temp->data<<"\t";
            s1.push(temp);
            temp=temp->left;
        }
        
        if(s1.isEmpty())
        {
            break;
        }

        temp=s1.pop();
        temp=temp->right;

    }
}

//Post Order Recursive
void binarySearchTree::postOrder(node *root)
{
    if(root!=NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        cout<<root->data<<"\t";
    }
}

//Post Order Non-Recursive
void binarySearchTree::postOrderNon()
{
    stack s1,s2;
    node *temp;
    s1.push(root);
    while(!s1.isEmpty())
    {
        temp=s1.pop();
        s2.push(temp);

        if(temp->left)
        {
            s1.push(temp->left);
        }

        if(temp->right)
        {
            s1.push(temp->right);
        }
    }

    while(!s2.isEmpty())
    {
        node *temp=s2.pop();
        cout<<temp->data<<"\t";
    }
    cout<<endl;
}


//DFS : Depth First Search
void binarySearchTree::DFS()
{
    stack s;
    node *temp=root;
    do
    {
        cout<<temp->data<<"\t";
        
        if(temp->right!=NULL)
        {
            s.push(temp->right);
        }

        if(temp->left!=NULL)
        {
            s.push(temp->left);
        }

        if(s.isEmpty())
        {
            break;
        }

        temp=s.pop();
    } while (1);
    
}

//BFS : Breadth First Search
void binarySearchTree::BFS()
{
    queue Q;
    node *temp=root;
    do
    {
        cout<<temp->data<<"\t";

        if(temp->left!=NULL)
        {
            Q.Add(temp->left);
        }

        if(temp->right!=NULL)
        {
            Q.Add(temp->right);
        }

        if(Q.isEmpty())
        {
            break;
        }

        temp=Q.Del();
    } while (1);
    
}

//Height of the Tree
int binarySearchTree::treeHeight(node *root)
{
    int heightL,heightR;
    if(root==NULL)
    {
        return 0;
    }
    if(root->left==NULL && root->right==NULL)
    {
        return 0;
    }
    heightL=treeHeight(root->left);
    heightR=treeHeight(root->right);

    if(heightR>heightL)
    {
        return(heightR+1);
    }
    return (heightL+1);
}


//Minimum Value in BST
int binarySearchTree::minValue(node *root)
{
    while(root->left!=NULL)
    {
        root=root->left;
    }
    return root->data;
}

//Maximum Value in BST
int binarySearchTree::maxValue(node *root)
{
    while(root->right!=NULL)
    {
        root=root->right;
    }
    return root->data;
}

//Finding Mirrored Tree 
void binarySearchTree::MirrorTree(node *root)
{
    node *temp;
    if(root!=NULL)
    {
        temp=root->left;
        root->left=root->right;
        root->right=temp;
        MirrorTree(root->left);
        MirrorTree(root->right);
    }
}

int main()
{
    binarySearchTree bst;
    int ch,key;
    char con[3];
    
    do
    {
        cout<<"\n\t\tMENU"<<endl;
        cout<<"1.) Insert a Node \n2.) In-Order Traversal \n3.) Pre-Order Traversal \n4.) Post-Order Traversal"<<endl;
        cout<<"5.) Height of the Tree \n6.) Minimum Data Value found in the tree"<<endl;
        cout<<"7.) Maximum Data Value found in the tree\n8.) Search a Node \n9.) Mirror of a Tree"<<endl;
        cout<<"10.) DFS\n11.) BFS\n12.) Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>ch;
        cout<<"---------------------------------------------------------------------------"<<endl;
        
        switch(ch)
        {
            case 1: bst.insert();
                    break;
                    
            case 2: cout<<"\nIn-Order Recursive Traversal is : ";
                    bst.inOrder(bst.root);
                    cout<<"\nIn-Order Non-Recursive Traversal is : ";
                    bst.inOrderNon();
                    break;
                    
            case 3: cout<<"\nPre-Order Recursive Traversal : ";
                    bst.preOrder(bst.root);
                    cout<<"\nPre-Order Non-Recursive Traversal : ";
                    bst.preOrderNon();
                    break;
                    
            case 4: cout<<"\nPost-Order Recursive Traversal : ";
                    bst.postOrder(bst.root);
                    cout<<"\nPost-Order Non-Recursive Traversal : ";
                    bst.postOrderNon();
                    break;

            case 5: cout<<"Height of the Tree is : "<<bst.treeHeight(bst.root)<<endl;
                    break;

            case 6: cout<<"Minimum Data Value found in the tree is : "<<bst.minValue(bst.root)<<endl;
                    break;

            case 7: cout<<"Maximum Data Value found in the tree is : "<<bst.maxValue(bst.root)<<endl;
                    break;
                    
            case 8: cout<<"Enter the data to search : ";
                    cin>>key;
                    bst.search(key);
                    break;

            case 9: cout<<"Mirroring the Binary Search Tree !!"<<endl;
                    bst.MirrorTree(bst.root);
                    break;

            case 10: cout<<"DFS : "<<endl;
                    bst.DFS();
                     break;

            case 11: cout<<"BFS : "<<endl;
                    bst.BFS();
                     break;

            case 12: break;

            default: cout<<"Wrong Input!! Enter number b/w 1 and 12"<<endl;
                     break;
        }
        
    }while(ch!=12);
   
    return 0;
}
