/**
 *	CSE 4471 - Information Security
 *
 * 	Evan Adamic, Rebecca Hu, Jeffrey Jagger, 
 * 	Abdikarim Mohamed, Catherine Wang
 *
 *	Symmetric encryption/decryption for two-factor authenication 
 *	codes stored in the database.
 *
 *	Command line:
 *		./encryption <code> <key>
 *
 *	<code>:	the authentication code to encrypt/decrypt
 *	<key>:	the private key
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
//#include "ciphers.h"

const int MaxNumArgs 		= 3;
const char* ArgCountError 	= "Invalid arg count";
const char* ArgError		= "Invalid args";
const int ModAlph		= 27;
const int ModDec		= 11;


//TODO this is for testing //***********************************************
const char* InvalidResult 	= "Error decrypting input";
void validateResults(char* plaintext_input, char* encrypted_input, int key);
//**************************************************************************


/**
 * Function prototypes
 */
char* encrypt(char* code, int key);
char xorCipher(char code, int key);
char rot14Cipher(char code);
char blockCipher(char code, int key);
char affineCipher(char code, int key, int index);


/**
 * Main function
 */
int main(int argc, char* argv[])
{
	int i;
	char* input;
	int key;
	char* encrypted_input;

	// Check arg count
	if (argc != MaxNumArgs) 
	{
		printf("Encryption.c::main\n\t%s\n", ArgCountError);
		printf("%i:", argc);
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
		printf("Encryption.c::main\n\t%s\n", ArgError);
		exit(-1);
	}
	
	// Second arg should be key int
	key = atoi(argv[2]);
	if (key == 0)
	{
		printf("Encryption.c::main\n\t%s\n", ArgError);
		exit(-1);
	}


	
	printf("Code: %s\n", input);
	printf("Key: %i\n", key);
	printf("Key %% 26: %i\n", key%26);

	// Encrypt input
	encrypted_input = encrypt(input, key);
	printf("Encrypted input: %s\n", encrypted_input);


	/*
	 * TODO
	 * this is for testing
	 */
	validateResults(input, encrypted_input, key);

	/* TODO
	 * Main cannot return a value
	 * must either scan results from output stream
	 */
	printf("%s\n", argv[MaxNumArgs-1]);
	argv[MaxNumArgs-1] = encrypted_input;
	printf("%s\n", argv[MaxNumArgs-1]);	
}


/**
 * TODO this is for testing
 * Test method to validate symmetric encryption/decryption
 * ************************************************************************************
 */
void validateResults(char* input, char* encrypted_input, int key) 
{
	bool isValid = true;
	char* decrypted_input;

	// Decrypt input
	decrypted_input = encrypt(encrypted_input, key);
	if (strlen(decrypted_input) == strlen(input))
	{
		int i = 0;
		for (i = 0; i < strlen(input); i++)
		{
			if (decrypted_input[i] != input[i])
			{
				isValid = false;
				printf("%c >> %c\n", \
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
//************************************************************************************


/**
 * Encrypt/decrypt function
 */
char* encrypt(char* code, int key)
{
	char* new_code = malloc(sizeof(char*));
	strcpy(new_code, code);
	int i;

	for (i = 0; i < strlen(code); i++)
	{
		new_code[i] = xorCipher(code[i], key);
	}
	return new_code;
}


/**
 * XOR Cipher
 */
char xorCipher(char code, int key) 
{
	return code^(key % ModAlph);
}


/**
 * Rot13 Cipher
 */
char rot13Cipher(char code)
{
	char new_code;
	int rot13 = 13, rot5 = 5;
	
	/*
	 * Authenication codes can only be 0-9, A-Z, a-z
	 */
	if (code >= 'A' && code <= 'Z')
	{
		new_code = ((code + rot13) % ('A' + ModAlph));
		if (new_code < 'A')
		{
			new_code += 'A';
		}
	}
	else if (code >= 'a' && code <= 'z')
	{
		new_code = ((code + rot13) % ('a' + ModAlph));
		if (new_code < 'a')
		{
			new_code += 'a';
		}
	}
	else if (code >= '0' && code <= '9')
	{
		new_code = ((code + rot5) % ('0' + ModDec));
		if (new_code < '0')
		{
			new_code += '0';
		}
	}
	else
	{
		printf("encryption.c::rot13\n\tinvalid code\n");
		printf("%c\n", code);
		exit(-1);
	}	

	return new_code;
}


/**
 * Block Cipher
 */
char blockCipher(char code, int key)
{
	int num = letter_to_num(code);

	return charMap[num];
}

/**
 * Affine Cipher
 */
char affineCipher(char code, int key, int index)
{
	char new_code = code;

	
	return new_code;
}
