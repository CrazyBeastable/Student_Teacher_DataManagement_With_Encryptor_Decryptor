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
			 name = _name;
		 }
		 void setid(string _id)
		 {
			 id = _id;
		 }
		 void setaddr(string _addr)
		 {
			 addr = _addr;
		 }
		 string getname()
		 {
			 return name;
		 }
		 string getid()
		 {
			 return id;
		 }
		 string getaddr()
		 {
			 return addr;
		 }
		 void save_info(string ex_atttribute_1)
		 {
			 ofstream o;
			 o.open("storage_t.txt", ios::_Nocreate | ios::app);
			 string str = id + "~" + name + "~" + addr + "~" + ex_atttribute_1;
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
			 o.open("storage_t.txt", ios::_Nocreate);
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
	subject = _subject;
}
string getsubject()
{
	return subject;
}
void load_info()
{
	Data::load_info();
	id = s_arr[0];
	name = s_arr[1];
	addr = s_arr[2];
	subject = s_arr[3];
}
};
class Valid_Length_Checker : public exception {
public:
	string what() {
		return "String Limit Crossed!!";
	}
};
class Invalid_ID : public exception {
public: 
	string what()
	{
		return "Invalid ID Input!!";
	}
};
class Student : public Data {
private: string std;
public:
	void setstd(string _std)
	{
		std = _std;
	}
	string getstd()
	{
		return std;
	}
	void load_info()
	{
		Data::load_info();
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