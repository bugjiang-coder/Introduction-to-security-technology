#include "des.h"


void DES::keyInit(char K[], char key[])
{
	// 密钥进行PC1选择置换
	// PC2_Table已经帮我们去除了 校验位
	int i;
	for (i = 0; i < 56; ++i)
	{
		key[i] = K[PC1_Table[i] - 1];
	}
}

void DES::keyShift(char key[], int shiftL)
{
	// 密钥进行循环左移
	int i;
	char temp[2] = {0, 0};
	for (i = 0; i < shiftL; ++i)
	{
		temp[i] = key[i];
	}
	for (; i < 28 + shiftL; ++i)
	{
		key[i - shiftL] = key[i];
	}
	for (i = 0; i < shiftL; ++i)
	{
		key[28 - shiftL + i] = temp[i];
	}

	for (i = 0; i < shiftL; ++i)
	{
		temp[i] = key[i + 28];
	}
	for (i = 28; i < 56 - shiftL; ++i)
	{
		key[i] = key[i + shiftL];
	}
	for (i = 0; i < shiftL; ++i)
	{
		key[56 - shiftL + i] = temp[i];
	}
}

void DES::keyOut(char key[], char keyi[])
{
	// 密钥进程PC2选择置换
	// PC2_Table帮我们选择性删除了一些 除了第9，18，22，25，35，38，43，54位。
	int i;
	for (i = 0; i < 48; ++i)
	{
		keyi[i] = key[PC2_Table[i] - 1];
	}
}

void DES::DES_Operation(char input[64], char output[64], char keys[16][48])
{ //由于加密和解密的过程是完全相同的所以这里单独提出一个过程
	int i, j, k;
	char L[32], R[32], tmpL[32], tmpR[32]; //记录各轮的左32位和右边32位

	char Extend[48]; // 临时存放扩展置换后的矩阵
	char S_out[32];	 // S盒代替后的输出矩阵

	char merge[64]; //最后合并L R 两个数组

	//输入后的初始置换,直接利用L和R数组存放置换矩阵置换的结果
	for (i = 0; i < 32; ++i)
		L[i] = input[IP_Table[i] - 1];
	for (i = 32; i < 64; ++i)
		R[i - 32] = input[IP_Table[i] - 1];

	for (i = 0; i < 16; ++i)
	{ // 16轮运算
		for (j = 0; j < 32; ++j)
		{ // 先把数据存放到临时数组中
			tmpL[j] = L[j];
			tmpR[j] = R[j];
		}

		for (j = 0; j < 32; ++j)
		{ // 右边数组移动到左边数组
			L[j] = tmpR[j];
		}

		for (j = 0; j < 48; ++j)
		{ // 扩展置换 + 与密钥异或
			Extend[j] = R[E_Table[j] - 1] ^ keys[i][j];
		}

		// S盒替代 最为复杂
		for (j = 0; j < 8; ++j)
		{
			int num = S_Box[j]
						   [Extend[j * 6] + Extend[j * 6 + 5]]
						   [Extend[j * 6 + 1] + Extend[j * 6 + 2] + Extend[j * 6 + 3] + Extend[j * 6 + 4]];
			for (k = 3; k >= 0; --k)
			{
				S_out[(j << 2) + k] = num & 1;
				num >>= 1;
			}
		}

		//P 盒置换
		for (j = 0; j < 32; ++j)
		{ // P盒子置换 + 与L异或
			R[j] = S_out[P_Table[j] - 1] ^ tmpL[j];
		}
	}

	// 进行R L 两个数组合并
	for (i = 0; i < 32; ++i)
		merge[i] = R[i];
	for (i = 32; i < 64; ++i)
		merge[i] = L[i - 32];

	// 16轮完成进行逆置换并输出
	for (i = 0; i < 64; ++i)
	{
		output[i] = merge[IPR_Table[i] - 1];
	}
}

void DES::initEncryptKey(char SecretKey[64], char keys[16][48])
{
	char key[56];			 // 输入的密钥进行初始置换的结果
	keyInit(SecretKey, key); //初始化密钥
	for (int i = 0; i < 16; ++i)
	{
		keyShift(key, KEY_Shift[i]);
		keyOut(key, keys[i]); //将该轮密钥存放在keyi中
	}
}

void DES::initDecryptKey(char SecretKey[64], char keys[16][48])
{
	char key[56];			 // 输入的密钥进行初始置换的结果
	keyInit(SecretKey, key); //初始化密钥
	for (int i = 0; i < 16; ++i)
	{
		keyShift(key, KEY_Shift[i]);
		keyOut(key, keys[15 - i]); //将该轮密钥倒叙存放在keys中
	}
}

void DES::DES_Encrypt(char input[8], char output[8], char keys[16][48])
{
    char origin[64] = {0}, encrypt[64] = {0};
    Char8ToBit64(input, origin);
    DES_Operation(origin, encrypt, keys);
    Bit64ToChar8(encrypt, output);
}

void DES::DES_Decrypt(char input[8], char output[8], char keys[16][48])
{
	char origin[64] = {0}, decrypt[64] = {0};
    Char8ToBit64(input, origin);
    DES_Operation(origin, decrypt, keys);
    Bit64ToChar8(decrypt, output);
}

void DES::Char8ToBit64(char ch[8], char bit[64])
{
	int i, j;
    for (i =0; i < 64;++i){
        bit[i] = 0;
    }
	for (i = 0; i < 8; ++i)
		for (j = 0; j < 8; ++j)
			*(bit + (i << 3) + j) = (*(ch + i) >> j) & 1;
	return;
}

void DES::Bit64ToChar8(char bit[64], char ch[8])
{
	int i, j;
    for (i =0; i < 8;++i){
        ch[i] = 0;
    }
	for (i = 0; i < 8; ++i)
		for (j = 0; j < 8; ++j)
			*(ch + i) += *(bit + (i << 3) + j) << j;

	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//上面的部分可以单独 作为一个库来使用  8位每组进行加密 下面是实现字符串加密的部分
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
