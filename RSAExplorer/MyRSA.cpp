#include "pch.h"

#include "MyRSA.h"

// static PrimeTable 初始化
std::vector<unsigned int>* MyRSA::RSA::PrimeTable = NULL;
// 建構子
MyRSA::RSA::RSA()
{
	key = new Key{ 0, NULL, NULL };
	uiMessage = new std::vector<unsigned int>();
	keyGeneration();
}
MyRSA::RSA::RSA(Key* key)
{
	this->key = key;
	uiMessage = NULL;
	keyGeneration();
}
MyRSA::RSA::~RSA()
{
	key = NULL;
	if (uiMessage != NULL)
		uiMessage->clear();
	uiMessage = NULL;
}
// 建立質數表
void MyRSA::RSA::createPrimeTable()
{
	std::vector<int> tmp(MAX_PRIME_SIZE, 0);
	size_t prime, filt;
	for (prime = 2; prime < tmp.size(); ++prime)
	{
		if (tmp.at(prime) != 0)
		{
			if (tmp.at(prime) == 1)
				PrimeTable->push_back(static_cast<unsigned int>(prime));
			continue;
		}
		PrimeTable->push_back(prime);
		for (filt = prime * 2; filt < tmp.size(); filt += prime)
		{
			tmp.at(filt) = -1;
		}
	}
}
// 取得隨機質數
unsigned int MyRSA::RSA::getRandPrime()
{
	return PrimeTable->at(rand() % (PrimeTable->size() - 1));
}
// 密鑰生成
void MyRSA::RSA::keyGeneration()
{
	if (PrimeTable == NULL)
	{
		PrimeTable = new std::vector<unsigned int>();
		createPrimeTable();
		// 亂數初始化
		srand(static_cast<unsigned int>(time(NULL)));
	}
	int p = getRandPrime(), q = getRandPrime();
	while (p == q) q = getRandPrime();

	keyDistribution(p * q, lcm((p - 1), (q - 1)));
}
// 密鑰分發
void MyRSA::RSA::keyDistribution(unsigned int N, unsigned int r)
{
	unsigned int e = getCoprimeE(r);
	unsigned int d = modularArithmetic(e, r);

	while (d == 0)
	{
		e = getCoprimeE(r);
		d = modularArithmetic(e, r);
	}
	key->N = N;
	key->publicKey = new PublicKey { N, e };
	key->privateKey = new PrivateKey { N,  d};
}
// e < r & 互質 gcd(e, r) == 1 
unsigned int MyRSA::RSA::getCoprimeE(unsigned int r)
{
	unsigned int e = getRandPrime();
	while (e >= r || gcd(r, e) == 0) e = getRandPrime();
	/* // 數可能過大，導致計算問題
	unsigned int e = (2 + rand() % (r - 1));
	while (gcd(r, e) != 1) e = (2 + rand() % (r - 1));
	*/
	return e;
}
//  d * e ≡ 1 (mod r) [ d * e % r == 1 ]
unsigned int MyRSA::RSA::modularArithmetic(unsigned int e, unsigned int r)
{
	for (size_t d = 1; d < r; ++d)
	{
		if (e * d % r == 1)
		{
			return d;
		}
	}
	return 0;
}
// 最大公因數
unsigned int MyRSA::RSA::gcd(unsigned int a, unsigned int b)
{
	int c = a % b;
	if (c) return gcd(b, c);
	else return b;
}
// 最小公倍數
unsigned int MyRSA::RSA::lcm(unsigned int a, unsigned int b)
{
	unsigned int c = 1;
	for (auto it = PrimeTable->begin(); it != PrimeTable->end();)
	{
		if (a % *it == 0 && b % *it == 0)
		{
			a /= *it;
			b /= *it;
			c *= *it;
			if (*it > a || *it > b) break;
		}
		else
		{
			++it;
		}
	}
	return c * a * b;
}
// string <=> unsigned int[]
void MyRSA::stringToVUI(const char* str, std::vector<unsigned int>& uiMessages)
{
	if (!uiMessages.empty())
		uiMessages.clear();
	while (*str)
	{
		uiMessages.push_back(static_cast<unsigned int>(*str++));
	}
}
std::string MyRSA::vUIToString(std::vector<unsigned int>& uiMessages)
{
	if (uiMessages.empty())
		return "NULL";
	std::string tmp = "";
	for (auto it = uiMessages.begin(); it != uiMessages.end(); ++it)
	{
		tmp += static_cast<char>(*it);
	}
	return tmp;
}
// 加密
void MyRSA::encryption(std::vector<unsigned int>& uiMessages, PublicKey& key)
{
	for (auto it = uiMessages.begin(); it != uiMessages.end(); ++it)
	{
		*it = cryption(*it, key.e, key.N);
	}
}
// 解密
void MyRSA::decryption(std::vector<unsigned int>& uiMessages, PrivateKey& key)
{
	if (uiMessages.empty()) return;
	for (auto it = uiMessages.begin(); it != uiMessages.end(); ++it)
	{
		*it = cryption(*it, key.d, key.N);
	}
}
// base ^ power ≡ c (mod N) [ (base ^ power) % N ]
unsigned int MyRSA::cryption(unsigned int base, unsigned int power, unsigned int N)
{
	unsigned long long c = base % N;
	while (power > 1)
	{
		c *= base;
		c %= N;
		--power;
	}
	return static_cast<unsigned int>(c);
}
// file
void MyRSA::readBinFile(std::string filename, std::vector<unsigned int>& uiMessages)
{
	if (!uiMessages.empty())
		uiMessages.clear();
	if (!binNameCheck(filename))
		filename += ".bin";
	unsigned int buff;
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	while (fin)
	{
		fin.read(reinterpret_cast<char*>(&buff), sizeof(unsigned int));
		uiMessages.push_back(buff);
	}
	fin.close();
}
void MyRSA::writeBinFile(std::string filename, std::vector<unsigned int>& uiMessages)
{
	if (uiMessages.empty()) 
		return;
	if (!binNameCheck(filename))
		filename += ".bin";
	std::ofstream fout;
	fout.open(filename, std::ios::out | std::ios::binary);
	for (auto it = uiMessages.begin(); it != uiMessages.end(); ++it)
	{
		fout.write(reinterpret_cast<const char*>(&*it), sizeof(unsigned int));
	}
	fout.close();
}
bool MyRSA::binNameCheck(std::string filename)
{
	auto it = filename.end() - 1;
	if (*it != 'n' || *(it - 1) != 'i' || *(it - 2) != 'b' || *(it - 3) != '.')
		return 0;
	return 1;
}

// save key
void MyRSA::savePublicKey(char* filename, PublicKey* publicKey)
{
	std::vector<unsigned int> tmp = { publicKey->N, publicKey->e };
	writeBinFile(filename, tmp);
}
void MyRSA::savePrivateKey(char* filename, PrivateKey* privateKey)
{
	std::vector<unsigned int> tmp = { privateKey->N, privateKey->d };
	MyRSA::writeBinFile(filename, tmp);
}
// read key
bool MyRSA::readPublicKey(char* filename, PublicKey* publicKey)
{
	std::vector<unsigned int> tmp;
	readBinFile(filename, tmp);
	// 寫入時末端會重複最後一個 2 + 1
	if (tmp.size() != 3)
		return 0;
	publicKey->N = tmp.at(0);
	publicKey->e = tmp.at(1);
	return 1;
}
bool MyRSA::readPrivateKey(char* filename, PrivateKey* privateKey)
{
	std::vector<unsigned int> tmp;
	MyRSA::readBinFile(filename, tmp);
	// 寫入時末端會重複最後一個 2 + 1
	if (tmp.size() != 3)
		return 0;
	privateKey->N = tmp.at(0);
	privateKey->d = tmp.at(1);
	return 1;
}
