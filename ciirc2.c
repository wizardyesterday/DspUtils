/*****************************************************************************/
/*                                                                           */
/* file name: ciirc2.c                                                       */
/*                                                                           */
/* The program provides the interface to the direct form 2 iir filter which  */
/* exists in the file dsputils.c.  The primitive filter function is handles  */
/* cascaded filter sections.  Input is taken from the standard input         */
/* with the following interface:                                             */
/*                                                                           */
/*  First Record in File:     number_of_filter_sections number_of_samples    */
/*  'a' coefficient:          a index1 index2 value                          */
/*  'b' coefficient:          b index1 index2 value                          */
/*  Input sample:             x index value                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

float a[200][3], b[200][4];
float w1[200], w2[200],x[200], y[200];

main()
{
  void ctdfii();
  int i;
  float coef;
  char array, *console_status, console_buffer[100];
  int index1, index2, count, k;

  for (i = 0; i <= 199; i++)
  { /* clear filter memory and intermediate responses */
    a[i][0] = 0.0;
    a[i][1] = 0.0;
    a[i][2] = 0.0;
    a[i][3] = 0.0;
    b[i][0] = 0.0;
    b[i][1] = 0.0;
    b[i][2] = 0.0;
    b[i][3] = 0.0;
    b[i][4] = 0.0;
    w1[i] = 0.0;
    w2[i] = 0.0;
    x[i] = 0.0;
    y[i] = 0.0;
  } /* for */

  scanf("%d %d",&k,&count); /* get number of stages and number of points */

  do
  {
    console_status = gets(console_buffer); /* get parameters */
    if (console_status != NULL)
    {
      sscanf(console_buffer,"%c %d %d %f",&array,&index1,&index2,&coef);

      switch (array)
      {
        case 'a': /* feedback array */
          a[index1][index2] = coef;
          break;

        case 'b': /* feedforward coefficient */
          b[index1][index2+1] = coef;
          break;

        case 'x': /* x input */
          sscanf(console_buffer,"%c %d %f",&array,&index1,&coef);
          x[index1] = coef;
          break;
 
      } /* case */
    } /* if */
  } while (console_status != NULL);

  for (i = 0; i < count; i++)
  { /* compute response y(n) */
    ctdfii(x[i],&y[i],k,b,a,w1,w2);
  } /* for */

  for (i = 0; i < count; i++)
  {
    printf("%d  %f\n",i,y[i]);
  } /* for */

} /* main */
