/*
 * main.c
 *
 *  Created on: 6. 1. 2019
 *      Author: tichy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char kas_mode_selected()
{
	return getchar();
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

int main()
{
	char mode;
	char *file_name;
	setbuf(stdout, NULL);
	printf("Welcome in Huffmann coding app. \nPlease, select app mode (k - coding, d - decoding):");

	mode = kas_mode_selected();
	switch(	mode )
	{
		case 'k':
			printf("Code mode activaced! \nYour choose is: %c\n", mode);
			break;
		case 'd':
			printf("Decode mode activaced! \nYour choose is: %c\n", mode);
			break;
	}

	setbuf(stdout, NULL);
	printf("Please write name of file: ");
	scanf("%s",file_name);
	kas_read_file(file_name);

	return 0;
}
