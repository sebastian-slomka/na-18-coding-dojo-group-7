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
SSHDConfig(std::string path)
{
	// if (path != "")
	// {

	// }

}

//methods
//getters

//setters


private:
std::string m_path;

};

int main() {

TEST(When_CreatedNewClass_Expect_PathIsEmpty) {
	
	std::unique_ptr<SSHDConfig> sshdconfigTested = std::make_unique<SSHDConfig>("");

	EXPECT(sshdconfigTested != nullptr);
};

}
