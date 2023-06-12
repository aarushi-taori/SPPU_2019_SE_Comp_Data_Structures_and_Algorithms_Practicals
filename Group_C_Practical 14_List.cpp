/* There are flight paths between cities. If there is a flight between city A and city B then there is an edge
 between cities. The cost of the edge can be the time that the flight takes to reach city B from A, or the 
 amount of fuel used for the journey. Represent this as a graph. The node can be represented by the airport
  name or name of the city.Use representation of the graph.Check whether the graph is connected or not. 
  Justify the storage representation used. */

  //USING ADJACENY LIST
  
#include<iostream>
using namespace std;
#define maxSize 20

class GraphNode
{
    public:
        string cityName;
        int time,fuel;
        GraphNode *next;
    
    GraphNode()
    {
        next=NULL;
        cityName="0";
        time=fuel=0;
    }
        
};

class stack
{
    private:
        GraphNode *array[maxSize];
        int top;

    public:
        stack()
        {
            for(int i=0;i<maxSize;i++)
            {
                array[i]=new GraphNode();
            }
            top=-1;
        }

        void push(GraphNode *temp)
        {
            if(top==maxSize-1)
            {
                cout<<"Stack Overflow"<<endl;
            }
            else
            {
                array[++top]=temp;
            }
        }
        GraphNode *pop()
        {
            if(!isEmpty())
            {
                GraphNode* temp=array[top];
                top--;
                return temp;
            }
        }
        int isEmpty()
        {
            if(top==-1)
            {
                return 1;
            }
            return 0;
        }
};

class queue
{
    private:
        GraphNode *array[maxSize];
        int front,rear,size;

    public:
        queue()
        {
            for(int i=0;i<maxSize;i++)
            {
                array[i]=new GraphNode();
            }
            front=rear=-1;
            size=0;
        }

        void add(GraphNode *temp)
        {
            if(rear==maxSize-1)
            {
                cout<<"Queue is Overflow"<<endl;
            }
            else
            {
                array[++rear]=temp;
                size++;
            }
        }

        GraphNode *del()
        {
            if(!isEmpty())
            {
                GraphNode *temp=array[++front];
                size--;
                return temp;
            }
        }

        int isEmpty()
        {
            if(front==rear)
            {
                return 1;
            }
            return 0;
        }
};

class flightsystem
{
    private:
        GraphNode *headlist[maxSize];
        int num;        //num of cities
        int visited[maxSize];

    public:
        flightsystem()
        {
            for(int i=0;i<maxSize;i++)
            {
                headlist[i]=new GraphNode();
            }
            num=0;
        }

        void create();
        void initvisit()
        {
            for(int i=0;i<num;i++)
            {
                visited[i]=0;
            }
        }
        int index(string u);
        void insertCity(string u);
        void insertFlight(string u,string v);
        void deleteCity(string u);
        void deleteFlight(string u,string v);
        void displayCity();
        void displayFlights();
        void searchCity(string u);
        void searchFlight(string u,string v);
        void DFSRec(string u);
        void DFSNonRec(string u);
        void BFS(string u);
};

void flightsystem::create()
{
    int n;
    string name;
    cout<<"Enter no. of cities : ";
    cin>>n;
    num=n;

    for(int i=0;i<n;i++)
    {
        cin>>name;
        headlist[i]->cityName=name;
    }
    cout<<"Flight System Created"<<endl;
}

int flightsystem::index(string u)
{
    for(int i=0;i<num;i++)
    {
        if(headlist[i]->cityName==u)
        {
            return i;
        }
    }
    return -1;  //City does not exist
}

void flightsystem::insertCity(string u)
{
    int pos=index(u);
    if(pos==-1)
    {
        cout<<"City Already Exists"<<endl;
    }
    else
    {
        headlist[num]->cityName=u;
        num++;
        cout<<"City inserted successfully"<<endl;
    }
}

void flightsystem::insertFlight(string u, string v)
{
    int pos1=index(u);
    int pos2=index(v);
    int fuel,time;
    GraphNode *tmp;
    cout<<"Enter Fuel : "<<endl;
    cin>>fuel;
    cout<<"Enter Time : "<<endl;
    cin>>time;
    GraphNode *temp1=new GraphNode();
    temp1->cityName=u;
    temp1->fuel=fuel;
    temp1->time=time;

    GraphNode *temp2=new GraphNode();
    temp2->cityName=v;
    temp2->fuel=fuel;
    temp2->time=time;

    for(tmp=headlist[pos1];tmp->next!=NULL;tmp=tmp->next);
    tmp->next=temp2;

    for(tmp=headlist[pos2];tmp->next!=NULL;tmp=tmp->next);
    tmp->next=temp1;
    cout<<"Flight inserted successfully"<<endl;
}

void flightsystem::deleteCity(string u)
{
    int pos = index(u);
    if (pos == -1) {
        cout << "City does not exist" << endl;
        return;
    }

    // Remove the city from the adjacency lists of other cities
    for (int i = 0; i < num; i++) 
    {
        if (headlist[i]->cityName != "0") 
        {
            GraphNode* tmp = headlist[i];
            while (tmp->next != NULL) 
            {
                if (tmp->next->cityName == u) 
                {
                    GraphNode* todel = tmp->next;
                    tmp->next = todel->next;
                    delete todel;
                } 
                else 
                {
                    tmp = tmp->next;
                }
            }
        }
    }

    // Shift the remaining cities to fill the empty space
    for (int i = pos; i < num - 1; i++) {
        headlist[i] = headlist[i + 1];
    }

    // Reset the last city
    headlist[num - 1] = new GraphNode();

    num--;
    cout << "City deleted successfully" << endl;
}


void flightsystem::deleteFlight(string u, string v)
{
    int pos1=index(u);
    int pos2=index(v);
}

void flightsystem::displayCity()
{
    for(int i=0;i<num;i++)
    {
        cout<<headlist[i]->cityName<<endl;
    }
    cout<<endl;
}

void flightsystem::displayFlights()
{
    int i;
    GraphNode *temp;
    
    for(i=0;i<num;i++)
    {
        temp=headlist[i];
        while(temp!=NULL)
        {
            cout<<temp->cityName<<" -> ";
            temp=temp->next;
        }
        cout<<endl;
    }
}

void flightsystem::searchCity(string u)
{
    int i;
    GraphNode *temp;
    for(i=0;i<num;i++)
    {
        if(headlist[i]->cityName==u)
        {
            cout<<"City found at position "<<i<<endl;
            break;
        }
    }
    
    cout<<"Flights from this city are : "<<endl;
    
    temp=headlist[i];
    while(temp->next!=NULL)
    {
        temp=temp->next;
        cout<<temp->cityName<<endl;
        
    }
}

void flightsystem::searchFlight(string u, string v)
{
    int pos=index(u);
    GraphNode *temp=headlist[pos];
    while(temp->next!=NULL)
    {
        temp=temp->next;
        if(temp->cityName==v)
        {
            cout<<"Flight exists between "<<u<<" and "<<v<<endl;
            cout<<"Time of flight : "<<temp->time<<endl;
            cout<<"Fuel Required during flight : "<<temp->fuel<<endl;
            return;
        }
    }
    //else
    cout<<"No Direct Flight exists between "<<u<<" and "<<v<<endl;
}

void flightsystem::DFSRec(string u)
{
    cout<<u<<"\t";
    visited[index(u)]=1;
    for(GraphNode *temp=headlist[index(u)];temp!=NULL;temp=temp->next)
    {
        if(visited[index(temp->cityName)]==0)
        {
            DFSRec(temp->cityName);
        }
    }
}

void flightsystem::DFSNonRec(string u)
{
    stack s1;
    int pos=index(u);
    GraphNode *temp=headlist[pos];

    s1.push(temp);
    while(!s1.isEmpty())
    {
        temp=s1.pop();
        pos=index(temp->cityName);
        if(visited[pos]==0)
        {
            cout<<temp->cityName<<"\t";
            visited[pos]=1;
            for(GraphNode *tmp=headlist[pos];tmp!=NULL;tmp=tmp->next)
            {
                if(visited[index(tmp->cityName)]==0)
                {
                    s1.push(tmp);
                }
            }
        }  
    }
}

void flightsystem::BFS(string u)
{
    queue q1;
    int pos=index(u);
    GraphNode *temp=headlist[pos];

    visited[pos]=1;
    q1.add(temp);
    while(!q1.isEmpty())
    {
        temp=q1.del();
        cout<<temp->cityName<<"\t";
        for(GraphNode *tmp=headlist[index(temp->cityName)];tmp!=NULL;tmp=tmp->next)
        {
            pos=index(tmp->cityName);
            if(visited[pos]==0)
            {
                q1.add(tmp);
                visited[pos]=1;
            }
        }
    }
}



int main()
{
    flightsystem fs;
    int ch;
    string city1,city2;
    
    fs.create();
    do
    {
        cout<<"------------------------------------------------------------------------------"<<endl;
        cout<<"\tMENU"<<endl;
        cout<<"1. Insert City\n2. Insert Flight Route\n3. Delete City\n4. Delete Flight Route\n5. Search City"<<endl;
        cout<<"6. Search Flight Route\n7. Display Cities\n8. Display Flight Route\n9. DFS\n10.BFS\n11. Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>ch;
        cout<<"------------------------------------------------------------------------------"<<endl;
        
        switch(ch)
        {
            case 1: cout<<"Enter the name of the City to enter : ";
                    cin>>city1;
                    fs.insertCity(city1);
                    break;
                    
            case 2: cout<<"Enter source city : ";
                    cin>>city1;
                    cout<<"Enter destination city : ";
                    cin>>city2;
                    fs.insertFlight(city1,city2);
                    break;
                   
            case 3: cout<<"Enter the name of the City to delete : ";
                    cin>>city1;
                    fs.deleteCity(city1);
                    break;

            case 4: cout<<"Enter source city : ";
                    cin>>city1;
                    cout<<"Enter destination city : ";
                    cin>>city2;
                    fs.deleteFlight(city1,city2);
                    break;
          
            case 5: cout<<"Enter the name of city to search : ";
                    cin>>city1;
                    fs.searchCity(city1);
                    break;
                    
            case 6: cout<<"Enter source city : ";
                    cin>>city1;
                    cout<<"Enter destination city : ";
                    cin>>city2;
                    fs.searchFlight(city1,city2);
                    break;
                   
            case 7: cout<<"Displaying Cities : "<<endl;
                    fs.displayCity();
                    cout<<endl;
                    break;
                
            case 8: cout<<"Displaying Flight Routes : "<<endl;
                    fs.displayFlights();
                    break;
              
            case 9: cout<<"Enter the starting city : ";
                    cin>>city1;
                    cout<<"DFS Recursive"<<endl;
                    fs.initvisit();
                    fs.DFSRec(city1);
                    cout<<"DFS Non-Recursive"<<endl;
                    fs.initvisit();
                    fs.DFSNonRec(city1);
                    break;

            case 10: cout<<"Enter the starting city : ";
                    cin>>city1;
                    cout<<"BFS"<<endl;
                    fs.initvisit();
                    fs.BFS(city1);
            case 11: break;
            
            default : cout<<"Incorrect Choice "<<endl;
                      break;
        }
    }while(ch!=11);
    return 0;
    
}