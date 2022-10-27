#pragma once
class AES
{
private:
	std::string keyStr = "EQST_KEY_GENERATE_SEED_STRING";
	std::string ivStr = "This_is_initial_vector!!";
public:
	std::string AESEncrypt(std::string plainText);
	std::string AESDecrypt(std::string cipherText);
};

