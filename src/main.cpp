#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <array>
#include <utility>
#include <memory> 
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


const std::string input =
"Port 22\n"\
"\n"\
"LoginGraceTime 2m\n"\
"#PermitRootLogin prohibit-password\n"\
"#StrictModes yes\n"\
"MaxAuthTries 6\n"\
"MaxSessions 10\n";


class SSHDConfig
{
	public:
		SSHDConfig(const std::string& name) : local_variable(name)
		{

		}
		


	
	private:
		std::string local_variable; 



}; 





int main()
{






TEST(stringTest)
{

std::unique_ptr<SSHDConfig> ptr = std::make_unique<SSHDConfig>(""); 

// SSHDConfig sshdconfig; 

	EXPECT(ptr != nullptr); 



}; 





}