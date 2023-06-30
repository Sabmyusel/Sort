#define _CRT_SECURE_NO_WARNINGS

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

int index = 0;
int* mas;
int size = 1;
int a = 0;
int type = 4;
static int counter = 0;

void sort(int mas[], int fst, int lst) {

	index = fst;
	int temp;

	for (int i = fst; i < lst; i++) {
		if (mas[i] <= mas[lst]) {
			if (mas[i] != mas[index])
			{
				counter++;
				temp = mas[i];
				mas[i] = mas[index];
				mas[index] = temp;
			}
			index++;
		}
	}
	temp = mas[lst];
	mas[lst] = mas[index];
	mas[index] = temp;
	counter++;
}


void quick(int mas[], int fst, int lst) {

	if (fst >= lst)
		return;

	sort(mas, fst, lst);

	quick(mas, fst, index - 1);
	quick(mas, index + 1, lst);
}

void start() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Введите кол-во элементов: ");
	scanf("%d", &size);
	do {
		printf("1 - случайный\n2 - отсортированный\n3 - в обратном порядке\nВыберите вид входного массива : ");
		scanf("%d", &type);
	} while (type > 3 && type > 0);

	mas = (int*)malloc(size * sizeof(int));

	createFile(size, type);
	scanFile(mas, size);


	clock_t start = clock();

	quick(mas, 0, size - 1);

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;

	writeFile(mas, size);
	free(mas);
	printf("Время выполнения %f секунд\nОпераций перестановок: %d\n", seconds, counter);

}

int main() {
	int exit = 0;
	while (exit != 1) {
		start();
		printf("1 - чтобы выйти: ");
		scanf("%d", &exit);
		system("@cls||clear");
	}
	return 0;
}