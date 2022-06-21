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
#include <cstdlib>
#include <map>

const std::string input =
"Port 22\n"\
"\n"\
"LoginGraceTime 2m\n"\
"#PermitRootLogin prohibit-password\n"\
"#StrictModes yes\n"\
"MaxAuthTries 6\n"\
"MaxSessions 10\n";

class Sshd_configWraper
{
public:

void dataFrom_shd_config()
{
	//std::ifstream sshd_config_data("sshd_config");

	std::ifstream sshd_config_data;
	sshd_config_data.open("/home/acad/projects/CodingDojo2/na-18-coding-dojo-group-7/src/sshd_config");

	// if(!sshd_config_data.is_open())
	// {
	// 	std::cerr << "Fille cannot be loaded" << std::endl;
	// }

	std::string str;
	std::vector<std::string> vecOfStrs;
	std::stringstream s(input);
	std::map<std::string, std::string> dojoMap;
	while (std::getline(s, str))
	{
		vecOfStrs.push_back(str);
	}
	
	
	for(auto const& line : vecOfStrs)
	{
		
		std::stringstream ssteam(line);
		std::string tempWord;
		std::vector <std::string> tempVec;
		// std::cout << line << std::endl;
		while(std::getline(ssteam,tempWord, ' '))
		{
			std::cout << tempWord << std::endl;
		    tempVec.push_back(tempWord);
		}

		try 
		{
			dojoMap.insert({tempVec.at(0),tempVec.at(1)});
		}
		catch(const std::out_of_range& e)
		{
			std::cerr << "out of range" << std::endl;
		}
		
	}
	
	for(auto[k,v]: dojoMap)
	{
		// std::cout<<k<<' '<<v<<std::endl;

	}
	
	
	

	sshd_config_data.close();



}

private:


};



int main() {

	/*TEST(ObjectCreated)
	{
		EXPECT(false);
	};*/

	/*TEST(MethodThatIsOpeningAndLoadingAFile)
	{*/
		Sshd_configWraper ssdconfigwraper;
		ssdconfigwraper.dataFrom_shd_config();
		//EXPECT(false);
	//};

}