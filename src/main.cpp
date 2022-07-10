/***
 * Dummy testing framework
 *
 * Example usage:
 * 	TEST(some_test_name) {
 * 		EXPECT(true == true);
 * 	}
 */

#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <array>
#include <utility>

struct TestCase { std::string name{}; std::ostringstream failures{}; };
template <typename T> void operator | (TestCase& testCase, T&& testBody) {
	    testBody(); auto failures = testCase.failures.str();
	        if (failures.empty()) std::cout << testCase.name << ": SUCCESS\n";
		    else std::cerr << testCase.name << ": FAILURE\n" << failures;
}
void addFailure(std::ostream& os, const char* file, unsigned line, const char* condition) {
	    os << file << ":" << line << ": Failed: " << condition << "\n";
}
#define TEST(name) TestCase name{#name}; name | [&, &failures = name.failures]
#define EXPECT(cond) if (cond) {} else addFailure(failures, __FILE__, __LINE__, #cond)
#define ASSERT(cond) if (cond) {} else return addFailure(failures, __FILE__, __LINE__, #cond)

/*******************************************************************************************/
#include <memory>
#include <fstream>
#include <map>
#include <cstdlib>
#include <algorithm>

class CustomExecpetion: public std::exception
{
	public:
	const char * what ()
	{
		return "there was a problem during creation of objec of class SSHDConfig";
	}
};



class SSHDConfig
{
public:

SSHDConfig (std::string const& path) 
{
	std::fstream my_file;
	my_file.open(path, std::ios::in);
	std::string key, value;

	configFileValidator(my_file);

	my_file.close();
	my_file.open(path, std::ios::in);

	while(my_file >> key >> value){
		data.insert({key, value});
		//std:: cout << key << " " << value << std::endl;
	}


}

void setPort (std::string key, std::string value)
{	
	data[key] = value;
	//std:: cout << key << " " << value << std::endl;
}

void addLine (std::string key, std::string value)
{
	data.insert ({key, value});
}

void saveFile (std::string const& path)
{
	std::string key, value;
	std::fstream my_copy;
	my_copy.open(path, std::ios::out);

	for (auto[key, value]: data)
	{
		my_copy<< key << " " << value << std::endl;
	}
	my_copy.close();

}

std::string getValue (std::string key)
{
	return data[key];
}


private:
	std::map<std::string, std::string> data;

	void configFileValidator(std::fstream &my_file){
		std::string line;
		while(std::getline(my_file, line)){

		auto it = std::unique(line.begin(), line.end(), [](char const &lhs, char const &rhs) {
			return (lhs == rhs) && (lhs == ' ');
		});
		line.erase(it, line.end());

		auto last_char = line.back();
		if(last_char == ' ')
			line.pop_back();

		int count = std::count_if(line.begin(), line.end(), [](char space){
			return space==' ';
		});
		
		if(count > 1)
			throw CustomExecpetion();
		
	}
	}
};


int main() {

	TEST (ReturnTrueIfNewConfigFileCreated)
	{
		auto pointer = std::make_unique <SSHDConfig> ("/home/konrad/PHASE_3/DOJO/na-18-coding-dojo-group-7/data/sshd_config");
		pointer->saveFile("/home/konrad/PHASE_3/DOJO/na-18-coding-dojo-group-7/data/sshd_config(copy)");
		auto pointer2 = std::make_unique <SSHDConfig> ("/home/konrad/PHASE_3/DOJO/na-18-coding-dojo-group-7/data/sshd_config(copy)");
		EXPECT(pointer2->getValue("Port")=="22");
	};

	TEST (ReturnTrueIfNewElementIsInserted)
	{
		auto pointer = std::make_unique <SSHDConfig> ("/home/konrad/PHASE_3/DOJO/na-18-coding-dojo-group-7/data/sshd_config");
		pointer->addLine("tego", "typu");
		EXPECT(pointer->getValue("tego")=="typu");
	};

	TEST (ReturnTrueIfSetPortWorks)
	{
		auto pointer = std::make_unique <SSHDConfig> ("/home/konrad/PHASE_3/DOJO/na-18-coding-dojo-group-7/data/sshd_config");
		pointer->setPort("Port", "25");
		EXPECT(pointer->getValue("Port")=="25");
	};

	TEST(ReturIfFileIsOpen) 
	{
		//home/acad/na-18-coding-dojo-group-7/data/sshd_config
		//home/konrad/PHASE_3/DOJO/na-18-coding-dojo-group-7/data/sshd_config
		//home/acad/na-18-coding-dojo-group-7/data/sshd_config
		try{
			auto pointer = std::make_unique <SSHDConfig> ("/home/konrad/PHASE_3/DOJO/na-18-coding-dojo-group-7/data/sshd_config");
			EXPECT(pointer != nullptr);
		}catch(CustomExecpetion e)
		{
			std::cerr << e.what() << '\n';
			EXPECT(false);
		};
 	};

	TEST(ReturnTrueIfObjectExists) 
	{
		auto pointer = std::make_unique <SSHDConfig> ("");
 		EXPECT(pointer != nullptr);
 	};

	

}
