#include <stdio.h>
#include <string.h>

#define max_string_size 100
#define max_pattern_size 100

int pmatch(char *string, char *pat);
void fail(char *pat);
int failure[max_pattern_size];
char string[max_string_size];
char pat[max_pattern_size];

int main() {

	FILE* fp = fopen("kmp.txt", "r");
	
	fgets(string, sizeof(string), fp);   
	fgets(pat, sizeof(pat), fp);

	fail(pat);
	printf("%d", pmatch(string, pat));

	fclose(fp);

	return 0;
}

int pmatch(char *string, char *pat)
{
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;
	}
	return ((j == lenp) ? (i - lenp) : -1);
}

void fail(char *pat)
{
	int i, n = strlen(pat);
	int j;

	failure[0] = -1;
	for (j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else failure[j] = -1;
	}
}