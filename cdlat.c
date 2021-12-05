/*****************************************************************************/
/*                                                                           */
/* file name: cdlat.c                                                        */
/*                                                                           */
/* The program provides the interface to the lattice ladder function which   */
/* calculates lattic and ladder coefficients and exists in the file          */
/* dsputils.c.  Input is taken from the standard input with the following    */
/* interface:                                                                */
/*                                                                           */
/*  First Record in File:     filter_order                                   */
/*  'a' coefficient:          a index value                                  */
/*  'b' coefficient:          b index value                                  */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>

float a[200], b[200], rk[200], rg[200];

main()
{
  void dlat();
  int i;
  float coef;
  char array, *console_status, console_buffer[100];
  int index, ip, ier;

  for (i = 0; i < 200; i++)
  { /* clear arrays */
    a[i] = 0.0;
    b[i] = 0.0;
    rk[i] = 0.0;
    rg[i] = 0.0;
  } /* for */

  scanf("%d",&ip); /* get filter order */

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
          b[index+1] = coef;
          break;

      } /* case */
    } /* if */
  } while (console_status != NULL);

  dlat(a,b,ip,rk,rg,&ier);

  for (i = 1; i <= ip; i++)
  {
    printf("k%d  %f\n",i,rk[i]);
  } /* for */

  printf("\n");

  for (i = 1; i <= ip+1; i++)
  {
    printf("v%d  %f\n",(i-1),rg[i]);
  } /* for */

} /* main */
