#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 21

int* insuccesso(char * pattern);
int KMP_match(char * string, char * pattern);
int KMP_match_cyclic_rotation(char * string, char * pattern);

int main(void){
	char string[STRING_SIZE];
	char pattern[STRING_SIZE];
	printf("KMP - Pattern Matching");

	printf("\nInsert a string : ");
	scanf("%s", string);

	printf("Insert a pattern : ");
	scanf("%s", pattern);

	int res = KMP_match(string, pattern);
	int c_res = KMP_match_cyclic_rotation(string, pattern);

	if(!res)
		printf("It's a match! (%d)\n", res);
	else
		printf("No match found (%d)\n", res);

	if(c_res!= -1)
		printf("Pattern it's a cyclic rotation (%d)\n", c_res);
	else
		printf("Pattern isn't a cyclic rotation (%d)\n", c_res);
	return 0;
}

int* insuccesso(char * pattern){
	int j, i;
	int n = strlen(pattern);
	int * vector = (int*)malloc(sizeof(int) * n);

	if(vector == NULL)
		exit(-1);

	vector[0] = -1;

	for(j = 1 ; j < n; j++){
		i = vector[j-1];
		while(pattern[j] != pattern[i+1] && i >= 0){
			i = vector[i];
		}

		vector[j] = (pattern[j] == pattern[i+1]) ? i+1 : -1; 
		
	}
	return vector;
}

int KMP_match(char * string, char * pattern){
	int * vector = insuccesso(pattern);

	int i = 0, j = 0;
	int lenS = strlen(string);
	int lenP = strlen(pattern);

	printf("\nInsuccesso : ");
	for(int k = 0; k < lenP; k++)
		printf("%d ", vector[k]);
	printf("\n");
	while(i < lenS && j < lenP){
		if(string[i] == pattern[j]){
			i++; j++;
		}else if(j == 0)
			i++;
		else
			j = vector[j - 1]+1;
	}

	return (j == lenP) ? i-lenP : -1;
}
int KMP_match_cyclic_rotation(char * string, char * pattern){
	if(strlen(string) != strlen(pattern))
		return -1;

	int * vector = insuccesso(pattern);
	int i = 0, j = 0;
	int lenS = strlen(string);
	int lenP = strlen(pattern);

	while(i < lenS && j < lenP){
		if(string[i] == pattern[j]){
			i++; j++;
			if(i >= lenS)
				i = 0;
		}
		else if(j == 0)
			i++;
		else
			j = vector[j - 1]+1;
	}

	return (j == lenP) ? i-lenP : -1;	
}