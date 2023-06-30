#include <windows.h>
#include <stdio.h>
#include <time.h>
void createFile(int amount, int type) {
	FILE* input = fopen("in.txt", "w");
	switch (type) {
	case 1:
		srand(time(NULL));
		for (int i = 0; i < amount; i++)
			fprintf(input, "%d\n", (rand() % 2001) - 1000);
		break;
	case 2:
		for (int i = 0; i < amount; i++)
			fprintf(input, "%d\n", i);
		break;
	case 3:
		int k = amount;
		for (int i = 0; i < amount; i++) {
			fprintf(input, "%d\n", k);
			k--;
		}
		break;
	}
	fclose(input);
}

void scanFile(int mas[], int amount) {
	FILE* input = fopen("in.txt", "r");

	for (int i = 0; i < amount; i++)
		fscanf(input, "%d\n", &mas[i]);

	fclose(input);
}

void writeFile(int mas[], int amount) {
	FILE* output = fopen("out.txt", "w");

	for (int i = 0; i < amount; i++)
		fprintf(output, "%d\n", mas[i]);

	fclose(output);
}