#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct person  //creates object for person
{
	public:
		int SSN;
		int bday;
		string fn;
		string ln;
		int zip;

		person(int ssn, int bd, string f_name, string l_name, int zc) //constructor
		{
			SSN = ssn;
			bday = bd;
			fn = f_name;
			ln = l_name;
			zip = zc;
		} 
};
 
struct Link  //creates link 
{ 
	person * data;
	Link * next;

	Link(person * d = NULL, Link * n = NULL)
	{
		data = d;
		next = n;
	}

};

void print_list(Link * content)
{ 
	while (content != NULL)
	{
		cout << content->data->SSN <<" "<< content->data->bday<<" "<< content->data->fn<<" "<< content->data->ln<< " "<<content->data->zip<<endl;
		content = content->next; 
	}
}

person * find(Link * content, string f, string l)
{
	while(content != NULL)
	{
		if(content->data->fn == f && content->data->ln == l)
			return content->data;
		
		content = content->next;	
	}
	return NULL;
}

void find_all(Link * content, string s)
{
	while(content != NULL)
	{
		if(content->data->ln == s)
			cout << content->data->SSN <<" "<< content->data->bday<<" "<< content->data->fn<<" "<< content->data->ln<< " "<<content->data->zip<<endl;	
		content = content->next;
	}
}

void find_zip(Link * content, int a)
{
	Link * allzip = NULL;
	while(content != NULL)
	{
		if(content->data->zip == a)
			allzip=new Link(content->data, allzip);	
		content = content->next;
	}
	print_list(allzip);
}

int find_oldest(Link * content)
{	
	int oldest = content->data->bday;

	while(content!=NULL)
	{	
		if(content->data->bday < oldest)
			oldest=content->data->bday;
		content=content->next;
	}
	return oldest;

}

int read_file()
{
	ifstream fin;
	fin.open("/home/218/database.txt");
	 
	int ssn, bd;
	string fn, ln;
	int zip;

	Link * content = NULL;
	
	if (fin.fail())
	{
		cout << "Couldn't open the file\n";
        	exit(1);
    	}

   	else
   	{
		int i=0;
        	while(i<10000)
	        {
			if(fin.fail())
			{
				cout<<"Could not open file."<<endl;
				break;
            		}

			fin >> ssn >> bd >> fn >> ln >> zip;
			
			content = new Link(new person(ssn, bd, fn, ln, zip), content);
			
			//print_list(content);

			i++;

        	}
        }
        fin.close();
	Link * all = NULL;
	while(true)
	{
		cout<<"Type command: "<<endl<<"Find - display all information on said person"<<endl<<"All - display the information on all person with given last name"<<endl<<"Zip - makes a new linked list of people with this zipcode and displays them"<<endl<<"Oldest - displays the name and zipcode of the oldest person" <<endl<<"Exit - exit out of loop"<<endl; 
		cout<<endl<<"-----------------------------------------------"<< endl;
		string command;
		cin>>command;
		
		if(command=="Find")
		{
			cout<<"Who would you like to find? Enter first name."<<endl;
			string first, last;
			cin>>first;
			cout<<"Enter last name."<<endl;
			cin>>last;
			
			person * p = find(content, first, last);
			
			if(p==NULL)
				cout<<"Person could not be found."<<endl;
			else
				all = new Link(p, all); 	
			print_list(all); 
		
		}
		if(command=="Exit")
			break;	

		if(command=="All")
		{
			cout<<"Enter person's last name."<<endl;
			string ln;
			cin>>ln;

			find_all(content, ln);

		}

		if(command=="Zip")
		{
			cout<<"Enter desired zip code."<<endl;
			int zc;
			cin>>zc;

			find_zip(content, zc);
			
		}

		if(command=="Oldest")
		{
			int oldest=find_oldest(content);
			
			while(content!=NULL)
			{
				if(content->data->bday==oldest)
					cout<<"The oldest person is "<<  content->data->fn <<" "<<content->data->ln<< " "<< content->data->zip<<endl;
				content=content->next;
			}
		}
		cout<<"-----------------------------------------------"<<endl;

	
	}
        return 0;
}

int main()
{
	read_file();
	return 0;
}
