/*****************************************************************************/
/*                                                                           */
/* file name: ccor.c                                                         */
/*                                                                           */
/* The program provides the interface to the correlator which                */
/* exists in the file dsputils.c.  Input is taken from the standard input    */
/* with the following interface:                                             */
/*                                                                           */
/*  First Record in File:     x_length y_length correlator_length            */
/*  Input sample:             x index value                                  */
/*  Input sample:             y index value                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

float r[200];
float x[200], y[200];

main()
{
  int i;
  float value;
  char array, *console_status, console_buffer[100];
  int index, m, n, lmax;

  for (i = 0; i <= 199; i++)
  { /* clear input and output records*/
    r[i] = 0.0;
    x[i] = 0.0;
    y[i] = 0.0;
  } /* for */

  /* get x length, y length, and output record length */
  scanf("%d %d %d",&n,&m,&lmax);

  do
  {
    console_status = gets(console_buffer); /* get parameters */

    if (console_status != NULL)
    {
      sscanf(console_buffer,"%c %d %f",&array,&index,&value);

      switch (array)
      {
        case 'x': /* x value */
          x[index] = value;
          break;

        case 'y': /* y value */
          y[index] = value;
          break;

      } /* case */
    } /* if */
  } while (console_status != NULL);

  correlate(x,n,y,m,r,lmax);

  for (i = 0; i < lmax; i++)
  {
    printf("r[%d] = %f\n",i,r[i]);
  } /* for */

} /* main */
