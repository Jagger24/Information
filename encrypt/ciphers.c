/*
 * Evan Adamic, Rebecca Hu, Jeffrey Jagger, 
 * 	Abdikarim Mohamed, Catherine Wang
 * CSE 4471
 * Last update: 4/17/18
 */

#include "ciphers.h"

/*
 *	CharMap is used to map alphanumeric characters to their
 * corresponding index base 26+26+10 = 62
 */
const char* CharMap = \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int LowercaseIndex = 0;
const int UppercaseIndex = 26;
const int NumIndex 	= 52;
const int CharMapSize	= 62;

/*
 * 	BlockCharMap is used to map alphanumeric character from
 * CharMap to their encrypted character value.
 * 	*NOTE* 
 * 	This block encoding is completely arbitrary and can be modified
 * or randomly generated so long as there is a 1-to-1 mapping of alpha-
 * numeric characters.
 */
const char* BlockCharMap = \
	"bnztFRL0WgamysEQKV19fhlxrDPJU28eqkwICOZT37dpjvHBNYS46coiuGAMX5";

/*
 * 	Functions for ease of converting the index number of an alpha-
 * numeric character in CharMap to the character itself and 
 * back again
 */
char num_to_letter(int num)
{
	return CharMap[num];
}

int letter_to_num(char letter)
{
	int num = 0;
	while (CharMap[num] != letter)
	{
		num++;
	}
	return num;
}
