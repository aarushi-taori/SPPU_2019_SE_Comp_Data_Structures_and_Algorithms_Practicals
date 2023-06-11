/* Construct an expression tree from the given prefix expression e.g. +--a*bc/def and traverse it using post order traversal
(non- recursive) and then delete the entire tree. */

#include<iostream>
#include<string>
using namespace std;

class node
{
    public: 
        char data;
        node *left,*right;

        node()
        {
            data='0';
            left=NULL;
            right=NULL;
        }
};

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

        node* getTop()
        {
            node *temp=stacks[top];
            return temp;
        }
};


class expressionTree
{
    public:
        node* root;

    public:
        expressionTree()
        {
            root=NULL;
        }

    int isDigit(char c);
    int isAlpha(char c);
    node* constructExpressionTree(string prefix);
    void postOrderNonRecursive();
};


int expressionTree::isDigit(char c)
{
    if(c>=0 && c<=9)
    {
        return 1;
    }
    return 0;
}

int expressionTree::isAlpha(char c)
{
    if((c>=65 && c<=90)||(c>=97 && c<=122))
    {
        return 1;
    }
    return 0;
}

node *expressionTree::constructExpressionTree(string prefix)
{
    char ch;
    int prefixLength=prefix.length();
    stack s;

    //Scan expression from right to left
    for(int i=prefixLength-1;i>=0;i--)
    {
        ch=prefix[i];
        if(isDigit(ch) || isAlpha(ch))
        {
            node *newNode=new node;
            newNode->data=ch;
            s.push(newNode);
        }
        else
        {
            node *newNode=new node;
            newNode->data=ch;
            newNode->left=s.pop();
            newNode->right=s.pop();
            s.push(newNode);
        }
    }

    root=s.getTop();
    return root;
}

void expressionTree::postOrderNonRecursive()
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
        delete temp;
    }
    cout<<endl;
}

int main()
{
    string prefix;
    expressionTree et;
    cout<<"Enter the prefix expression to convert : ";
    cin>>prefix;
    et.constructExpressionTree(prefix);
    cout<<"Post Order Traversal Gives : "<<endl;
    et.postOrderNonRecursive();
    cout<<endl;
    return 0;
}