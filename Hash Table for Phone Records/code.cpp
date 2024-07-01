#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>

using namespace std;

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    //function to return summation
    long long returnSum(const string& str)
    {
        int l=str.length();
        int x=263;
        long long p=1000000007LL,sum=0LL;

        for(int i=0;i<l;i++)
        {
            char ch=str.at(i);
            int ascii=(int)ch;
            sum=sum+(ascii*(long long)pow(x,i))%p;
        }

        return sum;
    }

    // Add your own implementation for hashing
    long long computeHash(const string& str)
    {
        long long sum=returnSum(str);
        return sum%HASH_TABLE_SIZE;
    }

    // Add your own implementation for adding a contact
    void addContact(const PhoneRecord* record)
    {
        string name=record->getName();
        stringstream ss(name);
        string word;

        while(!ss.eof())
        {
            getline(ss,word,' ');
            int key=(int)computeHash(word);
            HashTableRecord* ob=new HashTableRecord(key, const_cast<PhoneRecord*>(record));
            if(hashTable[key]==nullptr)
            {
                hashTable[key]=ob;
                hashTable[key]->setNext(nullptr);
            }
            else
            {
                HashTableRecord* temp=hashTable[key];
                hashTable[key]=ob;
                hashTable[key]->setNext(temp);
            }
        }
    }

    // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName)
    {
        vector<PhoneRecord*> contacts=fetchContacts(searchName);
        PhoneRecord* first=contacts[0];
        stringstream ss(first->getName());
        string word="";
        int f=0;
        while(!ss.eof())
        {
            getline(ss,word,' ');
            int key=(int)computeHash(word);
            HashTableRecord *ptr=hashTable[key];
            HashTableRecord *prev=nullptr;
            
            while(ptr!=nullptr)
            {
                if(ptr->getRecord()==first)
                {
                    if(ptr==hashTable[key])
                    {
                        hashTable[key]=ptr->getNext();
                        ptr=nullptr;
                        ++f;
                    }
                    else
                    {
                        prev->setNext(ptr->getNext());
                        ptr=nullptr;
                        ++f;
                    }
                    break;
                }
                prev=ptr;
                ptr=ptr->getNext();
            }
        }
        if(f==0)
        return false;
        return true;

    }



    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query)
    {
        vector<PhoneRecord*> prec;
        string name=*query;
        stringstream ss(name);
        string word="";
        while(!ss.eof())
        {
            getline(ss,word,' ');
            int key=(int)computeHash(word);
            
            HashTableRecord* ptr=hashTable[key];
            
            while(ptr!=nullptr)
            {
                
                if(ptr->getRecord()->getName().find(word)!=string::npos)
                prec.push_back(ptr->getRecord());
                
                ptr=ptr->getNext();
            }
            
        }

        vector<int> freq;
        vector<PhoneRecord*> unique;
        for(int i=0;i<prec.size();i++)
        {
            int s=0,f=0;
            for(int j=0;j<unique.size();j++)
            {
                if(prec[i]==unique[j])
                {
                    f=1;
                    break;
                }
            }

            if(f==1)
            break;

            for(int j=i;j<prec.size();j++)
            {
                if(prec[i]==prec[j])
                ++s;
            }
            freq.push_back(s);
            unique.push_back(prec[i]);
        }

        int l=freq.size();
        for(int i=0;i<l-1;i++)
        {
            for(int j=0;j<l-1-i;j++)
            {
                if(freq[j]<freq[j+1])
                {
                    int t=freq[j];
                    freq[j]=freq[j+1];
                    freq[j+1]=t;

                    PhoneRecord* temp=unique[j];
                    unique[j]=unique[j+1];
                    unique[j+1]=temp;
                }
            }
        }

        return unique;
    }

    // Add your own implementation for counting records pointing to a contact
    //int countRecordsPointingTo(const PhoneRecord* record) const;

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& filename)
    {
        fstream fp;
        fp.open(filename,ios::in); 

        if(fp.is_open())  
        {
            string temp;
            vector<string> details;
            vector<string> phNum;
            
            while(getline(fp, temp))  
            {
                stringstream ss(temp);
                string word;
                while(!ss.eof())
                {
                    getline(ss,word,',');
                    details.push_back(word);
                }

                int l=details.size();
                
                string fname=details[0], org=details[l-1];

                for(int i=1;i<l-1;i++)
                phNum.push_back(details[i]);

                PhoneRecord* pr=new PhoneRecord(fname,org,phNum);
                
                addContact(pr);
                details.clear();
                phNum.clear();   
            }
            fp.close();    
        }
    }

    /*void display()
    {
        for(int i=0;i<HASH_TABLE_SIZE;i++)
        {
            HashTableRecord* ptr=hashTable[i];
            if(ptr!=nullptr)
            {
                cout << ptr->getKey() << endl;
                while(ptr!=nullptr)
                {
                    cout << ptr->getRecord()->getName() << "\n" << ptr->getRecord()->getOrganisation() << endl;
                    vector<string> ph=ptr->getRecord()->getPhoneNumbers();
                    for(int j=0;j<ph.size();j++)
                    cout << ph[j] << "\t";

                    cout << "\n\n";
                    ptr=ptr->getNext();
                }
            }
        }
    }*/
            
    //Destructor
    ~PhoneBook()
    {
        for(int i=0;i<HASH_TABLE_SIZE;i++) 
        {
            HashTableRecord* ptr=hashTable[i];
            while(ptr!=nullptr)
            {
                HashTableRecord* temp=ptr;
                ptr=ptr->getNext();
                delete temp;
            }
        }
    }
};