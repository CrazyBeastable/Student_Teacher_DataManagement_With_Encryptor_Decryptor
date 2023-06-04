#include<iostream>
#include<string>
#include<fstream>
using namespace std;
void key_interpreter(string& key)
{
	while (key.length() < 5) key += " ";
	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] >= 32 && key[i] <= 63)
		{
			key[i] = 32 + int(key[i]);
		}
	}
}
string encryptor(string nrml, string key)
{
	while (nrml.length() % 3 != 0) nrml = " " + nrml;
	int num = 0;
	for (int i = 0; i < key.length(); i++) num += int(key[i]);
	int n1 = num / 100;
	int n2 = (num % 100) / 10;
	int n3 = num % 10;
	for (int i = 0; i < nrml.length(); i += 3)
	{
		nrml[i] = char(n3 + int(nrml[i]));
		nrml[i + 1] = char(n1 + int(nrml[i + 1]));
		nrml[i + 2] = char(n2 + int(nrml[i + 2]));
	}
	return nrml;
}
string decryptor(string nrml, string key)
{
	int num = 0;
	for (int i = 0; i < key.length(); i++) num += int(key[i]);
	int n1 = num / 100;
	int n2 = (num % 100) / 10;
	int n3 = num % 10;
	for (int i = 0; i < nrml.length(); i += 3)
	{
		nrml[i] = char(int(nrml[i]) - n3);
		nrml[i + 1] = char(int(nrml[i+1]) - n1);
		nrml[i + 2] = char(int(nrml[i+2]) - n2);
	}
	return nrml;
}