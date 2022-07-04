#pragma once

#ifndef MYRSA_H
#define MYRSA_H

#include <vector>
#include <ctime>
#include <fstream>

#define MAX_PRIME_SIZE 1000

namespace MyRSA
{
	struct PublicKey
	{
		unsigned int N;
		unsigned int e;
	};
	struct PrivateKey
	{
		unsigned int N;
		unsigned int d;
	};
	struct Key
	{
		unsigned int N;
		PublicKey* publicKey;
		PrivateKey* privateKey;
	};

	class RSA
	{
	private:
		// 質數表
		static std::vector<unsigned int>* PrimeTable;
		void createPrimeTable();
		unsigned int getRandPrime();
		// 密鑰生成
		void keyGeneration();
		void keyDistribution(unsigned int N, unsigned int r);
		unsigned int getCoprimeE(unsigned int r);
		unsigned int modularArithmetic(unsigned int e, unsigned int r);
		// 數學
		unsigned int gcd(unsigned int a, unsigned int b);
		unsigned int lcm(unsigned int a, unsigned int b);
	public:
		Key* key;
		std::vector<unsigned int>* uiMessage;

		RSA();
		RSA(Key *key);
		~RSA();
	};
	// string < = > unsigned int[]
	void stringToVUI(const char* str, std::vector<unsigned int>& uiMessages);
	std::string vUIToString(std::vector<unsigned int>& uiMessages);
	// 加/解密
	void encryption(std::vector<unsigned int>& uiMessages, PublicKey& key);
	void decryption(std::vector<unsigned int>& uiMessages, PrivateKey& key);
	unsigned int cryption(unsigned int base, unsigned int power, unsigned int N);
	// file
	void readBinFile(std::string filename, std::vector<unsigned int>& uiMessages);
	void writeBinFile(std::string filename, std::vector<unsigned int>& uiMessages);
	bool binNameCheck(std::string filename);
	void savePublicKey(char* filename, PublicKey* publicKey);
	void savePrivateKey(char* filename, PrivateKey* privateKey);
	bool readPublicKey(char* filename, PublicKey* publicKey);
	bool readPrivateKey(char* filename, PrivateKey* privateKey);
}

#endif // !MYRSA_H