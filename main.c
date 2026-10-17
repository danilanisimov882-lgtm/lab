#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define SIZE 10
#define ITEMS_COUNT 10
#define NAME_LEN 32
#define LINE_LEN 256
#define MAX_RESOURCES 100

// Название предметов
char itemNames[ITEMS_COUNT][NAME_LEN] = {
	"Empty", "Wood", "Stone", "Seeds", "Pickaxe",
	"Apple", "Torch", "Hay", "Bucket", "Meat"
};
// Время
int current_day = 1;
int current_hour = 8;

// Безопасный ввод целого числа
int readInt(void) {
	int number;
	int result;

	while (1) {
		result = scanf("%d", &number);

		if (result == 1) {
			while (getchar() != '\n');
			return number;
		}
		if (result == EOF) {
			return 0;
		}
		printf("Error. Enter an integer: ");
		while (getchar() != '\n');
	}
}

// Удаляет переход на новую строку в конце текста
void removeNewline(char text[]) {
	int length = strlen(text);
	if (length > 0 && text[length - 1] == '\n') {
		text[length - 1] = '\0';
	}
}

// Загружает названия предметов из items.txt
void loadItemNames(void) {
	FILE* file = fopen("items.txt", "r");
	int id;
	char name[NAME_LEN];

	if (file == NULL) {
		printf("File items.txt not found. Using default English names.\n");
		return;
	}

	while (fscanf(file, "%d %31s", &id, name) == 2) {
		if (id >= 0 && id < ITEMS_COUNT) {
			strcpy(itemNames[id], name);
		}
	}
	fclose(file);
}

// Показать инвентарь
void showInventory(int inventory[]) {
	int i;
	printf("\n=== ИНВЕНТАРЬ ===\n");
	for (i = 0; i < SIZE; i++) {
		printf("Слот %d: [%d] %s\n", i, inventory[i], itemNames[inventory[i]]);
	}
}

// Показать текущее время
void showTime(void) {
	printf("Current time: Day %d, %02d:00\n", current_day, current_hour);
}
// Перемотать время
void work(void) {
	int hours;

	printf("How many hours to work? ");
	hours = readInt();

	if (hours < 0) {
		printf("The number of hours cannot be negative.\n");
		return;
	}
	current_hour += hours;
	current_day += current_hour / 24;
	current_hour = current_hour % 24;

	showTime();
}
//  Положить предмет в слот
void addItem(int inventory[]) {
	int slot, id;

	printf("Enter the slot number (0-9): ");
	slot = readInt();

	if (slot < 0 || slot >= SIZE) {
		printf("There is no such slot.\n");
		return;
	}
	printf("Enter the item ID (0-9): ");
	id = readInt();
	if (id < 0 || id >= ITEMS_COUNT) {
		printf("There is no such item.\n");
		return;
	}
	inventory[slot] = id;
	printf("Item added to slot %d.\n", slot);
}
// Выбросить предмет
void dropItem(int inventory[]) {
	int slot;

	printf("Enter the slot number(0-9): ");
	slot = readInt();

	if (slot < 0 || slot >= SIZE) {
		printf("There is no such slot.\n");
		return;
	}
	inventory[slot] = 0;
	printf("Slot %d cleared.\n", slot);
}
// Перевернуть инвентарь
void reverseInventory(int inventory[]) {
	int i, temp;

	printf("Inventory before reversing:\n");
	showInventory(inventory);

	for (i = 0; i < SIZE / 2; i++) {
		temp = inventory[i];
		inventory[i] = inventory[SIZE - 1 - i];
		inventory[SIZE - 1 - i] = temp;
	}
	printf("\nInventory after reversing:\n");
	showInventory(inventory);
}

// Ищет предмет по названию
void searchItem(int inventory[]) {
	char name[NAME_LEN];
	int id = -1;
	int i;
	int found = 0;

	printf("Enter the item name: ");
	fgets(name, sizeof(name), stdin);
	removeNewline(name);

	for (i = 0; i < ITEMS_COUNT; i++) {
		if (strcmp(name, itemNames[i]) == 0) {
			id = i;
			break;
		}
	}

	if (id == -1) {
		printf("There is no such item in the catalog.\n");
		return;
	}

	for (i = 0; i < SIZE; i++) {
		if (inventory[i] == id) {
			printf("Item found in slot %d.\n", i);
			found = 1;
		}
	}

	if (found == 0) {
		printf("The item is in the catalog, but not in the inventory.\n");
	}
}

// Записывает текущее состояние фермера в дневник
void saveDiary(char farmerName[], int inventory[]) {
	FILE* file = fopen("diary.txt", "a");
	int i;

	if (file == NULL) {
		printf("	Failed to open diary.txt\n");
		return;
	}

	fprintf(file, "	Farmer's diary: %s\n", farmerName);
	fprintf(file, "Day %d, time %02d:00\n", current_day, current_hour);
	fprintf(file, "	Inventory:\n");
	for (i = 0; i < SIZE; i++) {
		fprintf(file, "Slot %d: %s\n", i, itemNames[inventory[i]]);
	}
	fprintf(file, "-------------------------\n");
	fclose(file);
	printf("	Entry saved to diary.txt\n");
}

// Суммирует одинаковые ресурсы из input.txt
void countResources(void) {
	FILE* input = fopen("input.txt", "r");
	FILE* output;
	char names[MAX_RESOURCES][NAME_LEN];
	int amounts[MAX_RESOURCES];
	char name[NAME_LEN];
	char line[LINE_LEN];
	int amount;
	int count = 0;
	int i, found;
	int badLines = 0;

	if (input == NULL) {
		printf("Failed to open input.txt.\n");
		return;
	}

int main(void) {

	int inventory[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int choice;

	while (1) {
		printf("\n=== FARMER MENU ===\n");
		printf("[1] View time\n");
		printf("[2] Skip time\n");
		printf("[3] View inventory\n");
		printf("[4] Put item\n");
		printf("[5] Drop item\n");
		printf("[6] Reverse pockets\n");
		printf("[0] Exit\n");
		printf("Your choice: ");

		choice = readInt();

		switch (choice) {
		case 1:
			showTime();
			break;

		case 2:
			work();
			break;

		case 3:
			showInventory(inventory);
			break;

		case 4:
			addItem(inventory);
			break;

		case 5:
			dropItem(inventory);
			break;

		case 6:
			reverseInventory(inventory);
			break;

		case 0:
			printf("Program terminated.\n");
			return 0;

		default:
			printf("Invalid menu item.\n");
		}
	}
	return 0;
}