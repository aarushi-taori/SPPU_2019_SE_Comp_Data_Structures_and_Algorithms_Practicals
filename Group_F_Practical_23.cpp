/*Department maintains student information. The file contains roll number,name,division and address. Allow 
users to add, delete information about students. Display information of a particular employee. If the record 
of the student does not exist an appropriate message is displayed. If it is, then the system displays the 
student details. Use a sequential file to maintain the data.*/

#include<iostream>
#include <fstream>
#include<string.h>
using namespace std;

class student
{
    private:
        int roll;
        char name[21];
        char div[3];
        char address[31];
    
    public:
    
    void getData()
    {
        cout<<"Enter Roll No. : ";
        cin>>roll;
        cout<<"Enter Name : ";
        cin>>name;
        cout<<"Enter Divison : ";
        cin>>div;
        cout<<"Enter Address : ";
        cin>>address;
    }
    
    int getRoll()
    {
        return roll;
    }
    void displayData()
    {
        cout<<"Roll No. : "<<roll<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Divison : "<<div<<endl;
        cout<<"Address : "<<address<<endl;
    }

    bool search(char s[20])
    {
        if(strcmp(s,name)==0)
        {
            return true;
        }
        return false;
    }
};

class file
{
    private:
        fstream fs;
        student s;
        int countStudent;
        
   public:
            
         file()
         {
            countStudent=0;
         }
         
         void create();
         void addInfo();
         void deleteInfo();
         void displayInfo();
         void searchInfo();
};

void file::create()
{
    int n;
    cout<<"Enter the number of students : ";
    cin>>n;
    countStudent=n;
    
    fs.open("studentData.dat",ios::out);
    
    do
    {   
        s.getData();
        fs.write((char*)&s,sizeof(s));
        n--;
        
    }while(n!=0);
    
    fs.close();
}

void file::addInfo()
{
   fs.open("studentData.dat",ios::app);
   s.getData();
   fs.write((char *)&s,sizeof(s));
   cout<<"Data Inserted Successfully!!"<<endl;
   fs.close();
}

void file::deleteInfo()
{
    int pos,index;
    fstream tfp;

    cout<<"Enter the Roll No to be deleted : ";
    cin>>index;

    fs.open("studentData.dat",ios::in);
    tfp.open("TempData.dat",ios::out);
    while(fs.read((char *)&s,sizeof(s)))
    {
        if(s.getRoll()==index)
        {
            cout<<"Deleting Record : "<<endl;
            s.displayData();
        }
        else
        {
            tfp.write((char *)&s,sizeof(s));
        }
    }
 
    fs.close();
    tfp.close();

    remove("studentData.dat");
    rename("TempData.dat","studentData.dat");

}

void file::displayInfo()
{
    fs.open("studentData.dat",ios::in);
    while (!fs.eof())
    {

        fs.read((char*)&s,sizeof(s));
        if (!fs.eof())
        {
            s.displayData();
            cout<<"\n"<<endl;
        }
        
    }
    fs.close();
}

void file::searchInfo()
{
    char sname[20];
    bool flag;
    cout<<"Enter the Name of the Student to be Searched : ";
    cin>>sname;
    fs.open("studentData.dat",ios::in);
    while (!fs.eof())
    {
        fs.read((char*)&s,sizeof(s));
        flag=s.search(sname);
        if(flag==true)
        {
            cout<<"Record Found!!"<<endl;
            s.displayData();
            break;
        }
    }
    //cout<<"Record Not found!!"<<endl;
}

int main()
{
    file f;
    int ch;
    
    f.create();
    
    do
    {
        cout<<"\n\t\tMENU"<<endl;
        cout<<"1. Add Record\n2.Delete Record\n3. Search Record\n4. Display Records\n6. Exit"<<endl;
        cout<<"Enter your Choice : ";
        cin>>ch;
        cout<<"------------------------------------------------------------"<<endl;
        
        switch(ch)
        {
            case 1: f.addInfo();
                    break;

            case 2: f.deleteInfo();
                    break;

            case 3: f.searchInfo();
                    break;
            
            case 4: cout<<"Displaying Details : "<<endl;
                    f.displayInfo();
                    break;
            
            case 5: break;
            
            default: cout<<"Incorrect Choice"<<endl;
                     break;
        }
        
    }while(ch!=5);
    
    return 0;
}
    
