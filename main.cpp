#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void createFile(int amount, int type) {
	FILE* input = fopen("in.csv", "w");
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

void scanFile(int arr[], int amount) {
	FILE* input = fopen("in.csv", "r");

	for (int i = 0; i < amount; i++)
		fscanf(input, "%d\n", &arr[i]);

	fclose(input);
}

void writeFile(int arr[], int amount) {
	FILE* output = fopen("out.csv", "w");

	for (int i = 0; i < amount; i++)
		fprintf(output, "%d\n", arr[i]);

	fclose(output);
}

static int counter = 0;

int sort(int arr[], int fst, int lst) {

	int index = fst;
	int temp;

	for (int i = fst; i < lst; i++) {
		if (arr[i] <= arr[lst]) {
			if (arr[i] != arr[index])
			{
				counter++;
				temp = arr[i];
				arr[i] = arr[index];
				arr[index] = temp;
			}
			index++;
		}
	}
	temp = arr[lst];
	arr[lst] = arr[index];
	arr[index] = temp;
	counter++;
	return index;
}


void quick(int arr[], int fst, int lst) {


	if (fst >= lst)
		return;

	int index = sort(arr, fst, lst);

	quick(arr, fst, index - 1);
	quick(arr, index + 1, lst);
}

void start() {
	int type = 4;
	int size = 1;
	int *arr;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Введите кол-во элементов: ");
	scanf("%d", &size);
	do {
		printf("1 - случайный\n2 - отсортированный\n3 - в обратном порядке\nВыберите вид входного массива : ");
		scanf("%d", &type);
	} while (type > 3 && type < 1);

	arr = (int*)malloc(size * sizeof(int));

	createFile(size, type);
	scanFile(arr, size);

	clock_t start = clock();

	quick(arr, 0, size - 1);

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;

	writeFile(arr, size);
	free(arr);
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
