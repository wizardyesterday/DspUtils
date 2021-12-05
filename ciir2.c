/*****************************************************************************/
/*                                                                           */
/* file name: ciir2.c                                                        */
/*                                                                           */
/* The program provides the interface to the direct form 2 iir filter which  */
/* exists in the file dsputils.c.  Input is taken from the standard input    */
/* with the following interface:                                             */
/*                                                                           */
/*  First Record in File:     filter_ordera filter_orderb number_of_samples  */
/*  'a' coefficient:          a index value                                  */
/*  'b' coefficient:          b index value                                  */
/*  Input sample:             x index value                                  */
/*  Initial 'w' memory'       w index value                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

float a[200], b[200];
float w[200], x[200], y[200];

main()
{
  void iirdf2();
  int i;
  float coef;
  char array, *console_status, console_buffer[100];
  int index, count, m, n;

  for (i = 0; i <= 199; i++)
  { /* clear filter memory and intermediate responses */
    a[i] = 0.0;
    b[i] = 0.0;
    w[i] = 0.0;
    x[i] = 0.0;
    y[i] = 0.0;
  } /* for */

  scanf("%d %d %d",&m,&n,&count); /* get filter order and number of points */

  do
  {
    console_status = gets(console_buffer); /* get parameters */
    if (console_status != NULL)
    {
      sscanf(console_buffer,"%c %d %f",&array,&index,&coef);

      switch (array)
      {
        case 'a': /* feedback array */
          a[index] = coef;
          break;

        case 'b': /* feedforward array */
          b[index+1] = coef;
          break;

        case 'w': /* w memory */
          w[index] = coef;
          break;

        case 'x': /* x input */
          x[index] = coef;
          break;

      } /* case */

    } /* if */
  } while (console_status != NULL);

  for (i = 0; i < count; i++)
  { /* compute response y(n) */
    iirdf2(x[i],&y[i],m,n,b,a,w);
  } /* for */

  for (i = 0; i < count; i++)
  {
    printf("%d  %f\n",i,y[i]);
  } /* for */

} /* main */
