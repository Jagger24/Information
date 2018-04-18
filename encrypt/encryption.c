/**
 *	CSE 4471 - Information Security
 *
 * 	Evan Adamic, Rebecca Hu, Jeffrey Jagger, 
 * 	Abdikarim Mohamed, Catherine Wang
 *
 *	Encryption/decryption module for two-factor authenication 
 *	codes stored in the database.
 *
 * 	Compile using Makefile
 * 		$ make (see Makefile)
 *
 *	Command line:
 *		$ encryption.exe <code> <key> <eflag>
 *
 *	<code>:		The authentication code to encrypt.
 *	<key>:		The private key used for encryption.
 *	<eflag>: 	Encrypt <-e> or decrypt <-d> input.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "ciphers.h"

const int MaxNumArgs 		= 4;
const char* ArgCountError 	= "Invalid arg count";
const char* ArgError		= "Invalid args";
const int ModAlph		= 26;
const int ModDec		= 10;
const int NumCiphers		= 4;

//TODO this is for testing //***********************************************
const char* InvalidResult 	= "Error decrypting input";
void validateResults(char* plaintext_input, char* encrypted_input, char* decrypted_input,\
			int key, bool eflag);
//**************************************************************************


/**
 * Function prototypes
 */
void encrypt(char* new_code, char* code, int key, bool eflag);
char xorCipher(char code, int key);
char caesarCipher(char code, int key, bool eflag);
char blockCipher(char code, int key, bool eflag);
char affineCipher(char code, int key, bool eflag);
int gcd(int a, int b);


/**
 * Main function
 */
int main(int argc, char* argv[])
{
	int i;
	char* input;
	int key;
	char* encrypted_input = malloc(sizeof(char*));
	char* decrypted_input = malloc(sizeof(char*));
	char* input_flag;
	bool eflag = true;

	// Check arg count
	if (argc != MaxNumArgs)
	{
		printf("Encryption.c::main\n\t%s\n", ArgCountError);
		printf("%i :", argc);
		for (i = 0; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		printf("\n");
		exit(-1);
	}

	// First arg should be code String
	input = argv[1];
	if (strlen(input) <= 1 || input == NULL)
	{
		printf("Encryption.c::main\n\t%s >> %s\n", ArgError, argv[1]);
		exit(-1);
	}
	
	// Second arg should be key int
	key = atoi(argv[2]);
	if (key == 0)
	{
		printf("Encryption.c::main\n\t%s >> %s\n", ArgError, argv[2]);
		exit(-1);
	}

	// Third arg should be ecrypt/decrypt flag
	input_flag = argv[3];
	if (input_flag[0] == '-' && input_flag[1] == 'e')
	{
		eflag = true;
	}	
	else  if (input_flag[0] == '-' && input_flag[1] == 'd')
	{
		eflag = false;
	}
	else
	{
		printf("Encryption.c::main\n\t%s >> %s\n", ArgError, argv[3]);
		exit(-1);
	}


	// TODO this is for testing ***************************************
//	printf("Code: %s\n", input);
//	printf("Key: %i\n", key);
//	printf("Key %% 26: %i\n", key%26);
//	printf("encrypt = %s\n", eflag ? "true" : "flase");
	//******************************************************************


	// Encrypt input
	encrypt(encrypted_input, input, key, eflag);
//	printf("Encrypted input: %s\n", encrypted_input);
	printf("%s", encrypted_input);
	
	printf("\n");

	// TODO this is for testing ***************************************
//	validateResults(input, encrypted_input, decrypted_input, key, eflag);
	//*****************************************************************
	
	free(encrypted_input);
	free(decrypted_input);
}


/**
 * TODO this is for testing ***********************************************
 * Test function to validate symmetric encryption/decryption
 * ***********************************************************************
 */
void validateResults(char* input, char* encrypted_input, char* decrypted_input,\
		int key, bool eflag) 
{
	bool isValid = true;
	eflag = !eflag;

	// Decrypt input
	encrypt(decrypted_input, encrypted_input, key, eflag);
	if (strlen(decrypted_input) == strlen(input))
	{
		int i = 0;
		for (i = 0; i < strlen(input); i++)
		{
			if (decrypted_input[i] != input[i])
			{
				isValid = false;
				printf("%c != %c\n", \
				decrypted_input[i], input[i]);
			}
		}
	}
	else 
	{
		isValid = false;
	}

	// Print results
	if (!isValid)
	{
		printf("Encryption::main\n\t%s: %s >>> %s\n", \
			InvalidResult, input, decrypted_input);
		exit(0);
	}
	else
	{
		printf("Decrypted input: %s\n", decrypted_input);
		printf("Success!\n");
	}
}
//************************************************************************


/**
 * Encrypt/decrypt function
 *
 * 	Iterate over the code to encrypt/decrypt character by character using multiple 
 * cipher algorithms in a "round robin" schedule. Each encrypt/decrypt algorithm is
 * executed in its respective function call.
 * 	1. XOR
 * 	2. Caesar
 * 	3. Block
 * 	4. Affine
 * 	(repeat until '\0')
 * 
 * char* <new_code>:	Pointer to the new code generated from encrypting/decrypting <code>.
 * char* <code>:	Pointer to the code argument given to be encrypted/decrypted.
 * int <key>:		Integer value key argument used to encrypt/decrypt input <code>.
 * bool <eflag>:	Boolean flag to determine whether to encrypt or decrypt <code>.
 */
void encrypt(char* new_code, char* code, int key, bool eflag)
{
	int i;
	for (i = 0; i < strlen(code); i++)
	{
		switch (i % NumCiphers) 
		{
			case 0:	
				new_code[i] = xorCipher(code[i], key);
				break;
			case 1:	
				new_code[i] = caesarCipher(code[i], key, eflag);
				break;
			case 2:
				new_code[i] = blockCipher(code[i], key, eflag);
				break;
			case 3:
				new_code[i] = affineCipher(code[i], key, eflag);
				break;
			default:
				break;
		}
	}
}


/**
 * XOR Cipher
 *
 * 	XOR operation on char <code> using <key> % ModAlph. The modulo 
 * operation is done on key to remove side effects of ASCII translation 
 * into the NULL character (0x0). XOR is symmetric, so the eflag is not 
 * needed.
 */
char xorCipher(char code, int key) 
{
	return code^(key % ModAlph);
}


/**
 * Caesar Cipher
 *
 * 	Caesar substitution on char <code> using <key> % CharMapSize. <code> 
 * is either encrypted or decrypted depending on eflag=true/false respectively. 
 * This function is dependent on ciphers.c function definitions for 
 * letter_to_num() and num_to_letter().
 */
char caesarCipher(char code, int key, bool eflag)
{
	char new_code = code;
	int code_num = letter_to_num(code);
	
	key = key % CharMapSize;

	if (eflag)
	{
		code_num = (code_num + key) % CharMapSize;		
	}
	else
	{
		code_num = (code_num - key);
		if (code_num < 0)
		{
			code_num += CharMapSize;
		}
	}

	new_code = num_to_letter(code_num);

	return new_code;
}


/**
 * Block Cipher
 *
 * 	Block substitution based on arbitrary BlockCharMap (ciphers.c). The
 * alphanumeric character <code> is mapped to its correspoonding alphanumeric
 * character in BlockCharMap or back to its plaintext depending on eflag=true/
 * false respectively.
 */
char blockCipher(char code, int key, bool eflag)
{
	char new_code = code;

	if (eflag) 
	{
		int code_num = letter_to_num(code);
		new_code = BlockCharMap[code_num];
	}
	else
	{
		int i = 0;
		while (BlockCharMap[i] != code)
		{
			i++;
		}
		new_code = num_to_letter(i);
	}

	return new_code;
}


/**
 * Affine Cipher
 *
 * 	Affine cipher is done on <code> using <key> % CharMapSize. This done 
 * by computing a value 'a' such that a is coprime with the alphabet size 
 * CharMapSize, and a*a^-1 Mod alphabet_size = 1. 'b' is an arbitrary offset
 * (as long as a != 1) similar to Caesar cipher. 
 */
char affineCipher(char code, int key, bool eflag)
{
	char new_code = code;
	int code_num;
	int a = key % CharMapSize;
	int a_inv = (CharMapSize + 1) / a;
	int b = key % CharMapSize;

	/*
	 * Example:
	 * 3 * 21 = 63
	 * 	=> 63 % 62 = 1;
	 */
	while ( (a*a_inv) % CharMapSize != 1 || gcd(a, CharMapSize) > 1 )
	{
		a++;
		a_inv = (CharMapSize + 1) / a;
	}

	if (eflag)
	{
		code_num = (a * letter_to_num(code) + b) % CharMapSize;
		new_code = num_to_letter(code_num);
	}
	else
	{
		code_num = (a_inv * ((letter_to_num(code)) - b)) % CharMapSize;
		
		if (code_num < 0)
		{
			code_num += CharMapSize;
		}

		new_code = num_to_letter(code_num);
	}

	return new_code;
}

/**
 * Greatest Common Denominator function
 *
 * Returns the GCD of 'a' and 'b'
 */
int gcd(int a, int b)
{
	int temp;
	while (b != 0)
	{
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}
// EoF
