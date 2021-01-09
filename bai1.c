#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
sem_t semv1,semv2,semw1,semw2,semy1,semy2,semz1,semz2;
int x1=1,
    x2=3,
    x3=5,
    x4=7,
    x5=9,
    x6=11;
int w,v,y,z,ans;
void *processA(void* mess)
{
		w = x1*x2;
		printf("\nw= x1*x2= %d",w);
		sem_post(&semw1);
		sem_post(&semw2);
	
}
void *processB(void* mess)
{
	
		v = x3*x4;
		printf("\nv= x3*x4= %d",v);
		sem_post(&semv1);
		sem_post(&semv2);
	
}
void *processC(void* mess)
{
	
		sem_wait(&semv1);
		y=v*x5;
		printf("\ny= v*x5= %d",y);
		sem_post(&semy1);
	
}
void *processD(void* mess)
{
        
                sem_wait(&semv2);
                z=v*x6;
                printf("\nz= v*x6= %d",z);
                sem_post(&semz1);
        
}
void *processE(void* mess)
{
              
                sem_wait(&semw1);
		sem_wait(&semy1);
                y=w*y;
                printf("\ny= w*y= %d",y);
                sem_post(&semy2);
       
}
void *processF(void* mess)
{
        
                sem_wait(&semw2);
		sem_wait(&semz1);
                z=w*z;
                printf("\nz= w*z= %d",z);
                sem_post(&semz2);
}
void *processG(void* mess)
{
                sem_wait(&semy2);
		sem_wait(&semz2);
                ans=y+z;
                printf("\nans= y*z= %d",ans);       
}


int main()
{
        printf("\nx1= %d\nx2= %d\nx3= %d\nx4= %d\nx5= %d\nx6= %d\n",x1,x2,x3,x4,x5,x6);
	sem_init(&semw1,0,0);
	sem_init(&semw2,0,0);
	sem_init(&semv1,0,0);
	sem_init(&semv2,0,0);
	sem_init(&semy1,0,0);
	sem_init(&semy2,0,0);
	sem_init(&semz1,0,0);
	sem_init(&semz2,0,0);
	pthread_t pA,pB,pC,pD,pE,pF,pG;
	pthread_create( &pA,NULL,&processA,NULL);
	pthread_create( &pB,NULL,&processB,NULL);
	pthread_create( &pC,NULL,&processC,NULL);
	pthread_create( &pD,NULL,&processD,NULL);
	pthread_create( &pE,NULL,&processE,NULL);
	pthread_create( &pF,NULL,&processF,NULL);
	pthread_create( &pG,NULL,&processG,NULL);
	while(1);
	return 0;
}
