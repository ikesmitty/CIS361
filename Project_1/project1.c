#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFreq(float given[], FILE *letFreq);
void calcFreq(float found[], FILE *datafile);
char rotate(char ch, int num);
int findKey(float given[], float found[]);
void decrypt(int key, FILE *datafile, FILE *outfile);


char *letFreq;
char *inputFile;
char *outputFile;
float given[26];
float found[26];
int key;

//takes encrypted file as input along with
//letFreq.txt file
int main(int argc, char* argv[]){
	if(argc < 4){
		printf("Not enough arguments. Please enter the letter frequency file and the file you want to decrypt and it's output\n");
		return -1;
	}

	letFreq = argv[1];
	FILE *freq;
	freq = fopen(argv[1], "r");
	if(freq == NULL){
		printf("could not open frequency file.\n");
		return 1;
	}

	inputFile = argv[2];
	outputFile = argv[3];

	FILE *input = fopen(inputFile, "rb");
	if(input == NULL){
		printf("Could not find input file\n");
		exit(1);
	}

	FILE *output = fopen(outputFile, "w");
	if(output == NULL){
		printf("Could not find output file\n");
		exit(1);
	}
	readFreq(given, freq);
	calcFreq(found, input);
	findKey(given, found);
	printf("We have found our key: %d\n", key);
	FILE *final = fopen(inputFile, "rb");
	decrypt(key, final, output);
}

//Load array given with the letter frequencies for
//English from file LetFreq.txt
void readFreq(float given[], FILE *letFreq){
	char c;
	float frequency;
	char line[50];
	int x = 0;
	c = fgetc(letFreq);
	while(fgets(line, sizeof(line), letFreq) != NULL){
		sscanf(line, "%c %f", &c, &frequency);
		given[x] = frequency;
		x++;
	}
	fclose(letFreq);
}

//Read the encoded text from an input file and accumulate
//the letter frequency data for the encoded text.
void calcFreq(float found[], FILE *datafile){
	int c;
	float frequency;
	float totalCharCount = 0;
	float count[26] = {0};
	while((c=fgetc(datafile)) != EOF){
		if(c == ' '){

		}else if(isalpha(c)){
			c = tolower(c);
			if(c >= 'a' && c <= 'z')
				count[c-'a']++;
			totalCharCount++;
		}
	}
	for(int i = 0; i < 26; i++){
		frequency = count[i]/totalCharCount;
		found[i] = frequency;
	}
	fclose(datafile);
}

//Rotate the character in parameter ch down the alphabet
//for the number of positiosn as given in parameter num
//and return the resulting character
char rotate(char ch, int num){
	if(num < 0)
		num = num + 26;

	if(isupper(ch))
		return (ch - 'A' + num) % 26 + 'A';

	if(islower(ch))
		return (ch - 'a' + num) % 26 + 'a';

	return ch;
}

//Compare the data in array found with the frequency
//data in array given, looking for a key that will give
//you the best match.
int findKey(float given[], float found[]){
	float temp;
	float tempdiff;
	float totaldiff = 100000.00;
	for(int i = 0; i < 26; i++){
		moveArray(found, 1);
		for(int x = 0; x < 26; x++){
			if(given[x] > found[x]){
				tempdiff += given[x] - found[x];
			}else{
				tempdiff += found[x] - given[x];
			}
		}
		if(tempdiff < totaldiff){
			totaldiff = tempdiff;
			key = i+1;
		}
		tempdiff = 0;
	}
}

//Move array one spot to the left
void moveArray(float data[], int shift){
	int i, j;
	int n = 26;
	float tmp;
	for (i = 0; i < shift; i++) {
							 tmp = data[0];
							 for (j = 1; j <= n - 1; j++) {
											 data[j - 1] = data[j];
							 }
							 data[n - 1] = tmp;
			 }
}

//Decrypt the encoded text in the input file using the key
//and display the decoded text
void decrypt(int key, FILE *datafile, FILE *outfile){
	int c;
	key = -key;
	printf("Here is our decrypted file.\n");
	while((c=fgetc(datafile)) != EOF){
		fprintf(outfile, "%c", rotate(c, key));
		printf("%c", rotate(c, key));
	}
	fclose(datafile);
}
