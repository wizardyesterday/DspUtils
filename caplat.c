/*****************************************************************************/
/*                                                                           */
/* file name: caplat.c                                                       */
/*                                                                           */
/* The program provides the interface to the all pole lattice filter which   */
/* exists in the file dsputils.c.  Input is taken from the standard input    */
/* with the following interface:                                             */
/*                                                                           */
/*  First Record in File:     filter_order number_of_samples                 */
/*  Lattice Parameter:        k index value                                  */
/*  Input sample:             x index value                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

float rk[200], g[200], x[200], y[200];

main()
{
  void aplat();
  int i;
  float oldy;
  float coef;
  char array, *console_status, console_buffer[100];
  int index, count, ip;

  oldy = 0.0; /* initialize */

  for (i = 0; i <= 199; i++)
  { /* clear filter memory and intermediate responses */
    rk[i] = 0.0;
    g[i] = 0.0;
    x[i] = 0.0;
    y[i] = 0.0;
  } /* for */

  scanf("%d %d",&ip,&count); /* get filter order and number of points */

  do
  {
    console_status = gets(console_buffer); /* get parameters */
    if (console_status != NULL)
    {
      sscanf(console_buffer,"%c %d %f",&array,&index,&coef);

      switch (array)
      {
        case 'k': /* lattice parameter */
          rk[index] = coef;
          break;

        case 'x': /* x input */
            x[index] = coef;
          break;

      } /* case */
    } /* if */ 
  } while (console_status != NULL);

  for (i = 0; i < count; i++)
  { /* compute response y(n) */
    aplat(ip,rk,x[i],&y[i],&oldy,g);
  } /* for */

  for (i = 0; i < count; i++)
  {
    printf("%d  %f\n",i,y[i]);
  } /* for */

} /* main */
