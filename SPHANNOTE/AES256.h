#pragma once
class AES256
{
private:
	std::string keyStr = "EQST_FLAG(search_string)";
	std::string ivStr = "This_is_initial_vector!!";
public:
	std::string AESEncrypt(std::string plainText);
	std::string AESDecrypt(std::string cipherText);
};

