#include <iostream>
#include <iterator> 
#include <map> 
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream>

using namespace std;
const int NUMOFTRAITS = 55;

// Real Filepath /public/coen320/Driving Data(KIA SOUL)_(150728-160714)_(10 Drivers_A-J)
map<string, int> read_csv(string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    map<string, int> result;

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
		int i=0;

        // Extract each column name
        while(getline(ss, colname, ',')){
            names[i] = (colname);
			i++;
        }
		getline(myFile, line2);
		stringstream new_ss(line2);
		i=0;

		while(getline(new_ss, colname, ',')){
            val[i] = (colname);
			i++;
        }

		/*while(strsr >> hold){
			cout<<hold<<endl;
			val[i] = hold;
			result.insert(pair<string, int>(names[i], val[i]));
            
			//if(ss.peek() == ',') ss.ignore();
            
            // Increment the column index
            i++;
        }*/

		// Add the current column's values map
		for(int i = 0; i<NUMOFTRAITS; i++){
			try{
				result.insert(pair<string, int>(names[i], stoi(val[i])));
			}
			catch(invalid_argument){
				cout<<"Error"<<endl;
			}
			
		}
	}

    // Close file
    myFile.close();

    return result;
}
int main (int argc, char *argv[]) {
	map<string,int> dictionary;
	for(int i =0; i<1; i++){
		dictionary = read_csv("Driving Data(KIA SOUL)_(150728-160714)_(10 Drivers_A-J).csv");
		map<string, int>::iterator itr; 
		cout << "\nThe map is : \n"; 
		cout << "\tKEY\tELEMENT\n"; 
		for (itr = dictionary.begin(); itr != dictionary.end(); ++itr) { 
			cout << '\t' << itr->first 
				<< '\t' << itr->second << '\n'; 
		} 
		cout << endl; 
	}

	return 0;
}