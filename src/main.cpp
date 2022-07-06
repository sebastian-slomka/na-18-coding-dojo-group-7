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
struct TestCase
{
	std::string name{};
	std::ostringstream failures{};
};
template <typename T>
void operator|(TestCase &testCase, T &&testBody)
{
	testBody();
	auto failures = testCase.failures.str();
	if (failures.empty())
		std::cout << testCase.name << ": SUCCESS\n";
	else
		std::cerr << testCase.name << ": FAILURE\n"
				  << failures;
}
void addFailure(std::ostream &os, const char *file, unsigned line, const char *condition)
{
	os << file << ":" << line << ": Failed: " << condition << "\n";
}
#define TEST(name)        \
	TestCase name{#name}; \
	name | [&, &failures = name.failures ]
#define EXPECT(cond) \
	if (cond)        \
	{                \
	}                \
	else             \
		addFailure(failures, __FILE__, __LINE__, #cond)
#define ASSERT(cond) \
	if (cond)        \
	{                \
	}                \
	else             \
		return addFailure(failures, __FILE__, __LINE__, #cond)

/*******************************************************************************************/
#include <memory>
#include <fstream>
#include <map>

class SSHDConfig
{
public:
	SSHDConfig(const std::string&);

	bool parse(){
		std::fstream sshdFile;
		sshdFile.open(path, std::ios::in);
		std::string line;
		std::string key;
		std::string value;
		size_t space;
		if(sshdFile.is_open()){
			while(!sshdFile.eof()){
				getline(sshdFile, line);
				space = line.find(" ");
				key = line.substr(0, space-1);
				value = line.substr(space+1, line.length());
				sshdData.insert(std::make_pair(key, value));
			}
			sshdFile.close();
			return !sshdFile.is_open();
		 } else {
			return false;
		 }

	};
private:
	const std::string path;

	std::map<std::string, std::string> sshdData;
};

SSHDConfig::SSHDConfig(const std::string& cpath):path(cpath)
{
}

int main()
{

	TEST(classCreation)
	{
		std::unique_ptr<SSHDConfig> sshdConfig = std::make_unique<SSHDConfig>("");
		EXPECT(sshdConfig != nullptr);
	};

	TEST(parseMethod)
	{
		std::unique_ptr<SSHDConfig> sshdConfig = std::make_unique<SSHDConfig>("../data/sshd_config");
		EXPECT(sshdConfig->parse());
	};

}
