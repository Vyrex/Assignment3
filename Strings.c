#include <stdio.h>
#include <string.h>

#define TXT 1024
#define WORD 30

#define A 65
#define Z 90
#define a 97
#define z 122

#define SPC 32
#define TAB 9
#define NEWLINE '\n'

#define ENDOFTXT 126

int main() {

	char charsArr[30] = {NULL};
	char TEXT[256] = {NULL};
	int i = 0;
	char endLoop;

	scanf("%s", charsArr);

	//general helper function
	//builds short sequences array
	while (i < 256) {
		scanf("%c", &endLoop);
		TEXT[i] = endLoop;
		if (endLoop == '~') {
			break;
		}
		i++;
	}

	int initialNumericalValue = numericalValueSum(charsArr);

	char ** words = shortSequence(TEXT);
	i=0;

	//A
	while(words[i] != NULL){
		if(numericalValueSum(words[i]) == initialNumericalValue){
			printf("%s\n", words[i]);
		}
	}
	//B
	char * atbash = Atbash(charsArr);

	for(i = 0; i < 256; i++){
		if(TEXT[i] == atbash[0]){
			int j;
			int offset=0;
			for(j = 0; j<sizeof(atbash); j++){
				while(TEXT[i+j+offset]==' '){
					offset++;
				}
				//checks if each letter of both words is equal
				if(atbash[j]!=TEXT[i+j+offset]){
					break;
				}
			}
			if(j==sizeof(atbash)){
				printf("%s\n", substr(TEXT, i, i+j));
			}
		}
		if(TEXT[i] == charsArr[0]){
			int j;
			int offset=0;
			for(j = 0; j<sizeof(atbash); j++){
				while(TEXT[i+j+offset]==' '){
					offset++;
				}
				if(charsArr[j]!=TEXT[i+j+offset]){
					break;
				}

			}
			if(j==sizeof(atbash)){
				printf("%s\n", substr(TEXT, i, i+j+offset));
			}
		}
	}

	//C
	for(i = 0; i < 256; i++){
		if(strchr(charsArr,TEXT[i]) != NULL){
			int j;
			int offset=0;
			int size = sizeof(charsArr);
			size*=size+1;
			size/=2;
			for(j = 0; j<sizeof(charsArr); j++){
				while(TEXT[i+j+offset]==' '){
					offset++;
				}
				int charIndex = strchr(charsArr,TEXT[i+j+offset]);
				if(charIndex == NULL){
					break;
				}
				else{
					size -= charIndex;
				}
			}
			if(j == sizeof(charsArr) && size == 0){
				printf("%s\n", substr(TEXT, i, i+j+offset));
			}
		}
	}


	return 0;
}

//helper function for part B
char * Atbash(char word[]){
	char reverted[sizeof(word)];

	for(int i=0; i<sizeof(word); i++){
		if(word[i] > A && word[i] < Z){
			reverted[i] = Z - (word[i] - A);
		}
		else if(word[i] > a && word[i] < z){
			reverted[i] = z - (word[i] - a);
		}
		else{
			reverted[i] = word[i];
		}
	}

	return reverted;
}

//general helper function
char** shortSequence(char Arr[]) {
	char ArrSeqCheck[256][256];
	int i, j=0, k=0;
	for (i = 0; i < 256 && Arr[i] == '~'; i++) {
		if (Arr[i] == SPC || TAB || NEWLINE) {
			ArrSeqCheck[j+1][i] = ' ';
			j++;
			k=-1;
		}
		ArrSeqCheck[j][i] = Arr[i];
		k++;
	}
	ArrSeqCheck[j+1]= NULL;
	return 0;
}

//general helper function
int numericalValueSum(char Arr[]) {

	int i, sum;
	for (i = 0; i < 30; i++) {
		sum += numericalChar(Arr[i]);
	}
	return sum;
}

//helper function for A
int numericalChar(char c){
	return (c >= A && c <= Z) ?
			c - A :
			(c >= a && c<=z) ?
					c-a :
					-1;
}
