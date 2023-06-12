/* There are flight paths between cities. If there is a flight between city A and city B then there is an edge
 between cities. The cost of the edge can be the time that the flight takes to reach city B from A, or the 
 amount of fuel used for the journey. Represent this as a graph. The node can be represented by the airport
  name or name of the city.Use representation of the graph.Check whether the graph is connected or not. 
  Justify the storage representation used. */

//USING AJACENCY MATRIX

#include<iostream>
using namespace std;
#define maxSize 20

class stack
{
    private:
        string array[maxSize];
        int top;

    public:
        stack()
        {
            top=-1;
        }

        void push(string u)
        {
            array[++top]=u;
        }

        string pop()
        {
            string temp=array[top];
            top--;
            return temp;
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
        string arr[maxSize];
        int front,rear,size;

    public:
        queue()
        {
            front=rear=-1;
            size=0;
        }

        void add(string u)
        {
            if(rear==maxSize-1)
            {
                cout<<"Queue Overflow"<<endl;
            }
            else
            {
                size++;
                arr[++rear]=u;
            }
        }

        string del()
        {
            if(!isEmpty())
            {
                string temp=arr[++front];
                size--;
                return temp;
            }
        }

        int isEmpty()
        {
            if(front==rear==-1)
            {
                return 1;
            }
            return 0;
        }
};

class graph
{
    private:
        int timeMatrix[maxSize][maxSize];
        int fuelMatrix[maxSize][maxSize];
        string cityNames[maxSize];
        int num;        //Number of Cities
        int visited[maxSize];

    public:
        graph()
        {
            num=0;
            for(int i=0;i<maxSize;i++)
            {
                cityNames[i]="0";
                for(int j=0;j<maxSize;j++)
                {
                    timeMatrix[i][j]=0;
                    fuelMatrix[i][j]=0;
                }
            }

        }

        void create();
        void initvisit();
        int flightIndex(string u);
        void addCity(string u);
        void addFlight(string u,string v);
        void matrixdisplay();
        void displayCity();
        void displayFlights();
        void searchFlight(string u,string v);
        //void dfsSearch(string u,string v);
        void searchCity(string u);
        void deleteFlight(string u,string v);
        void deleteCity(string u);
        void dfsRec(string u);
        void dfsNonRec(string u);
        void bfs(string u);
        bool isConnected(string u);
    
};

void graph::create()
{
    int n;
    cout<<"Enter number of cities to add : "<<endl;
    cin>>n;
    num=n;
    for(int i=0;i<n;i++)
    {
        cin>>cityNames[i];
    }
    cout<<"Flight System Created"<<endl;
}

void graph::initvisit()
{
    for(int i=0;i<maxSize;i++)
    {
        visited[i]=0;
    }
}

int graph::flightIndex(string u)
{
    for(int i=0;i<num;i++)
    {
        if(cityNames[i]==u)
        {
            return i;
        }
    }

    return -1;      //Flight Not Found
}

void graph::addCity(string u)
{
    int pos=flightIndex(u);
    if(pos==-1)
    {
        cityNames[num]=u;
        num++;
    }
    else
    {
        cout<<"City Already Exists"<<endl;
    }
}

void graph::addFlight(string u, string v)
{
    int pos1=flightIndex(u);
    int pos2=flightIndex(v);
    int fuel,time;

    if(pos1==-1)
    {
        cout<<u<<" city does not exist"<<endl;
    }
    else if(pos2==-1)
    {
        cout<<v<<" city does not exist"<<endl;
    }
    else
    {
        cout<<"Enter the Fuel Required : ";
        cin>>fuel;
        cout<<"Enter the Time Required : ";
        cin>>time;
        timeMatrix[pos1][pos2]=time;
        fuelMatrix[pos1][pos2]=fuel;
        timeMatrix[pos2][pos1]=time;
        fuelMatrix[pos2][pos1]=fuel;
    }
}

void graph::displayCity()
{
    for(int i=0;i<num;i++)
    {
        cout<<cityNames[i]<<endl;
    }
}

void graph::displayFlights()
{
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
            if(timeMatrix[i][j]!=0)
            {
                cout<<"Flight Exists from "<<cityNames[i]<<" to "<<cityNames[j]<<endl;
            }
        }
    }
}

void graph::searchFlight(string u, string v)
{
    int pos1=flightIndex(u);
    int pos2=flightIndex(v);

    if(timeMatrix[pos1][pos2]!=0)
    {
        cout<<"Flight Exists from "<<u<<" to "<<v<<endl;
        cout<<"Fuel Required : "<<fuelMatrix[pos1][pos2]<<endl;
        cout<<"Time Required : "<<timeMatrix[pos1][pos2]<<endl;
    }
    else
    {
        cout<<"Direct Flight Does not Exist"<<endl;
    }
}

void graph::searchCity(string u)
{
    int pos=flightIndex(u);
    if(pos!=-1)
    {
        cout<<"City Exists at pos "<<pos<<endl;
    }
    else
    {
        cout<<"City does not exist"<<endl;
    }
}

void graph::deleteFlight(string u, string v)
{
    int pos1=flightIndex(u);
    int pos2=flightIndex(v);
    fuelMatrix[pos1][pos2]=0;
    timeMatrix[pos1][pos2]=0;
}

void graph::deleteCity(string u)
{
    int pos=flightIndex(u);
    cityNames[pos]="0";
    for(int i=0;i<num;i++)
    {
        fuelMatrix[pos][i]=0;
        timeMatrix[pos][i]=0;
        fuelMatrix[i][pos]=0;
        timeMatrix[i][pos]=0;

    }
}

void graph::dfsRec(string u)
{
    cout<<u<<"\t";
    visited[flightIndex(u)]=1;
    for(int i=0;i<num;i++)
    {
        if(timeMatrix[flightIndex(u)][i]!=0 && visited[i]==0)
        {
            dfsRec(cityNames[i]);
        }
    }

}

void graph::dfsNonRec(string u)
{
    stack s1;
    string temp;
    int pos=flightIndex(u);
    s1.push(u);
    while(!s1.isEmpty())
    {
        temp=s1.pop();
        cout<<temp<<"\t";
        pos=flightIndex(temp);
        visited[pos]=1;
        for(int i=0;i<num;i++)
        {
            if(timeMatrix[pos][i]!=0 && visited[i]==0)
            {
                s1.push(cityNames[i]);
            }
        }
    }
}

void graph::bfs(string u)
{
    queue q1;
    int pos;
    string temp;

    pos=flightIndex(u);
    visited[pos]=1;
    q1.add(u);
    while(!q1.isEmpty())
    {
        temp=q1.del();
        cout<<temp<<"\t";
        pos=flightIndex(temp);
        for(int i=0;i<num;i++)
        {
            if(timeMatrix[pos][i]!=0 && visited[i]==0)
            {
                q1.add(cityNames[i]);
                visited[i]=1;
            }
        }
    }
}

bool graph::isConnected(string u)
{
    dfsRec(u);

    for(int i=0;i<num;i++)
    {
        if(visited[i]==0)
        {
            return false;
        }
    }
    return true;
}

void graph :: matrixdisplay()
{
    cout<<"Displaying City Matrix"<<endl;
    displayCity();

    cout<<"Displaying Time Matrix"<<endl;
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
            cout<<timeMatrix[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout<<"Displaying Fuel Matrix"<<endl;
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
            cout<<fuelMatrix[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int main()
{
    graph fs;
    string city1,city2;
    int ch;
    bool flag;

    fs.create();
    do
    {
        cout<<"\n------------------------------------------------------------------------------\n"<<endl;
        cout<<"\tMENU"<<endl;
        cout<<"1. Insert City\n2. Insert Flight Route\n3. Delete City\n4. Delete Flight Route\n5. Search City"<<endl;
        cout<<"6. Search Flight Route\n7. Display Cities\n8. Display Flight Route\n9. Display Matrix"<<endl;
        cout<<"10. DFS\n11. BFS\n12. Check if Connected or not\n13. Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>ch;
        cout<<"------------------------------------------------------------------------------\n"<<endl;
        
        switch(ch)
        {
            case 1: cout<<"Enter the name of the City to enter : ";
                    cin>>city1;
                    fs.addCity(city1);
                    break;
                    
            case 2: cout<<"Enter source city : ";
                    cin>>city1;
                    cout<<"Enter destination city : ";
                    cin>>city2;
                    fs.addFlight(city1,city2);
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
                    
            case 9: fs.matrixdisplay();
                    break;

            case 10: cout<<"Enter starting city : ";
                    cin>>city1;
                    cout<<"\nRecursive DFS"<<endl;
                    fs.initvisit();
                    fs.dfsRec(city1);
                    cout<<"\nNon-Recursive DFS"<<endl;
                    fs.initvisit();
                    fs.dfsNonRec(city1);
                    break;

            case 11:cout<<"Enter starting city : ";
                    cin>>city1;
                    cout<<"BFS"<<endl;
                    fs.initvisit();
                    fs.bfs(city1);

            case 12: cout<<"Enter starting city : ";
                    cin>>city1;
                    fs.initvisit();
                    flag=fs.isConnected(city1);
                    if(flag==true)
                    {
                        cout<<"\nIt is a Connected Graph"<<endl;
                    }
                    else
                    {
                        cout<<"\nIt is Not Connected Graph"<<endl;
                    }
                    break;
            case 13: break;

            default : cout<<"Incorrect Choice "<<endl;
                      break;
        }
    }while(ch!=13);
    
    return 0;
}