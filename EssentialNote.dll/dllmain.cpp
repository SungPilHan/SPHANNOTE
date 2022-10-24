// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"

std::string DefaultkeyStr = "EQST_KEY_DEFAULT_SEED";
std::string ivStr = "This_is_initial_vector!!";

std::string AESDecrypt(std::string cipherText);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport)std::string AESEncrypt(std::string plainText) {
		std::string cipherText;
		std::string EncodedcipherText;

		CryptoPP::HexEncoder encoder;

		//키 생성
		CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];


		if (CryptoPP::AES::DEFAULT_KEYLENGTH < DefaultkeyStr.size())
			DefaultkeyStr = DefaultkeyStr.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH);
		else if (CryptoPP::AES::DEFAULT_KEYLENGTH > DefaultkeyStr.size())
			DefaultkeyStr += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - DefaultkeyStr.size(), 'a');
		memcpy(key, DefaultkeyStr.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

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
		encoder.Put((CryptoPP::byte*)cipherText.data(), cipherText.size());
		encoder.MessageEnd();
		CryptoPP::word64 size = encoder.MaxRetrievable();
		if (size) {
			EncodedcipherText.resize(size);
			encoder.Get((CryptoPP::byte*)&EncodedcipherText[0], EncodedcipherText.size());
		}

		std::string test = AESDecrypt(EncodedcipherText);

		return EncodedcipherText;
	}
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport)std::string AESEncryptWithKey(std::string plainText, std::string keyString) {
		std::string cipherText;
		std::string EncodedcipherText;
		std::string keyStr;

		CryptoPP::HexEncoder encoder;

		keyStr = AESDecrypt(keyString);


		//키 생성
		CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];


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
		encoder.Put((CryptoPP::byte*)cipherText.data(), cipherText.size());
		encoder.MessageEnd();
		CryptoPP::word64 size = encoder.MaxRetrievable();
		if (size) {
			EncodedcipherText.resize(size);
			encoder.Get((CryptoPP::byte*)&EncodedcipherText[0], EncodedcipherText.size());
		}

		return EncodedcipherText;
	}
#ifdef __cplusplus
}
#endif

std::string AESDecrypt(std::string cipherText) {
	std::string plainText;
	std::string DecodedcipherText;

	CryptoPP::HexDecoder decoder;

	//키 생성
	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

	if (CryptoPP::AES::DEFAULT_KEYLENGTH < DefaultkeyStr.size())
		DefaultkeyStr = DefaultkeyStr.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH);
	else if (CryptoPP::AES::DEFAULT_KEYLENGTH > DefaultkeyStr.size())
		DefaultkeyStr += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - DefaultkeyStr.size(), 'a');
	memcpy(key, DefaultkeyStr.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

	if (CryptoPP::AES::BLOCKSIZE < ivStr.size())
		ivStr = ivStr.substr(0, CryptoPP::AES::BLOCKSIZE);
	else if (CryptoPP::AES::BLOCKSIZE > ivStr.size())
		ivStr += std::string(CryptoPP::AES::BLOCKSIZE - ivStr.size(), 'a');
	memcpy(iv, ivStr.c_str(), CryptoPP::AES::BLOCKSIZE);

	//hexString을 byte로 디코딩
	decoder.Put((CryptoPP::byte*)cipherText.data(), cipherText.size());
	decoder.MessageEnd();
	CryptoPP::word64 size = decoder.MaxRetrievable();
	if (size && size <= SIZE_MAX) {
		DecodedcipherText.resize(size);
		decoder.Get((CryptoPP::byte*)&DecodedcipherText[0], DecodedcipherText.size());
	}

	//AES 256 복호화
	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;
	d.SetKeyWithIV(key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

	CryptoPP::StringSource s(DecodedcipherText, true,
		new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(plainText)));

	return plainText;
}

#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport)std::string AESDecryptWithKey(std::string cipherText, std::string keyString) {
		std::string plainText;
		std::string DecodedcipherText;
		std::string keyStr;

		CryptoPP::HexDecoder decoder;

		keyStr = AESDecrypt(keyString);

		//키 생성
		CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

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
		decoder.Put((CryptoPP::byte*)cipherText.data(), cipherText.size());
		decoder.MessageEnd();
		CryptoPP::word64 size = decoder.MaxRetrievable();
		if (size && size <= SIZE_MAX) {
			DecodedcipherText.resize(size);
			decoder.Get((CryptoPP::byte*)&DecodedcipherText[0], DecodedcipherText.size());
		}

		//AES 256 복호화
		CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;
		d.SetKeyWithIV(key, CryptoPP::AES::DEFAULT_KEYLENGTH, iv);

		CryptoPP::StringSource s(DecodedcipherText, true,
			new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(plainText)));

		return plainText;
	}
#ifdef __cplusplus
}
#endif