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
#include <vector>
#include <fstream>

class Sshd_configWraper
{
public:

void dataFrom_shd_config()
{
	//std::ifstream sshd_config_data("sshd_config");

	std::ifstream sshd_config_data;
	sshd_config_data.open("/home/acad/projects/CodingDojo2/na-18-coding-dojo-group-7/src/sshd_config");

	if(!sshd_config_data.is_open())
	{
		std::cerr << "Fille cannot be loaded" << std::endl;
	}

	sshd_config_data.close();



}

private:


};



int main() {

	TEST(ObjectCreated)
	{
		EXPECT(false);
	};

	TEST(MethodThatIsOpeningAndLoadingAFile)
	{
		Sshd_configWraper ssdconfigwraper;
		ssdconfigwraper.dataFrom_shd_config();
		EXPECT(false);
	};

}
