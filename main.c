#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 10
#define ITEMS_COUNT 10
#define NAME_LEN 32
#define LINE_LEN 256

// Название предметов
char itemNames[ITEMS_COUNT][NAME_LEN] = {
	"Пусто", "Дерево", "Камень", "Семена", "Кирка",
	"Яблоко", "Факел", "Сено", "Ведро", "Мясо"
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
		printf("Ошибка. Введите целое число: ");
		while (getchar() != '\n');
	}
}

// Показать инвентарь
void showInventory(const int inventory[]) {
	int i;
	printf("\n=== ИНВЕНТАРЬ ===");
	for (i = 0; i < SIZE; i++) {
		printf("Слот %d: [%d] %s\n",
			i, inventory[i], itemNames[inventory[i]]);
	}
}
// Показать текущее время
void showTime(void) {
	printf("Текущее время: День %d, %02d:00\n" , current_day, current_hour);
}
void work(void) {
	int hours;

	printf("Сколько часов работать? ");
	hours = readInt();

	if (hours < 0) {
		printf("Количество часов не может быть отрицательным.\n");
		return;
	}
	current_hour += hours;
	current_day += current_hour / 24;
	current_hour = current_hour % 24;

	showTime();
}
//  Положить предмет в слот
void addItem(int inventory[]) {
	int slot;
	int id;

	printf("Введите номер слота (0-9): ");
	slot = readInt();

	if (slot < 0 || slot >= SIZE) {
		printf("Такого слота нет.\n");
			return;
	}
	printf("Введите ID предмемета (0-9): ");
	id = readInt();
	if (id < 0 || id >= ITEMS_COUNT) {
		printf("Такого предмета нет.\n");
		return;
	}
	inventory[slot] = id;
	printf("Предмет добавлен в слот %d.\n", slot);
}
// Выбросить предмет
void dropItem(int inventory[]) {
	int slot;

	printf("Введите номер слота(0-9): ");
	slot = readInt();

	if (slot < 0 || slot >= SIZE) {
		printf("Такого слота нет.\n");
		return;
	}
	inventory[slot] = 0;
	printf("Слот %d очищен.\n", slot);
}
// Перевернуть инвентарь
void reverseInventory(int inventory[]) {
	int i;
	int temp;

	printf("Инвентарь до переворота:\n");
	showInventory(inventory);

	for (i = 0; i < SIZE / 2; i++) {
		temp = inventory[i];
		inventory[i] = inventory[SIZE - 1 - i];
		inventory[SIZE - 1 - i] = temp;
	}
	printf("\nИнвентарь после переворота:\n");
	showInventory(inventory);
}
int main(void) {

	int inventory[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int choice;

	while (1) {
		printf("\n=== МЕНЮ ФЕРМЕРА ===\n");
		printf("[1] Посмотреть время\n");
		printf("[2] Промотать время\n");
		printf("[3] Посмотреть инвентарь\n");
		printf("[4] Положить предмет\n");
		printf("[5] Выбросить предмет\n");
		printf("[6] Инверсия карманов\n");
		printf("[0] Выход\n");
		printf("Ваш выбор: ");

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
			printf("Программа завершена.\n");
			return 0;

		default:
			printf("Неверный пункт меню.\n");
		}
	}
	return 0;
}