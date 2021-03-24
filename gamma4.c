#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define SWAP(a,b) {temp = (a); (a) = (b); (b) = temp;}

/* Function prototypes. */
long input(void);
void setup(double *seq, double *seqx);
void cleanup(void);
/* Global variables. */


double prom1=0;
double prom2=0;
long puntos;
char *pname;	/* this program's name (for use in error messages) */
double *seq;	/* input data buffer; allocated and filledvarios_u4096_ra_r32_c0.6_r0.17_s1_30_delta100_logbin15.dat by input() */
double *seqx;	/* input data buffer; allocated and filled by input() */
long *rs;	/* box size array; allocated and filled by rscale() */
double *mse;	/* fluctuation array; allocated by setup(), filled by dfa() */
int iflag = 1;	/* integrate the input data if non-zero */
int nfit = 2;	/* order of the regression fit, plus 1 */
int nr,i;		/* number of box sizes */
double a = 0;

main(int argc, char **argv)
{
    int i, sw = 0;
    long minbox = 0L, maxbox = 0L, npts, temp;

     
    /* Allocate and fill the input data array seq[]. */
    input();
    //printf("longitud = %li \n", puntos);
    setup(seq, seqx);
    free(seq);			/* allocated by input() */
    free(seqx);			/* allocated by input() */
    exit(0);
}

long input()
{
    long maxdat = 0L, maxdat1 = 0L, npts = 0L;
    double yy, y, yp = 0.0;
    int i,k,b,j,cont;
    b=0;
    //scanf("%lf %lf", &y, &yy);
    //printf("%lf %lf \n", y, yy);
 
      while (scanf("%lf %lf", &y, &yy)==2) {
	/*printf("%lf \n", y);*/
       // printf("%lf %lf \n", y, yy);
           
            
           if (++npts >= maxdat) {
            double *s;
	    maxdat += 50000;	/* allow the input buffer to grow (the
				   increment is arbitrary) */
	    if ((s = realloc(seq, maxdat * sizeof(double))) == NULL) {
		fprintf(stderr,
		      "%s: insufficient memory, truncating input at row %li\n",
		      pname, npts);
	        break;
	    }
	  seq = s;
	  }			  

           if (npts >= maxdat1) {
            double *s1;
            maxdat1 += 50000;	/* allow the input buffer to grow (the  increment is arbitrary) */
	    if ((s1 = realloc(seqx, maxdat1 * sizeof(double))) == NULL) {
		fprintf(stderr,
		      "%s: insufficient memory, truncating input at row %li\n",
		      pname, npts);
	        break;
	    }
           seqx = s1;
           }




        prom1=prom1+y;
        prom2=prom2+yy;    
	seq[npts] =y;
        seqx[npts] =yy;
         

        puntos=npts;
    }
 prom1=prom1/npts;
 prom2=prom2/npts;

}


#define A(y,x) seq[(y)*N+(x)]
void setup(double *seq, double *seqx)
{ double dynac=0;
  double scos, scos2;
  double ssen, ssen2;
  double dph[10000];
  double a;
  int j=0, delta=15;
  double pi=3.141592;
  for (i=1;i<=puntos;i++)
   {
    if(seq[i]<0){seq[i]+=2*pi;}
    if(seqx[i]<0){seqx[i]+=2*pi;}
    a=seq[i]-seqx[i];
    if (a>=pi){a+=-2*pi;}
    else if(a<=-pi){a+=2*pi;}
    dph[i]=a; 
   }

  for (i=1;i<=puntos-delta;i++)
   {
    if(i==1)
     {
      scos=0;
      ssen=0;
      for(j=i;j<i+delta;j++)
      {
       scos=scos+cos(dph[j]);
       ssen=ssen+sin(dph[j]);                 	
       //dynac=dynac+(seq[i]-prom1)*(seqx[i]-prom2);
      }
      scos2=scos;
      ssen2=ssen;
     }
    else
    {
     scos2=scos2-cos(dph[i-1])+cos(dph[i+delta-1]);
     ssen2=ssen2-sin(dph[i-1])+sin(dph[i+delta-1]);
    } 
    dynac=sqrt(pow(scos2,2)/pow(delta,2)+pow(ssen2,2)/pow(delta,2)); //((scos**2)/(delta**2)+(ssen**2)/(delta**2))**0.5;
    //printf("%g %g \n",  seq[i], dynac);
    if(dynac>0.7071 && fabs(dph[i])<pi/4)
      printf("%i %i \n", i, 1);
    else
      printf("%i %i \n",  i, 0); 
      //printf("%g %g \n",  seq[i], dynac);
      //printf("%g %g \n", dynac, seqx[i]); 
   }

}

