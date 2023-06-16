#include "../pbplots/pbPlots.h"
#include "../pbplots/supportLib.h"

// DFT çizim fonksiyonu
int DFT_ciz(int ornek_sayisi, double *DFT)
{
    double xs[ornek_sayisi];

    for (int i = 0; i < ornek_sayisi; i++)
        xs[i] = i;

    _Bool success;
    StringReference *errorMessage;

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = xs;
    series->xsLength = ornek_sayisi;
    series->ys = DFT;
    series->ysLength = ornek_sayisi;
    series->linearInterpolation = false;
	series->pointType = L"dotlinetoxaxis";
	series->pointTypeLength = wcslen(series->pointType);
    series->color = CreateRGBColor(1, 0, 0.5);

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1280;
    settings->height = 400;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = L"DFT SPEKTRUMU";
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"FREKANS(Hz)";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"BUYUKLUK";
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s [] = {series};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 1;

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    errorMessage = (StringReference *)malloc(sizeof(StringReference));
    success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);

    if(success)
    {
        size_t length;
        double *pngdata = ConvertToPNG(&length, canvasReference->image);
        WriteToFile(pngdata, length, "DFT_spektrumu.png");
        DeleteImage(canvasReference->image);
    }
    else
    {
        fprintf(stderr, "Error: ");
        for(int i = 0; i < errorMessage->stringLength; i++)
        {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

    return success ? 0 : 1;
}

int ayrik_sinus_ciz(int ornek_sayisi, double *ayrik_sinus)
{
    double xs[ornek_sayisi];

    for (int i = 0; i < ornek_sayisi; i++)
        xs[i] = i;

    _Bool success;
	StringReference *errorMessage;

	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = xs;
	series->xsLength = ornek_sayisi;
	series->ys = ayrik_sinus;
	series->ysLength = ornek_sayisi;
	series->linearInterpolation = false;
    series->pointType = L"dotlinetoxaxis";
	series->pointTypeLength = wcslen(series->pointType);
	series->color = CreateRGBColor(1, 0, 0);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1280;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = L"AYRIK ZAMANDA SINUS SINYALI";
	settings->titleLength = wcslen(settings->title);
	settings->xLabel = L"n";
	settings->xLabelLength = wcslen(settings->xLabel);
	settings->yLabel = L"X[n]";
	settings->yLabelLength = wcslen(settings->yLabel);
	ScatterPlotSeries *s [] = {series};
	settings->scatterPlotSeries = s;
	settings->scatterPlotSeriesLength = 1;

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	errorMessage = (StringReference *)malloc(sizeof(StringReference));
	success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);

	if(success)
    {
		size_t length;
		double *pngdata = ConvertToPNG(&length, canvasReference->image);
		WriteToFile(pngdata, length, "ayrik_sinus_dalgasi.png");
		DeleteImage(canvasReference->image);
	}
    else
    {
		fprintf(stderr, "Error: ");
		for(int i = 0; i < errorMessage->stringLength; i++)
        {
			fprintf(stderr, "%c", errorMessage->string[i]);
		}
		fprintf(stderr, "\n");
	}

	return success ? 0 : 1;
}

void orijinal_sinus_ciz(double *xs, double *sinus, int toplam_ornek_sayisi)
{
    _Bool success;
    StringReference *errorMessage;

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = xs;
    series->xsLength = toplam_ornek_sayisi;
    series->ys = sinus;
    series->ysLength = toplam_ornek_sayisi;
    series->linearInterpolation = true;
    series->lineType = L"solid";
    series->lineTypeLength = wcslen(series->lineType);
    series->lineThickness = 3;
    series->color = CreateRGBColor(0.784, 0.635, 0.784);

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1280;
    settings->height = 400;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = L"ORIJINAL SINUS DALGASI";
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"ZAMAN (sn)";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"GENLIK";
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s [] = {series};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 1;

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    errorMessage = (StringReference *)malloc(sizeof(StringReference));
    success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);

    if (success)
    {
        size_t length;
        double *pngdata = ConvertToPNG(&length, canvasReference->image);
        WriteToFile(pngdata, length, "orijinal_sinus_dalgasi.png");
        DeleteImage(canvasReference->image);
    }
    else
    {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errorMessage->stringLength; i++)
        {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }
}