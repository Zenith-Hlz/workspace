#include <iostream>
#include <regex>
#include <unordered_map>

bool is_valid_username(const std::string &username)
{
    std::regex username_pattern("^[a-zA-Z][a-zA-Z0-9_]{3,14}$");
    return std::regex_match(username, username_pattern);
}
bool is_valid_password(const std::string &password)
{
    bool has_letter = std::any_of(password.begin(), password.end(), ::isalpha);
    bool has_digit = std::any_of(password.begin(), password.end(), ::isdigit);
    std::regex password_pattern("^[a-zA-Z0-9]{8,20}$");
    return std::regex_match(password, password_pattern) && has_digit && has_letter;
}
bool is_valid_email(const std::string &email)
{
    std::regex email_pattern(R"([\w]+@[\w.]+)");
    return std::regex_match(email, email_pattern);
}
std::string mask_username(const std::string &username)
{
    return username.substr(0, 3) + std::string(username.length() - 3, '*');
}
std::string mask_password(const std::string &password)
{
    return std::string(password.length(), '*');
}
std::string mask_email(const std::string &email)
{
    std::string masked_email;
    for (char ch : email)
    {
        if (ch == '@' || ch == '.')
        {
            masked_email += ch;
        }
        else
        {
            masked_email += '*';
        }
    }
    return masked_email;
}

std::string trim(const std::string &str)
{
    const std::string whitespace = " \"";
    size_t start = str.find_first_not_of(whitespace);
    size_t end = str.find_last_not_of(whitespace);
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

int main()
{
    std::string input;
    std::getline(std::cin, input);

    input = input.substr(1, input.length() - 2);

    std::unordered_map<std::string, std::string> data;
    std::stringstream ss(input);
    std::string pair;

    while (std::getline(ss, pair, ','))
    {
        std::size_t colonPos = pair.find(':');
        if (colonPos != std::string::npos)
        {
            std::string key = trim(pair.substr(0, colonPos));
            std::string value = trim(pair.substr(colonPos + 1));
            data[key] = value;
        }
    }

    std::string illegalFields;

    if (data.find("username") == data.end() || !is_valid_username(data["username"]))
    {
        illegalFields += "username,";
    }
    if (data.find("password") == data.end() || !is_valid_password(data["password"]))
    {
        illegalFields += "password,";
    }
    if (data.find("email") == data.end() || !is_valid_email(data["email"]))
    {
        illegalFields += "email,";
    }

    if (!illegalFields.empty())
    {
        illegalFields.pop_back();
        std::cout << "Illegal " << illegalFields << std::endl;
    }
    else
    {
        std::cout << "Successfully registered." << std::endl;
        std::cout << "username: " << mask_username(data["username"]) << std::endl;
        std::cout << "password: " << mask_password(data["password"]) << std::endl;
        std::cout << "email: " << mask_email(data["email"]) << std::endl;
    }

    return 0;
}