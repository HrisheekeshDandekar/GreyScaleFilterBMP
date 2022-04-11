/*
 *    Code to take in a BMP name in the same directory as a command line argument to main
 *
 *    PSUDO CODE:
 *      >  Open file
 *      >  Open another file wtih _bw as a suffix
 *      >  Make sure it is an BMP file
 *      >  Locate bitmap starting pos
 *      >  Apply formula to each pixal and rewrite pixals till the end
 *      >  Flash error / success msg
 *      >  Close both files
 *      >  exit
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool arguments_to_main_validation (int argc, char** argv);
bool open_files (FILE* original, FILE* to_create, char* original_name);
char* new_file_name (char* original_name);
bool file_is_bmp (FILE* fp);
long bitmap_start (FILE* fp);
long bitmap_end (FILE* fp);
bool apply_greyscale (FILE* fp);
void status_printed ();

typedef struct Errors {
	int fopen_original;
	int fopen_final;
	int filter_application_failure;
	int fclose_original;
	int fclose_final;
	int arguments_err;
	int arg_name_err;
	int fopen_new;
	
	char msgs[8][100];
} Error_msgs;

Error_msgs code_errors = {
		.fopen_original = 0,
		.fopen_final = 0,
		.filter_application_failure = 0,
		.fclose_original = 0,
		.fclose_final = 0,
		.arguments_err = 0,
		.arg_name_err = 0,
	
		.msgs[0] = "---[ Error Opening original image ]---\n",		
		.msgs[1] = "---[ Error createing file with suffix _bw ]---\n(make sure file does not exist)\n",		
		.msgs[2] = "---[ Failed to apply Fileter ]---\n",		
		.msgs[3] = "---[ Error closing original file ]---\n",		
		.msgs[4] = "---[ Error closing created file ]---\n"
		.msgs[5] = "---[ Wrong arguments passed ]---\nUsage: ./program_name image_name.bmp\n"
		.msgs[6] = "---[ Bad name passed ]---\nUsage: ./program_name image_name.bmp\n"
		.msgs[7] = "---[ Could not create new output file ]---\n"
	};

 
int main(int argc, char** argv)
{
	//Print the correct error/success msg whenever program exits
	atexit(status_printed);

	//Correct arguments passed to the program
	if (!arguments_to_main_validation(argc, argv))		{ return 1; }

	FILE* original;
	FILE* to_create;

	if (!open_files(original, to_create, argv[1]))		{ return 1; }
		
	if (!file_is_bmp(original))							{ return 1; } 

	if (!apply_greyscale(original))						{ return 1; }

	return 0;
}

bool arguments_to_main_validation(int argc, char** argv)
{
	//Argc needs to be 2, first argv is the exe name, 2nd is the img name
	if (argc != 2) 
	{
		code_errors.arguments_err = 1;
		return false;
	}
		
	//If wrong arguments passed, set correct flags
	if (!strcmp(argv[strlen(argv[1]) - 4], ".bmp"))
	{
		code_errors.arg_name_err = 1;
		return false;
	}

	return true;
}

bool open_files(FILE* original, FILE* to_create, char* original_name)
{
	//Check if file exists
	original = fopen(original_name, "rb");
	if (!original)
	{
		code_errors.fopen_original = 1;
		return false;
	}

	//Check and open open to_create file with added suffix
	char* output_file_name = new_file_name(original_name);
	to_create = fopen(output_file_name, "rb");
	if (!to_create)
	{
		code_errors.fopen_final = 1;
		return false;
	}
	fclose(to_create);

	//Create a blank file for output
	to_create = fopen(output_file_name, "wb")
	if (!to_create)
	{
		code_errors.fopen_new = 1;
		return false;
	}

}

char* new_file_name (char* original_name)
{
    //Add suffix _bx by creating new char array with original size +2 len
    char* new_name;
    new_name = (char*)malloc((strlen(original_name) + 3) * sizeof(char));

    //Copying as it is
    strcpy(new_name, original_name);

    //Adding suffix
    strcpy(&new_name[strlen(new_name) - 4], "_bm.bmp");

    return new_name;
}

bool file_is_bmp (FILE* fp)
{
	//check if the file is actually an bmp file
	
	//If not , set the correct error codes and return false
}

long bitmap_start (FILE* fp)
{
	//Return address of the bitmap start position as a long
}

long bitmap_end (FILE* fp)
{
	//Return the end address of the bitmap position as a long
}

bool apply_greyscale (FILE* fp)
{
	//Apply the greyscale filter to the whole bitmap
	//Formula : Grayscale = 0.299R + 0.587G + 0.114B.
	
	//Find bitmap size 
	//Find start position
	//Find end position
	//Itterate through the bitmap and convert every pixal
}

void status_printed()
{
	//Check for all the encountered errors in the error structure and print the corresponding 
	//message 
}

