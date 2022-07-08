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
	std::string line, value;

	while(std::getline(my_file, line)){
		// int position = line.find(" ");
		// std::cout << line.substr(0, position) << std::endl;
		int count = std::count_if(line.begin(), line.end(), [](char space){return space==' ';});
		std::cout << count << std::endl;

		//data.insert({key, value});
	}
	// for(auto[key, value] : data){
	// 	std::cout << key << " " << value << std::endl;
	// }
	//if (my_file.is_open()==false)
	//{	
		//throw CustomExecpetion();
	//}
}
private:
	std::map<std::string, std::string> data;
};


int main() {

	TEST(ReturIfFileIsOpen) 
	{
		auto pointer = std::make_unique <SSHDConfig> ("/home/acad/na-18-coding-dojo-group-7/data/sshd_config");

 		EXPECT(pointer != nullptr);
 	};

	/*TEST(ReturIfFileIsOpen)
	//{
		try
		{
			auto pointer = std::make_unique <SSHDConfig> ("/home/acad/na-18-coding-dojo-group-7/data/sshd_config");
			//EXPECT(true);
		}
		catch(CustomExecpetion e)
		{
			std::cerr << e.what() << '\n';
			//EXPECT(false);
		}
	//};*/


	TEST(ReturnTrueIfObjectExists) 
	{
		auto pointer = std::make_unique <SSHDConfig> ("");
 		EXPECT(pointer != nullptr);
 	};

	

}
