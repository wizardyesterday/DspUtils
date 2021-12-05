
/*****************************************************************************/
/*                                                                           */
/* file name: ciirss.c                                                       */
/*                                                                           */
/* The program provides the interface to the state space iir filter which    */
/* exists in the file dsputils.c.  Input is taken from the standard input    */
/* with the following interface:                                             */
/*                                                                           */
/*  First Record in File:     filter_order number_of_samples                 */
/*  'f' coefficient:          f index1 index2 value                          */
/*  'q' coefficient:          d index value                                  */
/*  'g' coefficient:          g index value                                  */
/*  'd' coefficient:          d value                                        */
/*  Input sample:             x index value                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

float x[200], y[200];
float f[3][3], q[3], g[3], d;
float v1[2], v2[2];

main()
{
  void iirss();
  int i;
  float coef;
  char array, *console_status, console_buffer[100];
  int index1, index2, count, k;

  for (i = 0; i <= 199; i++)
  { /* clear input and output arrays */
    x[i] = 0.0;
    y[i] = 0.0;
  } /* for */

  /* clear state variables */
  v1[0] = 0.0;
  v1[1] = 0.0;
  v2[1] = 0.0;
  v2[2] = 0.0;

  scanf("%d %d",&k,&count); /* get number of stages and number of points */

  do
  {
    console_status = gets(console_buffer); /* get parameters */
    if (console_status != NULL)
    {
      sscanf(console_buffer,"%c %d %d %f",&array,&index1,&index2,&coef);

      switch (array)
      {
        case 'f':
          f[index1][index2] = coef;
          break; 

        case 'q':
          sscanf(console_buffer,"%c %d %f",&array,&index1,&coef);
          q[index1] = coef;
          break; 

        case 'g':
          sscanf(console_buffer,"%c %d %f",&array,&index1,&coef);
          g[index1] = coef;
          break; 

        case 'd':
          sscanf(console_buffer,"%c %f",&array,&coef);
          d = coef;
          break; 

        case 'x':
          sscanf(console_buffer,"%c %d %f",&array,&index1,&coef);
          x[index1] = coef;
          break; 

      } /* case */
    } /* if */

  } while (console_status != NULL);


  for (i = 0; i < count; i++)
  { /* compute impulse response y(n) */
    iirss(x[i],&y[i],f,q,g,d,v1,v2);
  } /* for */

  for (i = 0; i < count; i++)
  {
    printf("%d  %f\n",i,y[i]);
  } /* for */

} /* main */
