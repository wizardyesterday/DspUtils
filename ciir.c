/*****************************************************************************/
/*                                                                           */
/* file name: ciir.c                                                         */
/*                                                                           */
/* The program provides the interface to the direct form 1 iir filter which  */
/* exists in the file dsputils.c.  Input is taken from the standard input    */
/* with the following interface:                                             */
/*                                                                           */
/*  First Record in File:     filter_order number_of_samples                 */
/*  'a' coefficient:          a index value                                  */
/*  'b' coefficient:          b index value                                  */
/*  Input sample:             x index value                                  */
/*  Initial 'y' memory:       y index value                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

float a[200], b[200];
float xm[200], ym[200],x[200], y[200];

main()
{
  void iir();
  int i;
  float coef;
  char array, *console_status, console_buffer[100];
  int index, count, n;

  for (i = 0; i <= 199; i++)
  { /* clear filter memory and intermediate responses */
    a[i] = 0.0;
    b[i] = 0.0;
    xm[i] = 0.0;
    ym[i] = 0.0;
    x[i] = 0.0;
    y[i] = 0.0;
  } /* for */

  scanf("%d %d",&n,&count); /* get filter order and number of points */

  do
  {
    console_status = gets(console_buffer); /* get parameters */

    if (console_status != NULL)
    {
      sscanf(console_buffer,"%c %d %f",&array,&index,&coef);

      switch (array)
      {

        case 'a': /* feedback coefficient */
          a[index] = coef;
          break;

        case 'b': /* feedforward coefficient */
          b[index] = coef;
          break;

        case 'y': /* 'y' memory */
          ym[index] = coef;
          break;

        case 'x': /* input sample */
          x[index] = coef;
          break;

      } /* case */
    } /* if */
  } while (console_status != NULL);

  for (i = 0; i < count; i++)
  { /* compute response y(n) */
    iir(n,a,b,xm,ym,x[i],&y[i]);
  } /* for */

  for (i = 0; i < count; i++)
  {
    printf("%d  %f\n",i,y[i]);
  } /* for */

} /* main */
