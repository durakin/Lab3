#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
	double* content;
	int razmer;
	double srznach;
	bool isFilled;
} object;

int VDCelPol(char name[100])
{
	int i, done = 0;
	char s[100];
	printf("Введите значение %s\n", name);
	while (done == 0)
	{
		for (i = 0; i < 99; i++)
		{
			s[i] = 0;
		}

		scanf("%s", s);

		i = 0;

		while (s[i] > 0)
		{
			if (!(s[i] >= '0'  && s[i] <= '9') || (s[i] == '0' && i == 0))
			{
				//system("cls");
				printf("Некорректное значение. Пожалуйста, повторите ввод %s.\n", name);
				break;
			}
			i++;
		}
		if (s[i] <= 0) done++;
	}
	return atoi(s);
}

double VDVesh(int iname, int jname)
{
	int i, zapyat, done = 0;
	char s[100];
	printf("Введите значение элемента массива с индексом %d %d\n", iname, jname);
	while (done == 0)
	{
		zapyat = 0;

		for (i = 0; i < 99; i++)
		{
			s[i] = 0;
		}

		scanf("%s", s);

		i = 0;

		if (s[0] == '-') i++;

		while (s[i] > 0)
		{
			if (s[i] == '.') zapyat++;
			if (!(s[i] >= '0'  && s[i] <= '9') && s[i] != '.' || s[i] == '.' && zapyat > 1)
			{
				printf("Некорректное значение элемента массива. Пожалуйста, повторите вводэлемента массива с индексом %d %d.\n", iname, jname);
				break;
			}
			i++;

		}
		if (s[i] <= 0) done++;
	}
	return atof(s);
}

void Customfill(object* obj)
{
	if (obj->isFilled)
	{
		free(obj->content);
		obj->srznach = 0;
	}
	obj->razmer = VDCelPol("размера квадратного массива");
	obj->content = (double*)malloc(obj->razmer * obj->razmer * sizeof(double));
	for (int i = 0; i < obj->razmer; i++)
	{
		for (int j = 0; j < obj->razmer; j++)
		{
			obj->content[i*obj->razmer + j] = VDVesh(i, j);
			if (j == obj->razmer - 1 - i)
			{
				obj->srznach += obj->content[i*obj->razmer + j];
			}
		}
	}
	obj->isFilled = true;
	obj->srznach /= obj->razmer;
}

void RandomFill(object* obj)
{
	srand((unsigned)time(NULL));
	if (obj->isFilled)
	{
		free(obj->content);
		obj->srznach = 0;
	}
	obj->razmer = VDCelPol("размера квадратного массива");
	obj->content = (double*)malloc(obj->razmer * obj->razmer * sizeof(double));
	for (int i = 0; i < obj->razmer; i++)
	{
		for (int j = 0; j < obj->razmer; j++)
		{

			obj->content[i*obj->razmer + j] = (rand() % 201) - 100;
			if (j == obj->razmer - 1 - i)
			{
				obj->srznach += obj->content[i*obj->razmer + j];
			}
		}
	}
	obj->isFilled = true;
	obj->srznach /= obj->razmer;
}

void obrabotka(object* obj)
{	
	double box = obj->srznach;
	obj->srznach = 0;
	
	for (int i = 0; i < obj->razmer; i++)
	{
		for (int j = 0; j < obj->razmer; j++)
		{
			if (i > j)
			{
				obj->content[i*obj->razmer + j] = box;
			}
			if (j == obj->razmer - 1 - i)
			{
				obj->srznach += obj->content[i*obj->razmer + j];
			}
		}
	}
	obj->srznach /= obj->razmer;
};

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	object obj;
	obj.isFilled = 0;
	obj.content = NULL;
	obj.razmer = 0;
	obj.srznach = 0;

	int k = -1, vih, n = 0;
	while (k != 6)
	{
		system("cls");
		printf("Меню пользователя:\n1. Ввести элементы массива вручную.\n2. Заполнить массив случайными числами.\n3. Вывести массив на экран.\n4. Вывести среднее арифметичиское элементов, находящихся на побочной диагонали.\n5. Заменить элементы массива, располагающиеся ниже главной диагонали, средним арифметичим элементов, находящихся на побочной диагонали.\n6. Выход.\n");
		k = VDCelPol("номера команды");
		if (k == 1)
		{
			system("cls");
			Customfill(&obj);
			system("cls");
			printf("Ввод массива завершен.\n");
		}
		if (k == 2)
		{
			system("cls");
			RandomFill(&obj);
			printf("Массив был заполнен случайными числами в диапозоне от -100 до 100.\n");
		}
		if (k == 3)
		{
			system("cls");
			if (obj.isFilled)
			{
				printf("Элементы массива:\n");
				for (int i = 0; i < obj.razmer; i++)
				{
					for (int j = 0; j < obj.razmer; j++)
					{
						printf("%f ", obj.content[i*obj.razmer + j]);
					}
					printf("\n");
				}

			}
			else
			{
				printf("Массив не был заполнен.\n");
			}
		}
		if (k == 4)
		{
			system("cls");
			printf("Среднее арифметичиское элементов, находящихся на побочной диагонали равно %f\n", obj.srznach);
		}
		if (k == 5)
		{
			system("cls");
			if (obj.isFilled)
			{
				obrabotka(&obj);
				printf("Массив был обработан.\n");
			}
			else
			{
				printf("Массив до сих пор не был заполнен.\n");
			}
		}
		if (k != 6)
		{
			getchar();
			getchar();
		}
	}
}