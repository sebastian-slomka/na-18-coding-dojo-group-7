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
	//if (my_file.is_open()==false)
	//{	
		//throw CustomExecpetion();
	//}
}
private:
};


int main() {

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
