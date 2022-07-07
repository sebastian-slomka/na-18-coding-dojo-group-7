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

class CustomException : public std::exception {
    public:
        const char* what() {
            return "There was a problem during creation a class";
        }
};

class SSHDConfig
{
public:
//constructors
SSHDConfig(const std::string &path)
{
	std::ifstream inputfile(path);

	if(!inputfile.is_open())
	{
		throw CustomException();
	}

	std::string word1;
	std::string word2;

	/*while(getline(inputfile,line)){

		 std::string s1;
		 std::string s2;

	}*/
	int it=0;
	while(inputfile >> word1 >> word2){
			ssh_map.insert({word1,word2});
	}

	for(auto &element: ssh_map)
	{
		std::cout << element.first << " " << element.second << std::endl;
	}

}

//methods
//getters

//setters


private:
std::string m_path;
std::map<std::string,std::string> ssh_map;

};

int main() {

TEST(When_CreatedNewClass_Expect_Object_Exists) {
	
	std::unique_ptr<SSHDConfig> sshdconfigTested = std::make_unique<SSHDConfig>("/home/ziomek/na-18-coding-dojo-group-7/src/sshd_config");

	EXPECT(sshdconfigTested != nullptr);
};

}
