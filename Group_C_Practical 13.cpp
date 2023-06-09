/* Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform BFS. 
Use the map of the area around the college as the graph. Identify the prominent landmarks as nodes and perform DFS and BFS on that.
*/

/*
Name : Aarushi Taori
Class : SE B
Roll no. : 75
*/

#include<iostream>
#include<string>
using namespace std;
#define maxSize 20


class node
{
    public:
        string landmark;
        node *link;
        int distance;
        
        node()
        {
            landmark="NA";
            link=NULL;
            distance=0;
        }
};

//Stack
class stack
{
    private:
        node *stacks[50];
        int top;
    
    public:

        stack()
        {
            for(int i=0;i<50;i++)
            {
                stacks[i]=new node;
            }

            top=-1;
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
            if(top!=maxSize-1)
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
        int rear,front,size;

    public:
        queue()
        {
            for(int i=0;i<50;i++)
            {
                queues[i]=new node;
            }
            front=rear=-1;
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





class college
{
    private:
        node *List[maxSize];
        int placeCount;
        int visited[maxSize];
        
   public:
        
        college()
        {
            for(int i=0;i<maxSize;i++)
            {
                List[i]=new node;
            }
            placeCount=0;
        }
        
        void create();
        void insertPlace(string name);
        void insertPath(string name1,string name2);
        int index(string c);
        void displayPlaces();
        void displayRoutes();
        void DFSRec(string n);
        void DFSNonRec(string n);
        void BFS(string n);
        
        void initvisit()
        {
            for(int i=0;i<maxSize;i++)
            {
                visited[i]=0;
            }
            
        }
};


int college::index(string c)
{
    for(int i=0;i<placeCount;i++)
    {
        if(List[i]->landmark==c)
        {
            return i;
        }
    }
    return -1;
}

void college::create()
{
    int n;
    cout<<"How many landmarks do you want to enter ?";
    cin>>n;
    if(n<=0)
    {
        cout<<"Number of landmarks should be greater than 0"<<endl;
        return;
    }
    placeCount=n;
    cout<<"Enter the Landmarks :"<<endl;
    for(int i=0;i<placeCount;i++)
    {
        cin>>List[i]->landmark;
    }
    cout<<"College Map Created !!"<<endl;
}

void college::insertPlace(string name)
{
    int flag=index(name);
    
    if(flag>=0)
    {
        cout<<"Landmark already exists!!"<<endl;
    }
    else
    {
        List[placeCount]->landmark=name;
        placeCount++;
        cout<<"Landmark Inserted Successfully !!"<<endl;
    }
}

void college::insertPath(string name1,string name2)
{
    int pos1=index(name1);
    int pos2=index(name2);
    node *newNode1=new node();
    node *newNode2=new node();
    newNode1->landmark=name2;
    newNode2->landmark=name1;
    
    //cout<<"Enter the Distance : ";
   // cin>>newNode->distance;
    node *temp=List[pos1];
    while(temp->link!=NULL)
    {
        temp=temp->link;
    }
    temp->link=newNode1;

    temp=List[pos2];
    while(temp->link!=NULL)
    {
        temp=temp->link;
    }
    temp->link=newNode2;
    cout<<"Route Inserted Successfully!!"<<endl;
}


void college::displayPlaces()
{
    for(int i=0;i<placeCount;i++)
    {
        cout<<List[i]->landmark<<endl;
    }
    cout<<endl;
}


void college::displayRoutes()
{
    int i;
    node *temp;
    
    for(i=0;i<placeCount;i++)
    {
        temp=List[i];
        while(temp->link!=NULL)
        {
            cout<<temp->landmark<<" -> ";
            temp=temp->link;
        }
        cout<<temp->landmark<<endl;
    }
}


void college::DFSRec(string n)
{
    cout<<n<<"\t";
    visited[index(n)]=1;
    for(node *temp=List[index(n)];temp!=NULL;temp=temp->link)
    {
        if(visited[index(temp->landmark)]==0)
        {
            DFSRec(temp->landmark);
        }
    }
}

void college::DFSNonRec(string n)
{
    stack s1;
    int pos=index(n);
    node *temp=List[pos];

    s1.push(temp);
    while(!s1.isEmpty())
    {
        temp=s1.pop();
        pos=index(temp->landmark);
        if(visited[pos]==0)
        {
            cout<<temp->landmark<<"\t";
            visited[pos]=1;
            for(node *tmp=List[pos];tmp!=NULL;tmp=tmp->link)
            {
                if(visited[index(tmp->landmark)]==0)
                {
                    s1.push(tmp);
                }
            }
        }  
    }
    

}

void college::BFS(string n)
{
    queue q1;
    int pos=index(n);
    node *temp=List[pos];

    visited[pos]=1;
    q1.Add(temp);
    while(!q1.isEmpty())
    {
        temp=q1.Del();
        cout<<temp->landmark<<"\t";
        for(node *tmp=List[index(temp->landmark)];tmp!=NULL;tmp=tmp->link)
        {
            pos=index(tmp->landmark);
            if(visited[pos]==0)
            {
                q1.Add(tmp);
                visited[pos]=1;
            }
        }
    }
}

int main()
{
    college c;
    int ch;
    string place1,place2;
    
    c.create();
    do
    {
        cout<<"\n------------------------------------------------------------------------------"<<endl;
        cout<<"\tMENU"<<endl;
        cout<<"1. Insert Landmark\n2. Insert Path\n3. Display Landmarks\n4. Display Paths"<<endl;
        cout<<"5. Recursive DFS\n6. Non-REcursive DFS\n7. BFS\n8. Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>ch;
        cout<<"------------------------------------------------------------------------------"<<endl;
        
        switch(ch)
        {
            case 1: cout<<"Enter the name of the Landmark to enter : ";
                    cin>>place1;
                    c.insertPlace(place1);
                    break;
                    
            case 2: cout<<"Enter starting landmark : ";
                    cin>>place1;
                    cout<<"Enter destination landmark : ";
                    cin>>place2;
                    c.insertPath(place1,place2);
                    break;
                    
            case 3: cout<<"Displaying Landmarks : "<<endl;
                    c.displayPlaces();
                    cout<<endl;
                    break;
                
            case 4: cout<<"Displaying Routes : "<<endl;
                    c.displayRoutes();
                    break;
              
            case 5: cout<<"Enter the starting landmark : ";
                    cin>>place1;
                    c.initvisit();
                    cout<<"DFS Recursively : ";
                    c.DFSRec(place1);
                    break;
                    
            case 6: cout<<"Enter the starting landmark : ";
                    cin>>place1;
                    c.initvisit();
                    cout<<"DFS Non-Recursively : ";
                    c.DFSNonRec(place1);
                    break;

            case 7: cout<<"Enter the starting landmark : ";
                    cin>>place1;
                    c.initvisit();
                    cout<<"BFS : ";
                    c.BFS(place1);
                    break;

            case 8: break;
            
            default : cout<<"Incorrect Choice "<<endl;
                      break;
        }
    }while(ch!=8);
    
    return 0;
}
