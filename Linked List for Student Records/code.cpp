#include<string>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};


class Node{
	private:
		Node* next=nullptr;
		StudentRecord* element=nullptr;
	public:
	    Node* get_next() {
	        return next; 
	    }
	    StudentRecord* get_element() {
	        return element; 
	    }

	    void set_next(Node* value){
	    	next = value;
	    }
	    void set_element(StudentRecord* student){
	    	element = student;
	    }

};


class Entity {
private:
    string name;
    Node* iterator=nullptr;

public:
    string get_name() const{
        return name;
    }
    void set_name(string Name) {
        name = Name;
    }
    Node* get_iterator() const{
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};


class LinkedList : public Entity {
    
    public:
    void add_student(const StudentRecord& student)
    {
        Node *ptr=new Node();
        ptr->set_element(new StudentRecord(student));

        if(get_iterator()==nullptr)
        {
            set_iterator(ptr);
            ptr->set_next(nullptr);
        }
        else
        {
            Node *temp=new Node();
            temp=get_iterator();
            set_iterator(ptr);
            ptr->set_next(temp);
        }
    }
    
    void delete_student(string studentName)
    {
        Node *prev=new Node();
        Node *ptr=new Node();
        ptr=get_iterator();
        while(ptr!=nullptr)
        {
            string name=ptr->get_element()->get_studentName();
            if(name.compare(studentName)==0)
            {
                if(ptr==get_iterator())
                {
                    set_iterator(ptr->get_next());
                    ptr=nullptr;
                }
                else
                {
                    prev->set_next(ptr->get_next());
                    ptr=nullptr;
                }
                break;
            }
            prev=ptr;
            ptr=ptr->get_next();
        }
    }
};

vector<StudentRecord> students;
vector<LinkedList> EntityArray;

bool entitypresent(string entry)
{
    for(auto& obj:EntityArray)
    {
        if(obj.get_name().compare(entry)==0)
        return true;
    }
    return false;
}

bool namepresent(string sname)
{
    for(size_t i=0;i<students.size();i++)
    {
        if(students[i].get_studentName().compare(sname)==0)
        return true;
    }
    return false;
}

bool rollpresent(string rollno)
{
    for(size_t i=0;i<students.size();i++)
    {
        if(students[i].get_rollNumber()==rollno)
        return true;
    }
    return false;
}

vector<StudentRecord> duplicate;

void read_input_file(string file_path)
{
    //creating objects of StudentRecord
    fstream fp;
    fp.open(file_path,ios::in); 

    if(fp.is_open())  
    {
        string temp;
        while(getline(fp, temp))  
        {
            stringstream ss(temp);
            string w;
            StudentRecord ob;
            getline(ss,w,',');
            ob.set_studentName(w);
            getline(ss,w,',');
            ob.set_rollNumber(w);

            //if(!namepresent(ob.get_studentName()))
            students.push_back(ob);
        }
        fp.close(); 
    }

    //Creating Entities
    fp.open(file_path,ios::in); 

    if(fp.is_open()) 
    {
        string temp;
        while(getline(fp, temp)) 
        {
            stringstream ss(temp);
            string w;
            getline(ss,w,',');
            getline(ss,w,',');
            while(!ss.eof())
            {
                getline(ss,w,',');
                if(w.at(0)=='[')
                w=w.substr(1);
                
                if(w.at(w.length()-1)==']')
                w=w.substr(0,w.length()-1);
                
                LinkedList ob;
                ob.set_name(w);
                ob.set_iterator(nullptr);
                if(!entitypresent(ob.get_name()))
                EntityArray.push_back(ob);
            }
        }
        fp.close();
    }

    //adding Linked List
    for(size_t i=0;i<EntityArray.size();i++)
    {
        LinkedList newList;
        fp.open(file_path,ios::in); 
        if(fp.is_open())  
        {
            string temp;
            while(getline(fp, temp))  
            {
                stringstream ss(temp);
                string w;
                getline(ss,w,',');
                string name=w;
                getline(ss,w,',');
                string roll=w;
                
                int check=-1;
                for(size_t j=0;j<students.size();j++)
                {
                    if(students[j].get_rollNumber().compare(roll)==0 && students[j].get_studentName().compare(name)==0)
                    {
                        check=j;
                        break;
                    }
                }

                while(!ss.eof())
                {
                    getline(ss,w,',');
                    if(w.at(0)=='[')
                    w=w.substr(1);
                
                    if(w.at(w.length()-1)==']')
                    w=w.substr(0,w.length()-1);
                    string ent=w;

                    if(EntityArray[i].get_name().compare(ent)==0)
                    {
                        newList.add_student(students[check]);
                        break;
                    }
                }
            }
        }
        fp.close();
        newList.set_name(EntityArray[i].get_name());
        EntityArray[i]=newList;
    }
}