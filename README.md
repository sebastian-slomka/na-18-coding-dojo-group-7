# NA 18 Coding Dojo - Group 18

## Coding task

SSH service on linux contains its global configuration in a file called `sshd_config`  located in `/etc/ssh/`. Please write a wrapper for this configuration file so that it is possible to read values from the given config as well as to alter the data entries inplace in the file.

*In order to alleviate breaking ssh service, copy the sshd_config file to some other location and work on that copy.*

### Example input

```c++

// Object initalisation
const std::path sshd_config_file_path(/etc/ssh/sshd_config)
SSHDConfig sshdConfig(sshd_config_file_path);

// Printing values from the parsed sshd_config file
std::cout << sshdConfig.getPort() << '\n'; // 22
std::cout << sshdConfig << '\n';
/*
Port 22
AddressFamily any
ListenAddress 0.0.0.0
ListenAddress ::
...
*/

// Modyfing values in the parsed sshd_config file (each passed value should be validaded depending what values certain entry can hold)

const unsigned short newPort = 13001;

// Option 1: Error code
auto result = sshdConfig.setPort(newPort);
if(!result && result.has_value()) {
    std::cerr << "Modyfing ssh port filed with error code:" << result.value(); << '\n';
}

// Option 2: Custom exception
try {
    auto result = sshdConfig.setPort(newPort);
} catch(const std::bad_sshd_config_file_entry& bscfe) {
    std::cerr << "Modyfing ssh port filed"; << '\n';
}
```
