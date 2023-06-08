/*A dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, 
updating values of any entry.provide facility to display data in  ascending/descending order. also find max 
no. of comparisons required to find a keyword. Use height balanced tree and find time complexity for finding
a keyword*/


#include<iostream>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;

class AVLnode
{
    public:
        char keyword[20],meaning[20];
        AVLnode *left,*right;
        int ht;
        
    public:
        AVLnode()
        {
            left=right=NULL;
            ht=0;
        }
        
        friend class AVLtree;
};

class AVLtree
{
    public:
        AVLnode *root;
        int count;
        
        AVLtree()
        {
            root=new AVLnode();
            root=NULL;
            count=0;
        }
        
        AVLnode *rotate_left(AVLnode *x);
        AVLnode *rotate_right(AVLnode *x);
        AVLnode *LL(AVLnode *x);
        AVLnode *RR(AVLnode *x);
        AVLnode *LR(AVLnode *x);
        AVLnode *RL(AVLnode *x);
        
        int height(AVLnode *T);
        int BalanceFactor(AVLnode *T);
        AVLnode *insert(AVLnode *root,char newkey[20],char newMean[20]);
        AVLnode *search(AVLnode *root,char key[20]);
        void inorder(AVLnode *root);
};

AVLnode *AVLtree::rotate_left(AVLnode *x)
{
    AVLnode *y;
    y=x->right;
    x->right=y->left;
    y->left=x;
    x->ht=height(x);
    y->ht=height(y);
    return y;
}

AVLnode *AVLtree::rotate_right(AVLnode *x)
{
    AVLnode *y;
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->ht=height(x);
    y->ht=height(y);
    return y;
}

AVLnode *AVLtree::LL(AVLnode *x)
{
    cout<<"Performing LL Rotation"<<endl;
    x=rotate_right(x);
    return x;
}

AVLnode *AVLtree::RR(AVLnode *x)
{
    cout<<"Performing RR Rotation"<<endl;
    x=rotate_left(x);
    return x;
}

AVLnode *AVLtree::LR(AVLnode *x)
{
    cout<<"Performing LR Rotation"<<endl;
    x->left=rotate_left(x->left);
    x=rotate_right(x);
    return x;
}

AVLnode *AVLtree::RL(AVLnode *x)
{
    cout<<"Performing RL Rotation"<<endl;
    x->right=rotate_right(x->right);
    x=rotate_left(x);
    return x;
}

int AVLtree::height(AVLnode *T)
{
    int hl,hr;
    if(T==NULL)
    {
        return 0;
    }
    
    if(T->left==NULL && T->right==NULL)
    {
        return 0;
    }
    
    hl=height(T->left);
    hr=height(T->right);
    
    if(hl<hr)
    {
        return hr+1;
    }
    else
    {
        return hl+1;
    }
}

int AVLtree::BalanceFactor(AVLnode *T)
{
    int lh,rh;
    if(T==NULL)
    {
        return 0;
    }
    else
    {
        if(T->left==NULL)
        {
            lh=0;
        }
        else
        {
            lh=1+T->left->ht;
        }
        
        if(T->right==NULL)
        {
            rh=0;
        }
        else
        {
            rh=1+T->right->ht;
        }
       
    }
   
    cout<<"Balance Factor of "<<T->keyword<<" : "<<lh-rh<<endl;
    return(lh-rh);
}

AVLnode *AVLtree::insert(AVLnode *root,char newkey[20],char newMean[20])
{
    AVLnode *curr;
    int lh,rh;
    
    if(root==NULL)
    {
        curr=new AVLnode;
        strcpy(curr->keyword,newkey);
        strcpy(curr->meaning,newMean);
        root=curr;
    }
    else
    {

        if(strcmp(newkey,root->keyword)<0)
        { 
            root->left=insert(root->left,newkey,newMean);
            
            if(BalanceFactor(root)==2)
            {
                if(strcmp(newkey,root->left->keyword)<0)
                {
                    
                    root=LL(root);
                }
                else
                {
                    root=LR(root);
                }
            }
       }
       else if(strcmp(newkey,root->keyword)>0)
       {
            root->right=insert(root->right,newkey,newMean);
            
            if(BalanceFactor(root)==-2)
            {
                if(strcmp(newkey,root->right->keyword)>0)
                {
                    root=RR(root);
                }
                else
                {
                    root=RL(root);
                }
            }
        }
        else
        {
            cout<<"Duplicate"<<endl;
        }
   }
   root->ht=height(root);
   return root;
}

AVLnode *AVLtree::search(AVLnode *root,char key[20])
{
    AVLnode *temp=root;
    if(temp==NULL)
    {
        cout<<"Empty VL Tree"<<endl;
    }
    while(temp!=NULL)
    {
        if(strcmp(temp->keyword,key)==0)
        {
            return temp;
        }
        else if(strcmp(key,temp->keyword)<0)
        {
            temp=temp->left;
        }
        else
        {
            temp=temp->right;
        }
        count++;
    }
    
    return temp;

}

void AVLtree::inorder(AVLnode *root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        cout<<root->keyword<<" : "<<root->meaning<<endl;
        inorder(root->right);
    }
}

int main()
{   
    AVLtree at;
    AVLnode *temp;
    int ch;
    char word[20],mean[20];

    do
    {
        cout<<"\n\t\tMENU"<<endl;
        cout<<"1. Insert a keyword\n2. Search a keyword\n3. Display in Ascending Order\n4. Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>ch;
        cout<<"------------------------------------------------------------------------"<<endl;
        
        switch(ch)
        {
            case 1: cout<<"Enter the keyword to insert : ";
                    cin>>word;
                    cout<<"Enter its meaning : ";
                    cin>>mean;
                    at.root=at.insert(at.root,word,mean);
                    cout<<"Keyword Inserted Successfully"<<endl;
                    break;
                    
            case 2: cout<<"Enter the keyword to search : ";
                    cin>>word;
                    temp=at.search(at.root,word);
                    if(temp!=NULL)
                    {
                        cout<<"Keyword Found"<<endl;
                        cout<<temp->keyword<<" : "<<temp->meaning<<endl;
                    }
                    else
                    {
                        cout<<"Keyword Not found"<<endl;
                    }
                    break;
                        
                
            case 3: cout<<"Displaying AVL Tree Contents in Ascending Order : "<<endl;
                    at.inorder(at.root);
                    break;
            
            case 4: break;
            
            default: cout<<"Wrong Input!"<<endl;
                     break;
        }
        
    }while(ch!=4);
    
    return 0;
}
