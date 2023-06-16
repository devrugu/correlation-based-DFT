#include <math.h>
#include <stdio.h>
#include "headers/ciz.h"

#define PI 3.14159265358979323846
#define ornek_sayisi 128

void sinus_olustur(int toplam_ornek_sayisi, double *sinus, double frekans)
{
    double xs[toplam_ornek_sayisi];

    for (int i = 0; i < toplam_ornek_sayisi; i++)
    {
        sinus[i] = sin(2 * PI * frekans * i / ornek_sayisi);
        xs[i] = (double)i / ornek_sayisi;
    }

    orijinal_sinus_ciz(xs, sinus, toplam_ornek_sayisi);
}

void ornek_al(double *sinus, double *ayrik_sinus)
{
    for (int i = 0; i < ornek_sayisi; i++)
    {
        ayrik_sinus[i] = sinus[i];
		printf("Ornek %d: %f\n", i, ayrik_sinus[i]);
    }

	ayrik_sinus_ciz(ornek_sayisi, ayrik_sinus);

	printf("-----------------------------\n");
}

void DFT_hesapla(double *ayrik_sinus, double *DFT)
{
	int k, n;
	double Xre[ornek_sayisi], Xim[ornek_sayisi];

    for (k = 0; k < ornek_sayisi; k++)
    {
        Xre[k] = 0;
        Xim[k] = 0;
        for (n = 0; n < ornek_sayisi; n++)
        {
            Xre[k] += ayrik_sinus[n] * cos(2 * PI * k * n / ornek_sayisi);
            Xim[k] -= ayrik_sinus[n] * sin(2 * PI * k * n / ornek_sayisi);
        }
        DFT[k] = sqrt(Xre[k] * Xre[k] + Xim[k] * Xim[k]) / (ornek_sayisi / 2);
        printf("DFT[%d] = %.2f %.2fi --> %.2f\n", k, Xre[k], Xim[k], DFT[k]);
    }

	DFT_ciz(ornek_sayisi, DFT);

	printf("-----------------------------\n");
}

int main(int argc, char *argv[])
{
    double frekans, zaman;

    if (argc != 3)
    {
        printf("Kullanim: %s <sinus dalgasinin frekansi(Hz)> <sinus dalgasinin zamani(Sn)>\n", argv[0]);
        return 1;
    }

    frekans = atof(argv[1]);
    zaman = atof(argv[2]);

    //int nysh_ornek_sayisi = ((int)frekans>(ornek_sayisi/2)) ? (int)(frekans*2) : ornek_sayisi; // Nyquist-shannon ornekleme teoremi

    int toplam_ornek_sayisi = zaman * ornek_sayisi;
    double *sinus = malloc(toplam_ornek_sayisi * sizeof(double));
    sinus_olustur(toplam_ornek_sayisi, sinus, frekans);

    double *ayrik_sinus = malloc(ornek_sayisi * sizeof(double));
    ornek_al(sinus, ayrik_sinus);

	double *DFT = malloc(ornek_sayisi * sizeof(double));
	DFT_hesapla(ayrik_sinus, DFT);

	free(sinus);
	free(ayrik_sinus);
	free(DFT);

    return 0;
}