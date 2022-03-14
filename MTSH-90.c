
#include <stdio.h>
#include <math.h>
#include <errno.h>

const long double polinom1 [9] = {472.418020L, 37.684494L, 7.472018L, 2.920828L, 0.005184L, -0.963864L, -0.188732L, 0.191203L, 0.049025L};
const long double polinom2 [15] = {0.240975303L, 0.209108771L, 0.190439972L, 0.142648498L, 0.077993465L, 0.012475611L, -0.032267127L, -0.075291522L, -0.056470670L, 0.076201285L, 0.123893204L, -0.029201193L, -0.091173542L, 0.001317696L, 0.026025526L};
const long double Dn = 439.932854L, Bn = 0.183324722L, a = -0.002181L, b = 0.000080L, M = -0.002194L, Rtt = 100.00315L, S = 1.00L / 6.00L;
unsigned char f = 1, mode;
long double  Rt;

long double thermo_pol (void);

int main(int argc, char** argv)
{
	FILE *fp;
	int res;
	float pi;

	if (argc != 2) {
		perror("Подайте название файла ради Христа!\n");
		return EINVAL;
	}

	fp = fopen(argv[1], "r");
	if (!fp) {
		int err = errno;
		perror("Ошибка открытия файла!\n");
		return err;
	}

	res = fscanf(fp, "PI=%f", &pi);
	if (res != 1) /* нам нужно вытащить одно значение */ {
		perror("Внутри файла хрень!\n");
		fclose(fp);
	}

	printf("PI = %f", pi);

	fclose(fp);
	printf ("\n");
	printf ("Файл найден и открыт\n");
	printf ("\n");
	printf ("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf ("Перерасчёт актуален до 3 сентября 2019 г. для ПТСВ-5-3 зав.№080.\n");
	printf ("Далее необходимо откорректировать исходный код в соответствии с\n");
	printf ("поверочным сертификатом на термометр и скомпилировать заново.\n");
	printf ("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf ("\n");
	while (f) {
		printf ("\nВведи измеренное значение сопротивления Rt, в Омах, 0 для выхода\n\n");
		scanf ("%Lf", &Rt);

		if (Rt >= 79.90L && Rt <= 196.00L) mode = 0;
		if (Rt < 79.90L || Rt > 196.00L) mode = 1;
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
			printf ("\nОшибка ввода\n\n");
			break;
		}
	}
}

long double thermo_pol (void)
{
	unsigned char i;
	long double g, W, Wr, t;

	g = 0;
	t = 0;
	Wr = 0;
	W = Rt / Rtt;

	if (Rt >= Rtt && Rt <= 196.00L) {
		Wr = W - (a * (W - 1.00L) + b * pow((W - 1.00L),2));
		for (i=0;i<9;i++) {
			g = polinom1[i] * pow((Wr - 2.64L) / 1.64L, i+1);
			t = t + g;
		}

		t = t + Dn;
	}	
	
	if (Rt >= 79.90L && Rt < Rtt) {
		Wr = W - (M * (W - 1.00L));
		for (i=0;i<15;i++) {
			g = polinom2[i] * pow((pow(Wr,S) - 0.65L) / 0.35L, i+1);
			t = t + g;
		}

		t = ((t + Bn) * 273.16L) - 273.15L;
	}

	return t;
}	
