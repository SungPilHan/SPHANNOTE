#pragma once
class EQSTLicense
{
public:
	std::string AESEncrypt(std::string plainText, std::string license);
	std::string AESDecrypt(std::string cipherText, std::string license);
};