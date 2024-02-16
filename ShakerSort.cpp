#include <iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<sys/resource.h>

using namespace std;

struct people
{
	int SSN;
	int day, month, year;
	string FN, LN;
	double BB;
};

people data[1000];


double get_cpu_time()
{ 
	struct rusage ruse;
  	getrusage(RUSAGE_SELF, &ruse);
	return ruse.ru_utime.tv_sec + 
ruse.ru_utime.tv_usec / 1000000.0 + ruse.ru_stime.tv_sec + ruse.ru_stime.tv_usec / 1000000.0; 
}

int read_file()
{	
	ifstream fin;
	fin.open("/home/118/database1.txt");

	int S, D, M, Y;
	string F, L;
	double B;
	
	if(fin.fail())
	{	
		cout<<"Could not open file."<<endl;
		exit(1);
	}
	else
	{
		int i=0;
		while(true)
		{
			if(fin.eof())
				break;
			

			fin>>S>>D>>M>>Y>>F>>L>>B;
			data[i].SSN = S;
			data[i].day = D;
			data[i].month = M;
			data[i].year = Y;
			data[i].FN = F;
			data[i].LN = L;
			data[i].BB = B;
	
			i++;
			
		}
	}
	fin.close();
	return 0;
}

	


void shaker_sort(int size)
{ 
  	for(int i=0; i<size; i++)
	{
		bool swap = false;
		
		for(int j = i ; j<size; j++)
		{
			if(data[j].FN  > data[j+1].FN)
			{ 	
				people temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
				
				swap = true;
			}
			
			else if(data[j].FN == data[j+1].FN)
			{
				if(data[j].LN > data[j+1].LN)
				{
					people temp = data[j];
					data[j] = data[j+1];
					data[j+1] = temp;
					
					swap = true;
					
				}
			}
		}
		
		for(int j = size; j>i; j--)
		{
			if(data[j].FN < data[j-1].FN)
			{
				people temp = data[j];
				data[j] = data[j-1];
				data[j-1] = temp;
				
				swap = true;					
			}

			else if(data[j].FN == data[j-1].FN)
			{
				if(data[j].LN < data[j-1].LN)
				{
					people temp = data[j];
					data[j] = data[j+1];
					data[j+1] = temp;
					
					swap = true;
					
				}
			}

		}
		
		if(!swap)
			break;
					
	}
}


void store_in_file(int size)
{
        ofstream myfile;
        myfile.open("SortedFile-Lab2");

        if(!myfile)
        {	
	        cout<<"Unable to open file";
		return;
	}
        while(!myfile.eof())
        {
                for(int i=0;i<size;i++)
                {
                        myfile << data[i].SSN << " " << data[i].day << " ";
                        myfile << data[i].month << " " << data[i].year << " ";
                        myfile << data[i].FN << " " << data[i].LN << " ";
                        myfile << data[i].BB << " " << endl;
                }
                myfile.close();
                break;
        }
}

/*
void result(int size)
{
        shaker_sort(size);

        for(int i=0;i<size;i++)
        {
                cout << data[i].SSN << " ";
                cout << data[i].day << " ";
                cout << data[i].month << " ";
                cout << data[i].year << " ";
                cout << data[i].FN << " ";
                cout << data[i].LN << " ";
                cout << data[i].BB << " ";
                cout << endl;
        }
}
*/

int main()
{
	int size = 1000; 

	read_file();
	cout<< "File was read."<< endl;

	double t1 = get_cpu_time();
	shaker_sort(size);
	double t2 = get_cpu_time();

	//result(size);
	cout << "It took " << t2-t1 << " seconds to sort this data. " << endl;
	
	return 0;
}
 
