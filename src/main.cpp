#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <array>
#include <utility>
#include <memory> 
#include <map>
#include <iterator>

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
		SSHDConfig(const std::string& data) : inputData(data)
		{

		}

		std::map<std::string, std::string> ParseInput()
		{
			std::map<std::string, std::string> map;
			std::string temp;

			int counter = 0; 
			std::array<std::string, 2> tmpArray; 

			std::stringstream is(input); 
			while(std::getline(is, temp, ' ')){

				if(temp != "")
					tmpArray[counter] = temp; 

				if (counter == 1)
					{
						std::cout << tmpArray.at(0) << " " << tmpArray.at(1); 
						map.insert({tmpArray.at(0),tmpArray.at(1)}); 
						counter = 0; 
					}
				else{
					counter++; 
				}
				
				


				 // map.insert(std::pair<std::string, std::string>(is, temp)); 
		
			}

			return map;
		}

	private:
		std::string inputData; 

}; 

int main()
{

	TEST(ConstractSHHDConfigWithStringParameter)
	{
		const std::string testString = "";

		std::unique_ptr<SSHDConfig> ptr = std::make_unique<SSHDConfig>(testString); 

		EXPECT(ptr != nullptr); 

	}; 

	TEST(ParsingTest)
	{
		std::unique_ptr<SSHDConfig> ptr = std::make_unique<SSHDConfig>(input); 

		std::map<std::string, std::string> map = {{"Port", "22"}, {"", ""}, {"LoginGraceTime", "2m"}, 
													{"#PermitRootLogin", "prohibit-password"}, {"#StrictModes", "yes"}, {"MaxAuthTries", "6"},
													{"MaxSessions", "10"}, {"ParsingTest:", "FAILURE"}
													};

		EXPECT(map == ptr->ParseInput());

	};

}