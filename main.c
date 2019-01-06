/*
 * main.c
 *
 *  Created on: 6. 1. 2019
 *      Author: tichy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MDEFAULT 'd'
#define TEXTFILENAME "data.txt"
#define ALPHABET	"alphabet.txt"
#define OUTPUT		"output.txt"

struct buff{
	char * string;
	unsigned int size;
};
typedef struct buff buff;

char kas_mode_selected()
{
	return getchar();
}

//------------------------BUFFER------------------------------

buff * create_buffer()
{
	buff * buffer = (buff*) malloc(sizeof(buff));
	buffer->size = 0;
	buffer->string = "";
	return buffer;
}

void print_buffer(buff * buffer)
{
	int i;
	for(i = 0; i < buffer->size; i++)
	{
		printf("%c", buffer->string[i]);
	}
	printf("\n");
}

unsigned char * read_text(char * file_name)
{
	FILE *fr;
	unsigned char *buffer;
	unsigned char c[1000];

	fr = fopen(file_name,"r");
	if(!fr)
	{
		fprintf(stderr, "Unable to open file %s", file_name);
		exit(1);
	}

	fscanf(fr,"%[^\n]", c);

	buffer = c;
	printf("\n buffer size: %d\n", sizeof(buffer));
	//printf("Data from the file:\n%s", c);
	//printf("Data from the file:\n%s", buffer->string);

	fclose(fr);
	return buffer;
}


buff * read_text_file(char * file_name)
{
	FILE *fr;
	buff *buffer = create_buffer();
	char c[1000];

	fr = fopen(file_name,"r");
	if(!fr)
	{
		fprintf(stderr, "Unable to open file %s", file_name);
		exit(1);
	}

	fscanf(fr,"%[^\n]", c);

	buffer->string = c;
	buffer->size = strlen(c);
	printf("\n buffer size: %d\n", buffer->size);
	//printf("Data from the file:\n%s", c);
	//printf("Data from the file:\n%s", buffer->string);

	fclose(fr);
	return buffer;
}

int read_number_of_alphabet(char * alphabet_file)
{
		FILE *source;
		static int n;

		source = fopen(alphabet_file, "r+b");
		fseek(source, 0, SEEK_SET);

		// selecte number of alphabet
		n = fgetc(source);
		if (n<='9')
		{
			n = n - '0';
			printf("number of alphabet (%d)\n", n);
		}
		else
		{
			printf("Bad nubmer of alphabet\n");
		}
		return n;
}

void read_alphabet(char * alphabet_file, int number_of_alphabet, char buffer[])
{
	FILE *source;
	int i, c;
	int n = (int)number_of_alphabet;

	source = fopen(alphabet_file, "r+b");

	fseek(source, 1,SEEK_SET);

	if (source != NULL) {
		for (i = 0; i < n*64; i++) {
			c = fgetc(source); // Get character
			buffer[i] = c; // Store characters in array
			//printf("Result A: %X\n", c);
		}
	} else {
	       printf("File not found.\n");
	}
	fclose(source);

	/* Add null to end string */
	buffer[i] = '\0';
}

void generate_alphabet()
{
	char c;
	for(c = 'a'; c <= 'z'; ++c)
	{
		printf("%c", c);
	}
	for(c = 'A'; c <= 'Z'; ++c)
	{
		printf("%c", c);
	}
	for(c = '0'; c <= '9'; ++c)
	{
		printf("%c", c);
	}
}

void kas_read_file(char * file_name)
{
	FILE *fr;
	char x;

    printf("Enter name of a file you wish to see\n");
	fr = fopen(file_name,"r");

	while((x = getc(fr)) != '\n')
		putchar(x);

	fclose(fr);
}

void crypt_file(char array[], int array_size, char alphabet_buffer[], int number_of_alphabet)
{
//	buff * buffer = text_buffer;
	int row = number_of_alphabet;
	int col = strlen(alphabet_buffer)/number_of_alphabet;
	char alphabet_table [col][row];
//	char arr[text_buffer->size] = text_buffer->string;
	// this cyclus will set alphabet into the table
	// set row
	for(int i = 0; i < row;i++)
	{
		int l = 0;
		// set col
		for(int j = 0; j < col; j++)
		{
			alphabet_table[j][i] = alphabet_buffer[j+l];
	//		printf("alphabet_table[%d][%d]=%c\n", j,i,alphabet_table[j][i]);
		}
		l += col;
	}
		int w,choose;
		char c;
		char * sifra = malloc(array_size + 1);
		for(w = 0; w < array_size; w++)
		{
//			printf("%c", array[i]);

				c = array[w];
				printf("%c", c);
			for(int y = 0; y < col; y++)
			{
				if((alphabet_table[y][0] == c))
				{
//					printf("I find your char: %d\n", c, y);
					strcpy(sifra, alphabet_table[y,1]);
					break;
				}

			}

		}
		printf("\n");

//	c = array;
//	for(int x = 0; x < array_size; x++)
//	{
//
//		printf("%d\n", *c);

//	}
}

void decrypt_file(buff * text_buffer, unsigned char alphabet_buffer)
{

}

int main()
{
	char mode = MDEFAULT;
//	char * key_file_name;
//	char * text_file_name;
//	char * output_file_name;

	char * key_file_name = ALPHABET;
	char * text_file_name = TEXTFILENAME;
	char * output_file_name = OUTPUT;
	int number = 0;
	unsigned char * alphabet;
	buff * text_buffer = create_buffer();
//	generate_alphabet();

	setbuf(stdout, NULL);
	printf("Welcome in polyalphabetic crypting app. \nPlease, select app mode (s - crypt, d - decrypt):");

	mode = kas_mode_selected();
	switch(	mode )
	{
		case 'd':
			printf("Decrypt mode activaced! \nYour choose is: %c\n", mode);
			break;
		default :
			mode = 's';
			printf("Crypt mode activaced! \nYour choose is: %c\n", mode);
			break;
	}

	setbuf(stdout, NULL);
//	printf("Please write name of alphabet file: ");
//	scanf("%s",key_file_name);
//	printf("Please write name of file: ");
//	scanf("%s", text_file_name);
//	printf("Set name of output file (or let empty for print in console): ");
//	scanf("%s", output_file_name);

	number = read_number_of_alphabet(key_file_name);
	char alphabet_buffer[number*64];
	read_alphabet(key_file_name, number, alphabet_buffer);

	for (int var = 0; var < sizeof(alphabet_buffer); ++var) {
		printf("Result B: %c\n", alphabet_buffer[var]);
	}
//	text_buffer = read_text(text_file_name);
	text_buffer = read_text_file(text_file_name);
	print_buffer(text_buffer);
//	kas_read_file(key_file_name);
//	kas_read_file(text_file_name);
	crypt_file(text_buffer->string,text_buffer->size,alphabet_buffer,number);
	getchar();


//	kas_read_file(file_name);

	return 0;
}
