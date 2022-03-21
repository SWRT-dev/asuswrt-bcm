/*
 * MDCT/IMDCT transforms
 * Copyright (c) 2002 Fabrice Bellard.
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include "dsputil.h"

/**
 * @file mdct.c
 * MDCT/IMDCT transforms.
 */

// Generate a Kaiser-Bessel Derived Window.
#define BESSEL_I0_ITER 50 // default: 50 iterations of Bessel I0 approximation
void ff_kbd_window_init(float *window, float alpha, int n)
{
   int i, j;
   double sum = 0.0, bessel, tmp;
   double local_window[n];
   double alpha2 = (alpha * M_PI / n) * (alpha * M_PI / n);

   for (i = 0; i < n; i++) {
       tmp = i * (n - i) * alpha2;
       bessel = 1.0;
       for (j = BESSEL_I0_ITER; j > 0; j--)
           bessel = bessel * tmp / (j * j) + 1;
       sum += bessel;
       local_window[i] = sum;
   }

   sum++;
   for (i = 0; i < n; i++)
       window[i] = sqrt(local_window[i] / sum);
}

/**
 * init MDCT or IMDCT computation.
 */
int ff_mdct_init(MDCTContext *s, int nbits, int inverse)
{
    int n, n4, i;
    double alpha;

    memset(s, 0, sizeof(*s));
    n = 1 << nbits;
    s->nbits = nbits;
    s->n = n;
    n4 = n >> 2;
    s->tcos = av_malloc(n4 * sizeof(FFTSample));
    if (!s->tcos)
        goto fail;
    s->tsin = av_malloc(n4 * sizeof(FFTSample));
    if (!s->tsin)
        goto fail;

    for(i=0;i<n4;i++) {
        alpha = 2 * M_PI * (i + 1.0 / 8.0) / n;
        s->tcos[i] = -cos(alpha);
        s->tsin[i] = -sin(alpha);
    }
    if (ff_fft_init(&s->fft, s->nbits - 2, inverse) < 0)
        goto fail;
    return 0;
 fail:
    av_freep(&s->tcos);
    av_freep(&s->tsin);
    return -1;
}

/* complex multiplication: p = a * b */
#define CMUL(pre, pim, are, aim, bre, bim) \
{\
    double _are = (are);\
    double _aim = (aim);\
    double _bre = (bre);\
    double _bim = (bim);\
    (pre) = _are * _bre - _aim * _bim;\
    (pim) = _are * _bim + _aim * _bre;\
}

/**
 * Compute inverse MDCT of size N = 2^nbits
 * @param output N samples
 * @param input N/2 samples
 * @param tmp N/2 samples
 */
void ff_imdct_calc(MDCTContext *s, FFTSample *output,
                   const FFTSample *input, FFTSample *tmp)
{
    int k, n8, n4, n2, n, j;
    const uint16_t *revtab = s->fft.revtab;
    const FFTSample *tcos = s->tcos;
    const FFTSample *tsin = s->tsin;
    const FFTSample *in1, *in2;
    FFTComplex *z = (FFTComplex *)tmp;

    n = 1 << s->nbits;
    n2 = n >> 1;
    n4 = n >> 2;
    n8 = n >> 3;

    /* pre rotation */
    in1 = input;
    in2 = input + n2 - 1;
    for(k = 0; k < n4; k++) {
        j=revtab[k];
        CMUL(z[j].re, z[j].im, *in2, *in1, tcos[k], tsin[k]);
        in1 += 2;
        in2 -= 2;
    }
    ff_fft_calc(&s->fft, z);

    /* post rotation + reordering */
    /* XXX: optimize */
    for(k = 0; k < n4; k++) {
        CMUL(z[k].re, z[k].im, z[k].re, z[k].im, tcos[k], tsin[k]);
    }
    for(k = 0; k < n8; k++) {
        output[2*k] = -z[n8 + k].im;
        output[n2-1-2*k] = z[n8 + k].im;

        output[2*k+1] = z[n8-1-k].re;
        output[n2-1-2*k-1] = -z[n8-1-k].re;

        output[n2 + 2*k]=-z[k+n8].re;
        output[n-1- 2*k]=-z[k+n8].re;

        output[n2 + 2*k+1]=z[n8-k-1].im;
        output[n-2 - 2 * k] = z[n8-k-1].im;
    }
}

/**
 * Compute MDCT of size N = 2^nbits
 * @param input N samples
 * @param out N/2 samples
 * @param tmp temporary storage of N/2 samples
 */
void ff_mdct_calc(MDCTContext *s, FFTSample *out,
                  const FFTSample *input, FFTSample *tmp)
{
    int i, j, n, n8, n4, n2, n3;
    FFTSample re, im, re1, im1;
    const uint16_t *revtab = s->fft.revtab;
    const FFTSample *tcos = s->tcos;
    const FFTSample *tsin = s->tsin;
    FFTComplex *x = (FFTComplex *)tmp;

    n = 1 << s->nbits;
    n2 = n >> 1;
    n4 = n >> 2;
    n8 = n >> 3;
    n3 = 3 * n4;

    /* pre rotation */
    for(i=0;i<n8;i++) {
        re = -input[2*i+3*n4] - input[n3-1-2*i];
        im = -input[n4+2*i] + input[n4-1-2*i];
        j = revtab[i];
        CMUL(x[j].re, x[j].im, re, im, -tcos[i], tsin[i]);

        re = input[2*i] - input[n2-1-2*i];
        im = -(input[n2+2*i] + input[n-1-2*i]);
        j = revtab[n8 + i];
        CMUL(x[j].re, x[j].im, re, im, -tcos[n8 + i], tsin[n8 + i]);
    }

    ff_fft_calc(&s->fft, x);

    /* post rotation */
    for(i=0;i<n4;i++) {
        re = x[i].re;
        im = x[i].im;
        CMUL(re1, im1, re, im, -tsin[i], -tcos[i]);
        out[2*i] = im1;
        out[n2-1-2*i] = re1;
    }
}

void ff_mdct_end(MDCTContext *s)
{
    av_freep(&s->tcos);
    av_freep(&s->tsin);
    ff_fft_end(&s->fft);
}
