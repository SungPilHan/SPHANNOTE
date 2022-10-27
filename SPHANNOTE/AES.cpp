#include "pch.h"
#include "AES.h"

std::string AES::AESEncrypt(std::string plainText) {
	std::string cipherText;
	std::string EncodedcipherText;

	CryptoPP::HexEncoder encoder;

	//키 생성
	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

	if (CryptoPP::AES::DEFAULT_KEYLENGTH < keyStr.size())
		keyStr = keyStr.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH);
	else if (CryptoPP::AES::DEFAULT_KEYLENGTH > keyStr.size())
		keyStr += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - keyStr.size(), 'a');
	memcpy(key, keyStr.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

	if (CryptoPP::AES::BLOCKSIZE < ivStr.size())
		ivStr = ivStr.substr(0, CryptoPP::AES::BLOCKSIZE);
	else if (CryptoPP::AES::BLOCKSIZE > ivStr.size())
		ivStr += std::string(CryptoPP::AES::BLOCKSIZE - ivStr.size(), 'a');
	memcpy(iv, ivStr.c_str(), CryptoPP::AES::BLOCKSIZE);

	//AES 256 암호화
	CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
	e.SetKeyWithIV(key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

	CryptoPP::StringSource s(plainText, true,
		new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(cipherText)));

	//byte를 hexString으로 인코딩
	encoder.Put((byte*)cipherText.data(), cipherText.size());
	encoder.MessageEnd();
	CryptoPP::word64 size = encoder.MaxRetrievable();
	if (size) {
		EncodedcipherText.resize(size);
		encoder.Get((byte*)&EncodedcipherText[0], EncodedcipherText.size());
	}

	return EncodedcipherText;
}
std::string AES::AESDecrypt(std::string cipherText) {
	std::string plainText;
	std::string DecodedcipherText;

	CryptoPP::HexDecoder decoder;

	//키 생성
	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

	if (CryptoPP::AES::DEFAULT_KEYLENGTH < keyStr.size())
		keyStr = keyStr.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH);
	else if (CryptoPP::AES::DEFAULT_KEYLENGTH > keyStr.size())
		keyStr += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - keyStr.size(), 'a');
	memcpy(key, keyStr.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

	if (CryptoPP::AES::BLOCKSIZE < ivStr.size())
		ivStr = ivStr.substr(0, CryptoPP::AES::BLOCKSIZE);
	else if (CryptoPP::AES::BLOCKSIZE > ivStr.size())
		ivStr += std::string(CryptoPP::AES::BLOCKSIZE - ivStr.size(), 'a');
	memcpy(iv, ivStr.c_str(), CryptoPP::AES::BLOCKSIZE);

	//hexString을 byte로 디코딩
	decoder.Put((byte*)cipherText.data(), cipherText.size());
	decoder.MessageEnd();
	CryptoPP::word64 size = decoder.MaxRetrievable();
	if (size && size <= SIZE_MAX) {
		DecodedcipherText.resize(size);
		decoder.Get((byte*)&DecodedcipherText[0], DecodedcipherText.size());
	}

	//AES 256 복호화
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;
	d.SetKeyWithIV(key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

	CryptoPP::StringSource s(DecodedcipherText, true,
		new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(plainText)));

	return plainText;
}