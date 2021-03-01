
#include "../includes/fileio.h"
#include "../includes/utilities.h"
#include <vector>
#include <algorithm>

using namespace std;
using namespace constants;

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,std::ios_base::openmode mode){
	myfile.open(myFileName,mode);
	if (myfile.is_open()){
		return true;
	}
	else{
		return false;
	}

}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){
	myfile.close();
}

/* serializes all content in entries to file outputfilename
 * check out utils for helpful type conversion functions
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writetoFile(std::vector<constants::entry>  &entries, const std::string &outputfilename){
	std::ofstream wfile;
	std::string num;
	wfile.open(outputfilename,std::ios_base::out);
	if (!wfile.is_open()){
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	if (entries.size() ==0){
		return constants::FAIL_NO_ARRAY_DATA;
	}
	for (constants::entry i:entries){
		num = intToString(i.number_occurences);
		num = i.word + " " + num + "\n";
		//wfile.write(num,100);
		wfile << num;
	}
	return constants::SUCCESS;
}
