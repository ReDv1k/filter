#include <fltFltDGreb.h>

void fltFltDGreb::inverseImage(const quint8 *inp, quint8 *out)
{
	for (qint32 y = 0; y < height; ++y)
		for (qint32 x = 0; x < width; ++x)
		{
			qint32 pos = (y * width + x) * 3;
			out[pos + 0] = 255 - inp[pos + 0];
			out[pos + 1] = 255 - inp[pos + 1];
			out[pos + 2] = 255 - inp[pos + 2];
		}
}

void fltFltDGreb::imageBrightDivide(const quint8 *inp, quint8 *out, qint32 divider)
{
	for (qint32 y = 0; y < height; ++y)
		for (qint32 x = 0; x < width; ++x)
		{
			qint32 pos = (y * width + x) * 3;
			out[pos + 0] = inp[pos + 0]/divider;
			out[pos + 1] = inp[pos + 1]/divider;
			out[pos + 2] = inp[pos + 2]/divider;
		}
}



