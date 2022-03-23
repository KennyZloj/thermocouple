#include <stdio.h>
#include <math.h>
#include <errno.h>


long double a [4];
unsigned char f = 1, mode;
long double R;
char name[30];

long double thermo_pol (void);
void flushkeyboard(void);

int main(int argc, char** argv)
{
	FILE *fp;
	int res;

	if (argc != 2) {
		perror("Подайте название файла ради Христа!\n");
		return EINVAL;
	}

	fp = fopen(argv[1], "r");
	if (!fp) {
		//int err = errno;
		perror("Ошибка открытия файла!\n");
		//return err;
		return ENOENT;
	}

	res = fscanf(fp, "name=%s a0=%Lf a1=%Lf a2=%Lf a3=%Lf", name, &a[0], &a[1], &a[2], &a[3]);
	printf ("\n");
	printf ("Файл %s найден и прочитан\n", argv[1]);
	if (res != 5) /* нам нужно вытащить пять значений */ {
		perror("Внутри файла хрень!\n");
		fclose(fp);
		return 0;
	}
	
	fclose(fp);

	printf ("\n");
	printf ("Термопреобразователь %s\n", name);
	printf ("Коэффициенты уравнения Стейнхарта-Харта:\n");
	printf("a0= %1.9Le\n", a[0]);
	printf("a1= %1.9Le\n", a[1]);
	printf("a2= %1.9Le (обычно он принимается нулевым)\n", a[2]);
	printf("a3= %1.9Le\n", a[3]);
	printf ("\n");
	while (f) {

		do {
		printf ("\nВведи измеренное значение сопротивления NTC, в Омах, 0 для выхода\n\n");
		res = scanf ("%Lf", &R);
			if (res != 1) {
			printf ("\nОшибка ввода\n\n");
			//fscanf(stdin, "%*[^\n]%*c");
			flushkeyboard();
			}
		} while (res != 1);
		/*printf ("\nВведи измеренное значение сопротивления Rt, в Омах, 0 для выхода\n\n");
		res = scanf ("%Lf", &R);*/

		if (R >= 1.0L && R <= 2e7L) mode = 0;
		if (R < 1.0L || R > 2e7L) mode = 1;
		if (R == 0) mode = 2;

		switch (mode)
		{
		case 0:
			printf ("\nТемпература= %5.2Lf °С\n\n", thermo_pol());
			break;
		case 1:
			printf ("\nЗначение вне диапазона\n\n");
			break;
		case 2:
			f = 0;
			printf ("\nВыход\n\n");
		break;
		default:
		break;
		}
	}
	return 0;
}

long double thermo_pol (void)
{
	unsigned char i;
	long double g, t;

	g = 0;
	t = 0;

		for (i=0;i<4;i++) {
			g = a[i] * pow(log(R), i);
			t = t + g;
		}

		t = (1.0L/t)-273.15L;

	return t;
}

void flushkeyboard(void)
{	
	int ch;
	while((ch = getc(stdin)) != EOF && ch != '\n');
}
