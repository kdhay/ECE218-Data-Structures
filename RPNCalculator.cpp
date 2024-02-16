#include<string>
#include<iostream>
#include<vector>

using namespace std;


struct memory
{
	vector<string>varnames;
	vector<int>values;
	

	bool isdefined(string varname)
	{	for(int i=0; i<varnames.size(); i++)
		{	
			if(varnames[i]==varname)
				return true;
			
			else
				return false;
		}

	}
	void set(string varname, int val)
	{	if(isdefined(varname))
		{	for(int i=0; i<varnames.size(); i++)
			{	if(varname==varnames[i])
					values[i]=val;
			}	
		}
		else 
		{	varnames.push_back(varname);
			values.push_back(val);
		}
				
	}
	int getval(string varname)
	{	for(int i=0; i<varnames.size(); i++)
		{
			if(varname==varnames[i])
				return values[i];

			else
			{	
				cout<<"Value does not exist."<<endl;
				return 0; 
			}
		}
	
	}
	void print()
	{	
		for(int i=0; i<varnames.size(); i++)
		{
			cout<<varnames[i]<<endl<<"---"<<values[i]<<endl;
		}

	}

};

bool look_like_int(string s)
{	
	for(int i=0; i<s.length(); i++)
	{
		if(s[i]<'0'||s[i]>'9')
			return false;
		return true;
	}
}

bool looks_like_Op(string p)
{
	string Ops[]={"+", "-", "*", "/"};
	
	if(p==Ops[0]||p==Ops[1]||p==Ops[2]||p==Ops[3])
		return true;
	else
		return false;
}

int result(string val, int a, int b)
{
	if(val=="+")
		return a+b;

	else if(val=="-")
		return a-b;

	else if(val=="*")
		return a*b;

	else if(val=="/")
		return a/b;
	
}

int main()
{
	vector<int>calcstack;
	memory V;
	int Result;

	cout<< "Welcome to the RPN Calculator. Please begin."<<endl;

	while(true)
	{
		string input;
		int size= calcstack.size();
			

		cin>>input;

		//cout<<"-----------------------------------"<<endl;


		if(look_like_int(input))
		
			calcstack.push_back(stoi(input));
		
		else if(looks_like_Op(input))
		{
			int last=calcstack[size-1];
			calcstack.pop_back();
			
			int first=calcstack[size-2];
			calcstack.pop_back();
			

			//cout<<"first= "<<first<<endl;
			//cout<<"last="<<last<<endl;

			Result=result(input, first, last);
			calcstack.push_back(Result);
		}	
		else if(input == "=")
		{	string s;
			cin>>s;
			V.set(s, calcstack.back());
			cout<<"The value of "<< s << " has been set to "<< calcstack.back()<<endl; 
		}
	
		else if (input=="end")			
		{
			
			cout<<"The end result is: "<< calcstack[size-1]<<endl;
			calcstack.clear();
			cout<<"STARTING NEW CALCULATION...."<<endl;
		}
		else if (input=="stop")
			break;
		
		else
		{	if(V.isdefined(input))
			{	int x=V.getval(input);
				calcstack.push_back(x);
			}
		}		 

		//for(int i=0; i<calcstack.size(); i++)
		//	cout<< calcstack[i] << endl;

	}
}
