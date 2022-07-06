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
	SSHDConfig(const std::string &);

	bool parse()
	{
		std::ifstream sshdFile(path);
		if (!sshdFile.is_open())
		{
			return false;
		}

		std::string line;
		std::string key;
		std::string value;
		size_t space;
		while (getline(sshdFile, line))
		{
			space = line.find(" ");
			key = line.substr(0, space);
			value = line.substr(space + 1, line.length());
			sshdData.insert(std::make_pair(key, value));
			// sshdData.insert({key,value});
		}
		sshdFile.close();

		for (auto [key, value] : sshdData)
		{
			std::cout << key << " " << value << std::endl;
		}
		return !sshdFile.is_open();
	};

	std::string getPort()
	{
		return sshdData.find("Port")->second; // *sshdData.find("Port").second
	}

private:
	const std::string path;

	std::map<std::string, std::string> sshdData;
};

SSHDConfig::SSHDConfig(const std::string &cpath) : path(cpath)
{
}

int main()
{
	TEST(classCreation)
	{
		std::unique_ptr<SSHDConfig> sshdConfig = std::make_unique<SSHDConfig>("/home/wolek/nokia_accademy/14_four_days_codingdojo/second_day/na-18-coding-dojo-group-7/data/sshd_config");
		EXPECT(sshdConfig != nullptr);
	};

	TEST(parseMethod)
	{
		std::unique_ptr<SSHDConfig> sshdConfig = std::make_unique<SSHDConfig>("/home/wolek/nokia_accademy/14_four_days_codingdojo/second_day/na-18-coding-dojo-group-7/data/sshd_config");
		bool result = sshdConfig->parse();
		EXPECT(result == true);
	};

	TEST(shouldReturnPortNumber)
	{
		SSHDConfig sshdConfig("/home/wolek/nokia_accademy/14_four_days_codingdojo/second_day/na-18-coding-dojo-group-7/data/sshd_config");
		sshdConfig.parse();
		EXPECT(sshdConfig.getPort() == "22");
	};
}
