#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(const int argc, const char** argv)
{
	if(argc < 3){
		cerr << "Usage: " << argv[0] << " INPUT OUTPUT" << endl;
		return 0;
	}

	string input_file = argv[1];
	string output_file = argv[2];

	ifstream ifs(input_file.c_str());
	if(ifs.fail()){
		cerr << "Read file " << input_file << " error." << endl;
		return 0;
	}

	ofstream ofs(output_file.c_str());
	if(ofs.fail()){
		cerr << "Write file " << output_file << " error." << endl;
		return 0;
	}

	string line;
	// Read the first line
	getline(ifs, line, '\n');
	int events, users;
	stringstream sstr(line);
	sstr >> events >> users;
	ofs << events << " " << users << endl;

	// Read the following 2*users lines
	for(int i = 0; i < 2*users; i++){
		getline(ifs, line, '\n');
		stringstream sstr(line);
		double sum = 0.0, num;
		vector<double> numbers;
		while(sstr.good()){
			sstr >> num;
			numbers.push_back(num);
			sum += num;
		}
		for(int j = 0; j < numbers.size(); j++){
			if(j > 0){
				ofs << " ";
			}
			ofs << 1.0 * numbers[j] / sum;
		}
		ofs << endl;
	}

	while(getline(ifs, line, '\n')){
		ofs << line << endl;
	}

	ofs.close();
	ifs.close();
}

