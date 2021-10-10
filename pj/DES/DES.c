#include <stdio.h>
#include <string.h>

char S_Box[8][4][16] =
	{ //8个S盒   三维数组  											// S1
		14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
		// S2
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
		// S3
		10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
		// S4
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
		// S5
		2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
		// S6
		12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
		// S7
		4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
		// S8
		13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};
char IP_Table[64] =
	{ //IP置换矩阵
		58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
char E_Table[48] =
	{ //扩展矩阵
		32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
char P_Table[32] =
	{ //  P 盒
		16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
		2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
char IPR_Table[64] =
	{ //逆IP置换矩阵
		40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
char PC1_Table[56] =
	{ //密钥第一次置换矩阵
		57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
char PC2_Table[48] =
	{ // 密钥第二次置换矩阵
		14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
		23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
		41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
char KEY_Shift[16] =
	{ //不同轮次密钥进行循环左移位数
		1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

char M[64] = {1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 1, 0, 1, 1, 1, 1,
			  1, 1, 1, 1, 0, 1, 1, 1,
			  1, 1, 1, 1, 1, 0, 1, 1,
			  1, 1, 1, 1, 1, 0, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1};

char K[64] = {1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 1, 0, 1, 1, 1, 1,
			  1, 1, 0, 1, 1, 0, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 1, 1, 1, 0, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 0, 1, 1, 1, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1};

void keyInit(char K[], char key[]);
void keyShift(char key[], int shiftL);
void keyOut(char key[], char keyi[]);
void DES_Operation(char input[64], char output[64], char keys[16][48]);
void DES_Encrypt(char input[8], char output[8], char keys[16][48]);
void DES_Decrypt(char input[8], char output[8], char keys[16][48]);
void Char8ToBit64(char ch[8], char bit[64]);
void Bit64ToChar8(char bit[64], char ch[8]);

void print(char *m, int size)
{ // 测试函数
	int i;
	for (i = 0; i < size; ++i)
	{
		printf("%d ", m[i]);
	}
	printf("\n\n");
}
void printc(char *m, int size)
{ // 测试函数
	int i;
	for (i = 0; i < size; ++i)
	{
		printf("%c ", m[i]);
	}
	printf("\n\n");
}

void keyInit(char K[], char key[])
{
	// 密钥进行PC1选择置换
	// PC2_Table已经帮我们去除了 校验位
	int i;
	for (i = 0; i < 56; ++i)
	{
		key[i] = K[PC1_Table[i] - 1];
	}
}

void keyShift(char key[], int shiftL)
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

void keyOut(char key[], char keyi[])
{
	// 密钥进程PC2选择置换
	// PC2_Table帮我们选择性删除了一些 除了第9，18，22，25，35，38，43，54位。
	int i;
	for (i = 0; i < 48; ++i)
	{
		keyi[i] = key[PC2_Table[i] - 1];
	}
}

void DES_Operation(char input[64], char output[64], char keys[16][48])
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

void initEncryptKey(char SecretKey[64], char keys[16][48])
{
	char key[56];			 // 输入的密钥进行初始置换的结果
	keyInit(SecretKey, key); //初始化密钥
	for (int i = 0; i < 16; ++i)
	{
		keyShift(key, KEY_Shift[i]);
		keyOut(key, keys[i]); //将该轮密钥存放在keyi中
	}
}

void initDecryptKey(char SecretKey[64], char keys[16][48])
{
	char key[56];			 // 输入的密钥进行初始置换的结果
	keyInit(SecretKey, key); //初始化密钥
	for (int i = 0; i < 16; ++i)
	{
		keyShift(key, KEY_Shift[i]);
		keyOut(key, keys[15 - i]); //将该轮密钥倒叙存放在keys中
	}
}

void DES_Encrypt(char input[8], char output[8], char keys[16][48])
{
	char origin[64] = {64}, encrypt[64] = {64};
	Char8ToBit64(input, origin);
	DES_Operation(origin, encrypt, keys);
	Bit64ToChar8(encrypt, output);
}

void DES_Decrypt(char input[8], char output[8], char keys[16][48])
{
	char origin[64] = {0}, decrypt[64] = {0};
	Char8ToBit64(input, origin);
	DES_Operation(origin, decrypt, keys);
	Bit64ToChar8(decrypt, output);
}

void Char8ToBit64(char ch[8], char bit[64])
{
	int i, j;
	memset(bit, 0, 64);
	for (i = 0; i < 8; ++i)
		for (j = 0; j < 8; ++j)
			*(bit + (i << 3) + j) = (*(ch + i) >> j) & 1;
	return;
}

void Bit64ToChar8(char bit[64], char ch[8])
{
	int i, j;
	memset(ch, 0, 8);
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

int encrypt(char *originFile, char *keyStr, char *encryptedFile)
{
	FILE *origin, *encrypted;
	int cnt;
	char originBlock[8], encryptedBlock[8], keyBlock[8];
	char key[64];
	char keys[16][48];

	if ((origin = fopen(originFile, "rb")) == NULL)
		return -1;
	if ((encrypted = fopen(encryptedFile, "wb")) == NULL)
		return -1;

	memcpy(keyBlock, keyStr, 8);

	Char8ToBit64(keyBlock, key);
	initEncryptKey(key, keys);

	while (!feof(origin))
	{
		if ((cnt = fread(originBlock, sizeof(char), 8, origin)) == 8)
		{
			DES_Encrypt(originBlock, encryptedBlock, keys);
			fwrite(encryptedBlock, sizeof(char), 8, encrypted);
		}
	}

	if (cnt)
	{
		memset(originBlock + cnt, '\0', 7 - cnt);
		originBlock[7] = 8 - cnt;
		DES_Encrypt(originBlock, encryptedBlock, keys);
		fwrite(encryptedBlock, sizeof(char), 8, encrypted);
	}

	fclose(origin);
	fclose(encrypted);
	return 0;
}

int decrypt(char *originFile, char *keyStr, char *decryptedFile)
{
	FILE *origin, *decrypted;
	int cnt = 0, fileLen, i;
	char originBlock[8], decryptedBlock[8], keyBlock[8];
	char key[64];
	char keys[16][48];

	if ((origin = fopen(originFile, "rb")) == NULL)
		return -1;
	if ((decrypted = fopen(decryptedFile, "wb")) == NULL)
		return -1;

	memcpy(keyBlock, keyStr, 8);
	Char8ToBit64(keyBlock, key);
	initDecryptKey(key, keys);

	fseek(origin, 0, SEEK_END);
	fileLen = ftell(origin);
	rewind(origin);

	while (1)
	{
		fread(originBlock, sizeof(char), 8, origin);
		DES_Decrypt(originBlock, decryptedBlock, keys);
		cnt += 8;
		if (cnt < fileLen)
			fwrite(decryptedBlock, sizeof(char), 8, decrypted);
		else
			break;
	}

	if (decryptedBlock[7] < 8)
	{
		for (i = 8 - decryptedBlock[7]; i < 7; ++i)
		{
			if (decryptedBlock[i] != '\0')
			{
				break;
			}
		}
	}
	if (i == 7)
	{
		fwrite(decryptedBlock, sizeof(char), 8 - decryptedBlock[7], decrypted);
	}
	else
	{
		fwrite(decryptedBlock, sizeof(char), 8, decrypted);
	}

	fclose(origin);
	fclose(decrypted);
	return 0;
}

int main()
{
	encrypt("1.txt", "text", "1outOrigin.txt");
	decrypt("1outOrigin.txt", "text", "3.txt");
	return 0;
}
