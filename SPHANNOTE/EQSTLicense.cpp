#include "pch.h"
#include "EQSTLicense.h"

std::string EQSTLicense::AESEncrypt(std::string plainText, std::string license) {
	try {
		std::string cipherText;
		std::string base64encodedcipherText;

		std::string keyStr = license.substr(0, 32);
		std::string ivStr = license.substr(32, 16);

		byte key[CryptoPP::AES::MAX_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
		memcpy(key, keyStr.c_str(), CryptoPP::AES::MAX_KEYLENGTH);
		memcpy(iv, ivStr.c_str(), CryptoPP::AES::BLOCKSIZE);

		CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
		e.SetKeyWithIV(key, CryptoPP::AES::MAX_KEYLENGTH, iv, CryptoPP::AES::BLOCKSIZE);

		CryptoPP::StringSource s(plainText, true,
			new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(cipherText)));

		CryptoPP::StringSource ss(cipherText, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(base64encodedcipherText), false));

		return base64encodedcipherText;
	}
	catch (CryptoPP::Exception& e) {
		return "no";
	}
}

std::string EQSTLicense::AESDecrypt(std::string cipherText, std::string license) {
	try {
		std::string plainText;
		std::string base64decodecipherText;

		std::string keyStr = license.substr(0, 32);
		std::string ivStr = license.substr(32, 16);

		byte key[CryptoPP::AES::MAX_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
		memcpy(key, keyStr.c_str(), CryptoPP::AES::MAX_KEYLENGTH);
		memcpy(iv, ivStr.c_str(), CryptoPP::AES::BLOCKSIZE);

		CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;
		d.SetKeyWithIV(key, CryptoPP::AES::MAX_KEYLENGTH, iv, CryptoPP::AES::BLOCKSIZE);

		CryptoPP::StringSource s(cipherText, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(base64decodecipherText)));

		CryptoPP::StringSource ss(base64decodecipherText, true,
			new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(plainText), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING));

		return plainText;
	}
	catch (CryptoPP::Exception& e) {
		return "no";
	}
}