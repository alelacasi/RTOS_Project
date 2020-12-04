#include <iostream>
#include <map> 
#include <string>
#include <fstream>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream>
#include <thread>
using namespace std;

const int NUMOFTRAITS = 55;

// Real Filepath /public/coen320/Driving Data(KIA SOUL)_(150728-160714)_(10 Drivers_A-J).csv
map<string, string> read_csv(string filename){
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    map<string, string> result;

    // Create an input filestream
    ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line,line2, colname,colval;
	string names[NUMOFTRAITS];
	string val[NUMOFTRAITS];


    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);

        // Create a stringstream from line
        stringstream ss(line);
		int count=0;

        // Extract each column name
        while(getline(ss, colname, ',')){
            names[count] = (colname);
			//cout<<names[count]<<endl;
			count++;
        }
		//cout<<endl;
		getline(myFile, line2);
		stringstream new_ss(line2);
		count=0;

		while(getline(new_ss, colname, ',')){
            val[count] = (colname);
			//cout<<val[count]<<endl;
			count++;
        }

		// Add the current column's values map
		for(int i = 0; i<NUMOFTRAITS; i++){
			cout<<names[i]<<"\t"<< val[i]<<endl;
			result.insert(pair<string, string>(names[i], val[i]));
		}
	}
    // Close file
    myFile.close();
    return result;
}

// A Thread function 
void foo(int Z) 
{ 
    for (int i = 0; i < Z; i++) { 
        cout << "Thread using function "<<i<<
               " pointer as callable\n"; 
    } 
} 

int main (int argc, char *argv[]) {
	map<string,string> dictionary;
	for(int i =0; i<1; i++){
		dictionary = read_csv("Driving Data(KIA SOUL)_(150728-160714)_(10 Drivers_A-J).csv"); 
	}
	cout << "Threads 1 and 2 "
         "operating independently" << endl; 
  
    // This thread is launched by using  
    // function pointer as callable 
    //thread th1(foo(3)); 
  
    // This thread is launched by using 
    // function object as callable 
    //thread th2(foo(3)); 
  
    // Wait for the threads to finish 
    // Wait for thread t1 to finish 
    //th1.join(); 
  
    // Wait for thread t2 to finish 
    //th2.join(); 
  
    // Wait for thread t3 to finish 
    //th3.join(); 

	return 0;
}