#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <exception>
#include <sstream>
#include "Encrypt_Decrypt_with_key.cpp"
using namespace std;

struct Data {
protected: string name, id, addr;
		   string s_arr[4];
public:	 
		 void setname(string _name)
		 {
			 name = _name;			//sets name
		 }
		 void setid(string _id)
		 {
			 id = _id;			//sets id
		 }
		 void setaddr(string _addr)
		 {
			 addr = _addr;			//sets address
		 }
		 string getname()
		 {
			 return name;			//returns name
		 }
		 string getid()
		 {
			 return id;			//returns id
		 }
		 string getaddr()
		 {
			 return addr;			//returns address
		 }
		 void save_info(string ex_atttribute_1)
		 {
			 ofstream o;
			 o.open("storage_t.txt", ios::_Nocreate | ios::app);
			 string str = id + "~" + name + "~" + addr + "~" + ex_atttribute_1;		//saves the set info
			 cout << "\n Enter a Key to Encrypt : ";
			 string key;
			 cin >> key;
			 key_interpreter(key);
			 o << encryptor(str, key) << endl;
			 o.close();
		 }
		 void load_info()
		 {
			 ifstream o;
			 o.open("storage_t.txt", ios::_Nocreate);		//loades the requested data
			 string str;
			 string key;
			 cout << "\n Enter a Key to Decrypt : ";
			 cin >> key;
			 key_interpreter(key);
			 while (getline(o, str))
			 {
				 str = decryptor(str, key);
				 if (str[0] == ' ') str = str.substr(1, str.length() - 1);
				 if (str.substr(0, str.find_first_of('~')).compare(id) == 0)
				 {
					 stringstream X(str);
					 for (int i = 0; getline(X, s_arr[i], '~'); i++);
					 return;
				 }
			 }
			 cout << "\nNO MATCH FOUND FOR " + id + "....";
			 exit(0);
		 }
};
class Teacher:public Data{
private: string subject;
public:
void setsubject(string _subject)
{
	subject = _subject;		//sets subject
}
string getsubject()
{
	return subject;			//returns subject
}
void load_info()
{
	Data::load_info();
	id = s_arr[0];
	name = s_arr[1];		//loades information from the parent struct
	addr = s_arr[2];
	subject = s_arr[3];
}
};
class Valid_Length_Checker : public exception {			//raises an exception if the entered string overflows
public:
	string what() {
		return "String Limit Crossed!!";
	}
};
class Invalid_ID : public exception {			//raises an error if the entered Id is invalid
public: 
	string what() {
		return "Invalid ID Input!!";
	}
};
class Student : public Data {
private: string std;
public:
	void setstd(string _std)
	{
		std = _std;		//sets standard/grade of the student
	}
	string getstd()
	{
		return std;		//returns standard
	}
	void load_info()
	{
		Data::load_info();		//loades information from the parent struct
		id = s_arr[0];
		name = s_arr[1];
		addr = s_arr[2];
		std = s_arr[3];
	}
};
int main()
{
	int t;
	cout << " '0' -> Teacher. \n '1' -> Student. \n Choose the User : ";
	cin >> t;
	if (t==0)
	{
		string name, addr, id, subject;
		cout << "\n\n '0' -> Create NEW data for Teacher. \n '1' -> Access existing data for Teacher. \n Choose what to do : ";
		cin >> t;
		getchar();
		if (t == 0)
		{
			Teacher tinobj;
			try {
				cout << "\n Enter Name : ";
				getline(cin, name);
				if (name.length() > 25) throw Valid_Length_Checker();
				cout << "\n Enter Address : ";
				getline(cin, addr);
				if (addr.length() > 100) throw Valid_Length_Checker();
				cout << "\n Enter ID : ";
				getline(cin,id);
				if (id.length() > 5) throw Valid_Length_Checker();
				cout << "\n Enter Subject : ";
				getline(cin, subject);
				if (subject.length() > 20) throw Valid_Length_Checker();
			}
			catch (Valid_Length_Checker e)
			{
				cout << e.what();
				exit(0);
			}
			tinobj.setname(name);
			tinobj.setaddr(addr);
			tinobj.setid(id);
			tinobj.setsubject(subject);
			tinobj.save_info(subject);
			cout << "\n !!!Data Saved sucessfully!!!";
		}
		else {
			Teacher toutobj;
			try {
				cout << "\n ID : ";
				cin >> id;
				if (id.length() > 5) throw Valid_Length_Checker();
			}
			catch (Valid_Length_Checker e)
			{
				cout << e.what();
				exit(0);
			}
			toutobj.setid(id);
			toutobj.load_info();
			cout << " Name : " << toutobj.getname() << endl << " Address : " << toutobj.getaddr() << endl << " Subject : " << toutobj.getsubject() << endl;
		}
	}
}
