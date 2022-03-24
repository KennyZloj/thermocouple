#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>

const long double polinom1 [9] = {472.418020L, 37.684494L, 7.472018L, 2.920828L, 0.005184L, -0.963864L, -0.188732L, 0.191203L, 0.049025L};
const long double polinom2 [15] = {0.240975303L, 0.209108771L, 0.190439972L, 0.142648498L, 0.077993465L, 0.012475611L, -0.032267127L, -0.075291522L, -0.056470670L, 0.076201285L, 0.123893204L, -0.029201193L, -0.091173542L, 0.001317696L, 0.026025526L};
const long double Dn = 439.932854L, Bn = 0.183324722L, S = 1.00L / 6.00L;
long double Rtt, a, b, M;
unsigned char f = 1, mode, angryctr = 0, wrath = 0;
long double  Rt;
char name[30], serialnumber[30], str[31];

long double thermo_pol (void);

int main(int argc, char** argv)
{
	FILE *fp;
	int res;
	int err;
	char *ptr;

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

	res = fscanf(fp, "name=%s serialnumber=%s Rtt=%Lf a=%Lf b=%Lf M=%Lf", name, serialnumber, &Rtt, &a, &b, &M);
	printf ("\n");
	printf ("Файл %s найден и прочитан\n", argv[1]);
	if (res != 6) /* нам нужно вытащить шесть значений */ {
		perror("Внутри файла хрень!\n");
		fclose(fp);
		return 0;
	}
	
	fclose(fp);

	printf ("\n");
	printf ("Термопреобразователь %s зав.№%s\n", name, serialnumber);
	printf ("Сопротивление в тройной точке Rtt= %Lf Ом\n", Rtt);
	printf ("Коэффициенты МТШ-90:\n");
	printf("a= %Lf\n", a);
	printf("b= %Lf\n", b);
	printf("M= %Lf\n", M);
	printf ("\n");
	while (f) {
	
		do {
		int cntr=0;
		err=0;
		printf ("\nВведи измеренное значение сопротивления Rt, в Омах, 0 для выхода\n\n");
		scanf ("%s", str);
			for (unsigned char i=0;i<strlen(str);i++) {
				if (str[i]==',') {
				str[i]='.';
				angryctr++;
				}
			err=1;
			if (str[i]=='.') cntr++;
			if (str[i]=='0') err=0;
			if (str[i]=='1') err=0;
			if (str[i]=='2') err=0;
			if (str[i]=='3') err=0;
			if (str[i]=='4') err=0;
			if (str[i]=='5') err=0;
			if (str[i]=='6') err=0;
			if (str[i]=='7') err=0;
			if (str[i]=='8') err=0;
			if (str[i]=='9') err=0;
			if (str[i]=='.') err=0;
			if (cntr>1) err=1;
			if (i>29) err=1;
			if (err==1) break;
			}
		if (err==1) printf ("\nОшибка ввода\n\n");		
		} while (err==1);
		
		if (angryctr > 0 && wrath == 0) {
		printf("\nОставь свои запятые в мёртвом Советском Союзе, совок!\n");
		printf("Дробная часть в десятичной дроби отделяется точкой.\n");
		wrath++;
		angryctr=0;
		}
		
		if (angryctr > 0 && wrath == 1) {
		printf("\nНадоел со своей запятой!\n");
		wrath++;
		angryctr=0;
		}
		
		if (angryctr > 0 && wrath == 2) {
		printf("\nУмный, да?\n");
		wrath++;
		angryctr=0;
		}
		
		if (angryctr > 0 && wrath == 3) {
		printf("\nХватит ставить запятую!\n");
		printf("Последнее предупреждение!\n");
		wrath++;
		angryctr=0;
		}
		
		if (angryctr>0 && wrath > 3) {
			for (unsigned char i=0;i<100;i++) {
			printf("ОШИБКА ОШИБКА ОШИБКА ОШИБКА ОШИБКА ОШИБКА ОШИБКА ОШИБКА ОШИБКА\n");
			printf("ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n");
			}
		printf("Машинка ругается\n");
		printf("Доволен?\n");
		return 0;
		}
		
		
		Rt=strtold(str, &ptr);

		if (Rt >= 50.000L && Rt <= 300.000L) mode = 0;
		if (Rt < 50.000L || Rt > 300.000L) mode = 1;
		if (Rt == 0) mode = 2;

		switch (mode)
		{
		case 0:
			printf ("\nТемпература= %5.3Lf °С\n\n", thermo_pol());
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
	long double g, W, Wr, t;

	g = 0;
	t = 0;
	Wr = 0;
	W = Rt / Rtt;

	if (Rt >= Rtt && Rt <= 300.000L) {
		Wr = W - (a * (W - 1.00L) + b * pow((W - 1.00L),2));
		for (i=0;i<9;i++) {
			g = polinom1[i] * pow((Wr - 2.64L) / 1.64L, i+1);
			t = t + g;
		}

		t = t + Dn;
	}	
	
	if (Rt >= 50.000L && Rt < Rtt) {
		Wr = W - (M * (W - 1.00L));
		for (i=0;i<15;i++) {
			g = polinom2[i] * pow((pow(Wr,S) - 0.65L) / 0.35L, i+1);
			t = t + g;
		}

		t = ((t + Bn) * 273.16L) - 273.15L;
	}

	return t;
}
