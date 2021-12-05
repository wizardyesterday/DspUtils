/**************************************************************************/
/*      file name: dsputils.c                                             */
/**************************************************************************/

#include <stdio.h>
#include <math.h>
#include "dsputils.h"

/**************************************************************************/
/*                                                                        */
/*      function: correlate                                               */
/*                                                                        */
/*      purpose: The purpose of this function is to perform a cross       */
/*      correlation between sequences X and Y, and store the output into  */
/*      sequence R.                                                       */
/*                                                                        */
/*      calling sequence: cross_correlation(x,n,y,m,r,lmax)               */
/*                                                                        */
/*      parameters:                                                       */
/*              x - Array containing sequence X.                          */
/*              n - The length of sequence X.                             */
/*              y - Array containing sequence Y.                          */
/*              m - The length of sequence Y.                             */
/*              r - Array containing the correlation.                     */
/*              lmax - The length of the correlation.                     */
/*                                                                        */
/**************************************************************************/

void correlate(x,n,y,m,r,lmax)
int n, m, lmax;
float x[], y[], r[];

{
  int l, k, nl;

  for (l = 0; l < lmax; l++)
  {
    nl = m + l - 1;
    if (nl >= (n - 1))
    {
      nl = n - 1;
    } /* if */
    r[l] = 0.0;
    for (k = l; k <= nl; k++)
    {
      r[l] = r[l] + (x[k] * y[k-l]);
    } /* for */
  } /* for */

  return;

} /* cross_correlation */

/**************************************************************************/
/*                                                                        */
/*      function: gauss                                                   */
/*                                                                        */
/*      purpose: The purpose of this function is to generate a random     */
/*      number that is weighted by a Gaussian density function.           */
/*                                                                        */
/*      calling sequence: number = gauss(sigma)                           */
/*                                                                        */
/*      parameters:                                                       */
/*              sigma - The standard deviation.                           */
/*                                                                        */
/**************************************************************************/

float gauss(sigma)
float sigma;

{
  float x, b, r, value;

  x = (float) rand(); /* get first random variable */
  x = x / 32768.0; /* scale */
  b = (float) rand(); /* get second random variable */
  b = b / 32768.0; /* scale */

  b = 2.0 * b * M_PI;
  r = sqrt(2.0 * sigma * sigma * log(1.0 / (1.0 - x)));
  value = r * cos(b);

  return (value);

} /* gauss */

/**************************************************************************/
/*                                                                        */
/*      function: iir                                                     */
/*                                                                        */
/*      purpose: The purpose of this function is to perform the actions   */
/*      of an infinite impulse response (IIR) filter. The following       */
/*      inputs are required:                                              */
/*                                                                        */
/*      Filter order: n                                                   */
/*      Filter Coefficients: {b(0),b(k),a(k), k=1,...,n}                  */
/*      Filter Memory: {xm(k),ym(k), k=0,1,...,n}                         */
/*      Note: xm, ym should be initialized to zero.                       */
/*      Input signal sample: xin                                          */
/*      Output signal sample: yout                                        */
/*                                                                        */
/*      calling sequence: iir(n,a,b,xm,ym,xin,&yout)                      */
/*                                                                        */
/*      parameters:                                                       */
/*              n - The filter order.                                     */
/*              a - An array of filter feedback weights.                  */ 
/*              b - An array of feedforward weights.                      */
/*              xm - The filter memory of past inputs.                    */
/*              ym - The filter memory of past outputs.                   */
/*              xin - The current input sample.                           */
/*              yout - A pointer to the returned output.                  */
/*                                                                        */
/**************************************************************************/

void iir(n,a,b,xm,ym,xin,yout)
int n;
float a[], b[], xm[], ym[], xin, *yout;

{
  int k;
  float sum;

  xm[0] = xin;
  sum = 0.0;

  for (k = n; k >= 1 ; k--)
  {
    sum = sum + (b[k] * xm[k]);
    sum = sum - (a[k] * ym[k]);
    xm[k] = xm[k-1];
    ym[k] = ym[k-1];
  } /* for */

  *yout = sum + b[0] * xm[0];
  ym[1] = *yout;

  return;

} /* iir */

/**************************************************************************/
/*                                                                        */
/*      function: convolve                                                */
/*                                                                        */
/*      purpose: The purpose of this function is to convolve two          */
/*      sequences f(n) and h(n) and generate an output g(n).              */
/*                                                                        */
/*      calling sequence: convolve(n,f,h,g)                               */
/*                                                                        */
/*      parameters:                                                       */
/*                 x - The input sequence.                                */
/*                 n - The length of the input sequence.                  */
/*                 h - The impulse response sequence.                     */
/*                 m - The length of the impulse response sequence.       */
/*                 y - The output sequence of length (m + n - 1).         */
/*                                                                        */
/**************************************************************************/

void convolve(x,n,h,m,y)
int m, n;
float x[], h[], y[];

{
  int i, j, k;

  k = m + n - 1; /* compute length of output sequence */

  for (i = 0; i < k; i++)
  { /* clear output sequence */
    y[i] = 0.0;
  } /* for */

  for (i = 0; i < n; i++)
  { /* perform convolution function */
    for (j = 0; j < m; j++)
    {
      y[i+j] += x[i] * h[j];
    } /* for */
  } /* for */

  return;

} /* convolve */

/**************************************************************************/
/*                                                                        */
/*      function: complex_mult                                            */
/*                                                                        */
/*      purpose: The purpose of this function is to multiply two          */
/*      complex numbers.                                                  */
/*                                                                        */
/*      calling sequence: result = complex_mult(a,b);                     */
/*                                                                        */
/*      parameters:                                                       */
/*                 a - A complex number to be multiplied.                 */
/*                 b - A complex number to be multiplied.                 */
/*                 result - The result of the computation.                */
/*                                                                        */
/**************************************************************************/

void complex_mult(a,b,result)
struct _complex *a;
struct _complex *b;
struct _complex *result;

{

  result->r = (a->r * b->r) - (a->i * b->i);
  result->i = (a->r * b->i) + (a->i * b->r); 

  return;

} /* complex_mult */

/**************************************************************************/
/*                                                                        */
/*      function: iirdf2                                                  */
/*                                                                        */
/*      purpose: The purpose of this function is to perform the actions   */
/*      of an infinite impulse response direct form II (IIR) filter.      */
/*      The following inputs are required:                                */
/*                                                                        */
/*      Input signal sample: xin                                          */
/*      Output signal sample: yout                                        */
/*      Size of "b" array: m                                              */
/*      Size of "a" array: n                                              */
/*      Filter Numerator Coefficients: {b(k), k=1,...,m+1}                */
/*                       Note that: b(k+1) = b,  k = 0,1,...,m            */
/*      Filter Denominator Coefficients: {a(k), k=1,...,n}                */
/*      Filter Memory: {w(k), k=1,...,max(m,n)+1}                         */
/*      Note: w should be initialized to zero.                            */
/*                                                                        */
/*      calling sequence: iirdf2(xin,&yout,m,n,b,a,w)                     */
/*                                                                        */
/*      parameters:                                                       */
/*              xin - The current input sample.                           */
/*              yout - A pointer to the returned output.                  */
/*              m - The numerator order.                                  */
/*              n - The denominator order.                                */
/*              b - An array of feedforward weights.                      */
/*              a - An array of filter feedback weights.                  */ 
/*              w - The filter memory of past inputs.                     */
/*                                                                        */
/**************************************************************************/

void iirdf2(xin,yout,m,n,b,a,w)
int m,n;
float a[], b[], w[], xin, *yout;

{
  int k, mp1, mp2, max;
  float s;

  mp1 = m+1;
  mp2 = m+2;
  max = n;

  if (m > n)
  {
    max = m;
  } /* if */

  /* Compute current output sample */
  s = xin;

  for (k = 1; k <= n; k++)
  {
    s = s - (a[k] * w[k+1]);
  } /* for */

  w[1] = s;
  s = 0.0;

  for (k = 1; k <= mp1; k++)
  {
    s = s + (b[k] * w[k]);
  } /* for */

  *yout = s;

  /* Shift stored data */
  for (k = 1; k <= max; k++)
  {
    w[max+2-k] = w[max+1-k];
  } /* for */

  return;

} /* iirdf2 */

/**************************************************************************/
/*                                                                        */
/*      function: ctdfii                                                  */
/*                                                                        */
/*      purpose: The purpose of this function is to perform the actions   */
/*      of an infinite impulse response direct form II (IIR) filter       */
/*      cascade of second-order stages.                                   */
/*      The following inputs are required:                                */
/*                                                                        */
/*      Input signal sample: xin                                          */
/*      Output signal sample: yout                                        */
/*      Number of filter sections: k                                      */
/*      Filter Numerator Coefficients: {b(i,j), i = 1,..,k, j = 1,2}      */ 
/*      Filter Denominator Coefficients: {a(i,j), i = 1,..,k, j = 1,2}    */
/*      Filter Memory: w1(i), w2(i), i = 1,...,k                          */
/*      Note: w should be initialized to zero.                            */
/*                                                                        */
/*      calling sequence: ctdfii(xin,&yout,k,b,a,w1,w2)                   */
/*                                                                        */
/*      parameters:                                                       */
/*              xin - The current input sample.                           */
/*              yout - A pointer to the returned output.                  */
/*              k - The number of filter sections.                        */
/*              b - An array of feedforward weights.                      */
/*              a - An array of filter feedback weights.                  */ 
/*              w1 - The filter memory array (one unit-delay).            */
/*              w2 - The filter memory array (two unit-delays).           */
/*                                                                        */
/**************************************************************************/

void ctdfii(xin,yout,k,b,a,w1,w2)
int k;
float a[][3], b[][4], w1[], w2[], xin, *yout;

{
  int j;
  float yj, yjm1;

  yjm1 = xin;

  for (j = 1; j <= k; j++)
  {
    yj = (b[j][1] * yjm1) + w1[j]; 
    w1[j] = (b[j][2] * yjm1) - (a[j][1] * yj) + w2[j];
    w2[j] = (b[j][3] * yjm1) - (a[j][2] * yj);
    yjm1 = yj;
  } /* for */

  *yout = yj;

  return;

} /* ctdfii */

/**************************************************************************/
/*                                                                        */
/*      function: dlat                                                    */
/*                                                                        */
/*      purpose: The purpose of this function is to convert pole-zero     */
/*      direct form coefficients into lattice-ladder parameters.          */
/*      The following inputs are required:                                */
/*                                                                        */
/*      Input:                                                            */
/*      Filter Denominator Coefficients: {a(i), i = 1,..,ip}              */
/*      Filter Numerator Coefficients: {b(i), i = 1,..,ip+1}              */ 
/*      ip = m = n: Filter's order                                        */
/*                                                                        */
/*      Output:                                                           */
/*      Lattice Parameters: {rk(i, i = 1,...,ip}                          */
/*      Ladder Parameters: {rg(i, i = 1,...,ip}                           */
/*                                                                        */
/*      calling sequence: dlat(a,b,ip,rk,rg,&ier)                         */
/*                                                                        */
/*      parameters:                                                       */
/*              a - An array of filter feedback weights.                  */ 
/*              b - An array of feedforward weights.                      */
/*              ip - The filter order.                                    */
/*              rk - The lattice parameters.                              */
/*              rg - The ladder parameters.                               */
/*              ier - An error flag.                                      */
/*                                                                        */
/**************************************************************************/

void dlat(a,b,ip,rk,rg,ier)
int ip;
int *ier;
float a[], b[], rk[], rg[];

{
  int j, k, l, m, m1, ip2;
  float help;

  *ier = 0; /* set initially to successful */
  ip2 = ip + 2;

  for (m = 1; m <= ip; m++)
  { /* initialize our arrays */
    rk[m] = a[m]; /* fill with denominator polynomial */
    rg[m] = b[m]; /* fill with numerator polynomial */
  } /* for */

  /* fill in the last position */
  rg[ip+1] = b[ip+1];

  for (l = 2; l <= ip; l++)
  {
    m = ip2 - l; /* used for upper limits on loops */
    m1 = m+1; 

    for (j = 1; j <= m; j++)
    { /* construct reverse polynomial */
      b[j] = rk[m1-j];
    } /* for */

    if (abs(rk[m]) >= 1.0)
    { /* unstable system, let's indicate this */
      *ier = 1;
    } /* if */

    help = 1.0 - (rk[m] * rk[m]); /* compute denominator */
    help = 1.0 / help;
    m1 = m - 1; /* used for upper limit on loop */

    for (j = 1; j <= m1; j++)
    { /* compute reflection coefficients */
      rk[j] = rk[j] - (rk[m] * b[j+1]);
      rk[j] = help * rk[j];
    } /* for */

    for (j = 1; j <= m; j++)
    { /* compute ladder coefficients */
      rg[j] = rg[j] - (rg[m+1] * b[j]);
    } /* for */
  } /* for */

  /* let's not forget the last coefficient */
  rg[1] = rg[1] - (rg[2] * rk[1]);

  return;

} /* dlat */

/**************************************************************************/
/*                                                                        */
/*      function: azlat                                                   */
/*                                                                        */
/*      purpose: The purpose of this function is to implement an all-zero */
/*      lattice filter.                                                   */
/*                                                                        */
/*      Input: ip, rk(1),...,rp(ip), xin                                  */
/*                                                                        */
/*      Output: yout                                                      */
/*                                                                        */
/*      calling sequence: azlat(ip,rk,xin,&yout,&oldx,oldg)               */
/*                                                                        */
/*      parameters:                                                       */
/*              ip - The filter order.                                    */
/*              rk - The lattice parameters.                              */
/*              xin - The current input sample.                           */
/*              yout - A pointer to the returned output.                  */
/*              oldx - The previous value of xin.                         */
/*              oldg - A memory array for past values of g.               */
/*                                                                        */
/**************************************************************************/

void azlat(ip,rk,xin,yout,oldx,oldg)
int ip;
float xin, *yout, *oldx, rk[], oldg[];

{
  int m;
  float f[21], g[21];

  f[1] = xin + (rk[1] * *oldx); /* compute first forward output */
  g[1] = (rk[1] * xin) + *oldx; /* compute first backward output */
  *oldx = xin; /* transfer current input sample to delayed sample */

  for (m = 2; m <= ip; m++)
  {
    f[m] = f[m-1] + (rk[m] * oldg[m-1]);
    g[m] = (rk[m] * f[m-1]) + oldg[m-1];
    oldg[m-1] = g[m-1]; 
  } /* for */

  *yout = f[ip]; /* get output value */

  return;

} /* azlat */

/**************************************************************************/
/*                                                                        */
/*      function: aplat                                                   */
/*                                                                        */
/*      purpose: The purpose of this function is to implement an all-pole */
/*      lattice filter.                                                   */
/*                                                                        */
/*      Input: ip, rk(1),...,rp(ip), xin                                  */
/*                                                                        */
/*      Output: yout                                                      */
/*                                                                        */
/*      calling sequence: azlat(ip,rk,xin,&yout,&oldy,g)                  */
/*                                                                        */
/*      parameters:                                                       */
/*              ip - The filter order.                                    */
/*              rk - The lattice parameters.                              */
/*              xin - The current input sample.                           */
/*              yout - A pointer to the returned output.                  */
/*              oldy - The previous value of y.                           */
/*              g - A memory array for values of g.                       */
/*                                                                        */
/**************************************************************************/

void aplat(ip,rk,xin,yout,oldy,g)
int ip;
float xin, *yout, *oldy, rk[], g[];

{
  int j, m, nm1;
  float f[21];

  nm1 = ip - 1; /* loop limit */
  f[ip] = xin; /* get current input sample */

  for (j = 1; j <= nm1; j++)
  {
    m = ip + 1 - j; /* set array index */
    f[m-1] = f[m] - (rk[m] * g[m-1]); /* compute forward output */
    g[m] = (rk[m] * f[m-1]) + g[m-1]; /* compute backard output */
  } /* for */

  *yout = f[1] - (rk[1] * *oldy); /* get output value */
  g[1] = (rk[1] * *yout) + *oldy; /* set first backward output */
  *oldy = *yout; /* transfer current output into delay output value */

  return;

} /* aplat */

/**************************************************************************/
/*                                                                        */
/*      function: latlad                                                  */
/*                                                                        */
/*      purpose: The purpose of this function is to implement a lattice-  */
/*      ladder filter.                                                    */
/*                                                                        */
/*      Input: ip, rk(1),...,rp(ip), rg(0),...,rg(ip), xin                */
/*                                                                        */
/*      Output: y                                                         */
/*                                                                        */
/*      calling sequence: latlad(ip,rk,rg,xin,&y,&oldy,g)                 */
/*                                                                        */
/*      parameters:                                                       */
/*              ip - The filter order.                                    */
/*              rk - The lattice parameters.                              */
/*              rg - The ladder parameters.                               */
/*              xin - The current input sample.                           */
/*              y - A pointer to the returned output.                     */
/*              oldy - The previous value of y.                           */
/*              g - A memory array for values of g.                       */
/*                                                                        */
/**************************************************************************/

void latlad(ip,rk,rg,xin,y,oldy,g)
int ip;
float xin, *y, *oldy, rk[], rg[], g[];

{
  int j, m, nm1;
  float yout, f[21];

  nm1 = ip - 1; /* loop limit */
  f[ip] = xin; /* get current input sample */

  for (j = 1; j <= nm1; j++)
  {
    m = ip + 1 - j; /* set array index */
    f[m-1] = f[m] - (rk[m] * g[m-1]); /* compute forward output */
    g[m] = (rk[m] * f[m-1]) + g[m-1]; /* compute backard output */
  } /* for */

  yout = f[1] - (rk[1] * *oldy); /* get output value */
  g[1] = (rk[1] * yout) + *oldy; /* set first backward output */
  *oldy = yout; /* transfer current output into delay output value */

  *y = rg[0] * yout;

  for (j = 1; j <= ip; j++)
  {
    *y = *y + (rg[j] * g[j]);
  } /* for */

  return;

} /* latlad */

/**************************************************************************/
/*                                                                        */
/*      function: iirpar                                                  */
/*                                                                        */
/*      purpose: The purpose of this function is to perform the actions   */
/*      of an infinite impulse response parallel form (IIR) filter        */
/*      composed of second-order stages.                                  */
/*      The following inputs are required:                                */
/*                                                                        */
/*      Input signal sample: xin                                          */
/*      Output signal sample: yout                                        */
/*      Number of filter sections: k                                      */
/*      Filter Numerator Coefficients: {b(i,j), i = 1,..,k, j = 1,..,2}   */ 
/*      Filter Denominator Coefficients: {a(i,j), i = 1,..,k, j = 1,..,2} */
/*      Filter Memory: w1(i), w2(i), i = 1,...,k                          */
/*      Note: w should be initialized to zero.                            */
/*                                                                        */
/*      calling sequence: iirpar(xin,&yout,k,b,a,w1,w2)                   */
/*                                                                        */
/*      parameters:                                                       */
/*              xin - The current input sample.                           */
/*              yout - A pointer to the returned output.                  */
/*              k - The number of filter sections.                        */
/*              b - An array of feedforward weights.                      */
/*              a - An array of filter feedback weights.                  */ 
/*              w1 - The filter memory array (one unit-delay).            */
/*              w2 - The filter memory array (two unit-delays).           */
/*                                                                        */
/**************************************************************************/

void iirpar(xin,yout,k,b,a,w1,w2)
int k;
float a[][3], b[][4], w1[], w2[], xin, *yout;

{
  int j;
  float yj, yjm1;

  yjm1 = 0.0; /* initialize */

  for (j = 1; j <= k; j++)
  {
    yj = (b[j][1] * xin) + w1[j]; 
    w1[j] = (b[j][2] * xin) - (a[j][1] * yj) + w2[j];
    w2[j] = (b[j][3] * xin) - (a[j][2] * yj);
    yjm1 = yjm1 + yj;
  } /* for */

  *yout = yjm1;

  return;

} /* iirpar */

/**************************************************************************/
/*                                                                        */
/*      function: iirss                                                   */
/*                                                                        */
/*      purpose: The purpose of this function is to perform the actions   */
/*      of a second order state space realization. Note that the v arrays */
/*      must be initialized to zero.                                      */
/*                                                                        */
/*      calling sequence: iirss(xin,&yout,f,q,g,d,v1,v2)                  */
/*                                                                        */
/*      parameters:                                                       */
/*              xin - The current input sample.                           */
/*              yout - A pointer to the returned output.                  */
/*              f - The coefficient matrix for v(n).                      */
/*              q - The coefficient vector for x(n).                      */
/*              g - The coefficient vector for v(n) for the output, y(n). */
/*              d - The multiplier for x(n) for the output, y(n).         */
/*              v1 - The state variable and its delayed value.            */
/*              v2 - The state variable and its delayed value.            */
/*                                                                        */
/**************************************************************************/

void iirss(xin,yout,f,q,g,d,v1,v2)
float xin, *yout;
float f[3][3], q[3], g[3], d;
float v1[2], v2[2];

{

  /* compute new state */
  v1[1] = (f[1][1] * v1[0]) + (f[1][2] * v2[0]) + (q[1] * xin);
  v2[1] = (f[2][1] * v1[0]) + (f[2][2] * v2[0]) + (q[2] * xin);

  /* compute output value */
  *yout = (g[1] * v1[0]) + (g[2] * v2[0]) + (d * xin);

  /* transfer through delay element */
  v1[0] = v1[1];
  v2[0] = v2[1];

  return;

} /* iirss */

/**************************************************************************/
/*                                                                        */
/*      function: lfir                                                    */
/*                                                                        */
/*      purpose: The purpose of this function is to perform the actions   */
/*      of a linear phase finite impulse response (IIR) filter. The       */
/*      following inputs are required:                                    */
/*                                                                        */
/*      Filter order: m                                                   */
/*      Filter Coefficients: {b(0),b(k),a(k), k=1,...,m}                  */
/*      Note: Only half of the filter coefficients are necessary since    */
/*      the filter is linear phase.                                       /*
/*      Filter Memory: {xm(k),ym(k), k=0,1,...,m}                         */
/*      Note: xm should be initialized to zero.                           */
/*      Input signal sample: xin                                          */
/*      Output signal sample: yout                                        */
/*                                                                        */
/*      calling sequence: lfir(m,b,xm,xin,&yout)                          */
/*                                                                        */
/*      parameters:                                                       */
/*              m - The filter order.                                     */
/*              b - An array of feedforward weights.                      */
/*              xm - The filter memory of past inputs.                    */
/*              xin - The current input sample.                           */
/*              yout - A pointer to the returned output.                  */
/*                                                                        */
/**************************************************************************/

void lfir(m,b,xm,xin,yout)
int m;
float b[], xm[], xin, *yout;

{
  int k, l;
  float sum;

  xm[0] = xin;
  sum = 0.0;

  k = m / 2; /* set up for even/odd test of m */
  k = k * 2;
  l = m / 2; /* set up loop limit */

  if (k != m)
  { /* m is odd */
    for (k = 0; k <= l; k++)
    {
      sum = sum + (b[k] * xm[k]);
      sum = sum + (b[k] * xm[m-k]);
    } /* for */
  } /* if */
  else
  { /* m is even */
    for (k = 0; k < l; k++)
    {
      sum = sum + (b[k] * xm[k]);
      sum = sum + (b[k] * xm[m-k]);
    } /* for */
    sum = sum + (b[l] * xm[l]); /* get middle term */
  } /* else */

  sum = sum + (b[m] * xm[m]); /* update sum */

  for (k = m; k >= 1 ; k--)
  { /* update filter memory */
    xm[k] = xm[k-1];
  } /* for */

  *yout = sum;

  return;

} /* lfir */
