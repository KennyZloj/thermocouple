#include <stdio.h>
#include <math.h>
#include <errno.h>

const long double polinom1 [9] = {472.418020L, 37.684494L, 7.472018L, 2.920828L, 0.005184L, -0.963864L, -0.188732L, 0.191203L, 0.049025L};
const long double polinom2 [15] = {0.240975303L, 0.209108771L, 0.190439972L, 0.142648498L, 0.077993465L, 0.012475611L, -0.032267127L, -0.075291522L, -0.056470670L, 0.076201285L, 0.123893204L, -0.029201193L, -0.091173542L, 0.001317696L, 0.026025526L};
const long double Dn = 439.932854L, Bn = 0.183324722L, S = 1.00L / 6.00L;
long double Rtt, a, b, M;
unsigned char f = 1, mode;
long double  Rt;
char name[30], serialnumber[30];

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
		printf ("\nВведи измеренное значение сопротивления Rt, в Омах, 0 для выхода\n\n");
		res = scanf ("%Lf", &Rt);
			if (res != 1) {
			printf ("\nОшибка ввода\n\n");
			//fscanf(stdin, "%*[^\n]%*c");
			flushkeyboard();
			}
		} while (res != 1);
		/*printf ("\nВведи измеренное значение сопротивления Rt, в Омах, 0 для выхода\n\n");
		res = scanf ("%Lf", &Rt);*/

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

void flushkeyboard(void)
{	
	int ch;
	while((ch = getc(stdin)) != EOF && ch != '\n');
}
