#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* vypis(FILE *subor)																							//pointer na txt subor, ktory je v zlozke
{
	char znak;
	int cisrad=1;																								 	// cislo riadku
	if((subor = fopen("file.txt", "r")) ==NULL)
	printf("NEOTVORENY SUBOR\n");
	else 
	{
	do
	{
	switch (cisrad%6) 	
		{
		case 1:printf("meno priezvisko: ");break;
		case 2:printf("SPZ: ");break;
		case 3:printf("typ auta: ");break;
		case 4:printf("cena: ");break;
		case 5:printf("datum: ");break;
		default:break;	
		}
		do{
			znak =getc(subor);
    		putchar(znak); 
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
	cisrad++;
	}while (znak!=EOF);
	rewind (subor);
}
return(subor);
}

void odmeny(FILE *subor)
{
	char znak;
	int i=1,a;
	int *p;
	long int d,e;
	float b;
	{
	scanf("%li",&d);	
	do
	{
		do{
			znak =getc(subor);
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
		i++;
	}while (znak!=EOF);
	a=i/6;
	p=(int*) malloc(sizeof(a));
	rewind(subor);
	i=1;
	
		do
	{
		a=i%6;
	switch (a) 	
		{
		case 3:
			{
				znak =getc(subor);
				if(znak=='0')
				*(p+(i/6))=1;
				else
				*(p+(i/6))=2;
				i++;
				znak =getc(subor);
			};break;
		case 5:
			{
				fscanf(subor,"%li",&e);
				if(d<(e+10000))
				*(p+(i/6))=0;									// ->2 nove auto 1 stare auto 0 nedostane odmenu  asfa
				i++;
				znak =getc(subor);
			};break;		
		
		default:{
			do{
			znak =getc(subor);
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
		i++;
		}
		break;
		}
	}while (znak!=EOF);
	rewind(subor);
	
	i=0;
	do
	{	
	if(*(p+(i/6))==0)
		{
		do{
			znak =getc(subor);
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
		i++;
		}
		else
		{
		a=i%6;
	switch (a) 	
		{
		case 0:
		{
			do{
			znak =getc(subor);
			if(znak =='\n')  
				break;  
    		putchar(znak); 
			if(znak ==EOF)  
				break; 			              
			}while (znak!=('\n')) ;
		i++;
		printf(" ");
		}
		break;
		case 1:{
			do{
			znak =getc(subor);
			if(znak =='\n')  
				break;         
    		putchar(znak); 
			if(znak ==EOF)  
				break; 		       
		}while (znak!=('\n')) ;
		i++;
		printf(" ");
		}break;
		case 3:{
			do{
			fscanf(subor,"%f",&b);
			//printf("%f  ",b);
			if(*(p+(i/6))==1) 
			printf("%.2f",(b*0.022));
			else
			printf("%.2f",(b*0.015));
			if(znak ==EOF)  
			break; 
			znak=getc(subor);
			putchar(znak)	;		           
		}while (znak!=('\n')) ;
		i++;
		}
		break;
		default:{
			do{
			znak =getc(subor);
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
		i++;
		}
		break;
		}
}
}while (znak!=EOF);
}
}

char* neviem_co(FILE *f)
{
	char c;
	int i=1,j,n,a; 																
	char *p;			
	rewind(f);
	a=sizeof(*p);
	//printf("%d\n",a);
	if (sizeof(*p)!=1)
	free(p);
	do
	{
		do{
			c =getc(f);
			if(c ==EOF)  
				break;             
		}while (c!=('\n')) ;
		i++;
	}while (c!=EOF);	
	n=i/6*8+1;
	p = (char*) malloc(n*sizeof(char));
	i=0;
	rewind(f);
	j=-1;
	do
	{
		a=i%6;
	switch (a) 	
		{
		case 1:{	
		do{
			j++;
			*(p+j) =getc(f);
			//putchar(*(p+j));
			if(*(p+j) ==EOF)  
				break; 	            																// 3 funkcia
		}while (*(p+j)!=('\n')) ;
		i++;
		}
		break;
		default:
		{	do{
			c =getc(f);	
			if(c ==EOF)  
				break;  	           
		}while (c!=('\n')) ;	
	i++;
	}break;	
		}	
	}while(c!=EOF);
return(p);
}

void spz (char*p,FILE *f)
{
	int i=1,n;
	char c;
	rewind(f);
	do{
		do{
			c =getc(f);
  		
			if(c ==EOF)  
				break;             
		}while (c!=('\n')) ;
	i++;
	}while (c!=EOF);
	i=i/6;
	n=i*8;
	for(i=0;i<n;i++)
	{
	printf("%c",*(p+i));																			//4 funkcia
	if(i%8==1)
	printf(" ");
	if(i%8==4)
	printf(" ");
	}
}

void palindrom(char*p,FILE*f)
{
int i=1,n;
	char c;
	rewind(f);
	do{
		do{
			c =getc(f);
  		
			if(c ==EOF)  
				break;             
		}while (c!=('\n')) ;
	i++;
	}while (c!=EOF);
	i=i/6;
	n=i*8;
		for(i=0;i<5;i++)
	{
	//printf("%c",*(p+i));
	if((*(p+i*8))==(*(p+i*8+6))&&(*(p+i*8+1))==(*(p+i*8+5))&&(*(p+i*8+2))==(*(p+i*8+4)))			// 5 funkcia
	printf("%c%c\n",*(p+i*8),*(p+i*8+1));
	}	
}

void pocet (char*p,FILE*f)
{
	int i=1,n,m,j,x,y,z,max;
	char c;
	rewind(f);
	char *r;
	do{
		do{
			c =getc(f);
  		
			if(c ==EOF)  
				break;             
		}while (c!=('\n')) ;
	i++;
	}while (c!=EOF);
	n=i/6*3;
	r=(char*) malloc(n*sizeof(char));
	*r=*p;
	*(r+1)=*(p+1);
	*(r+2)='1';
	n=i/6;
	
	i=0;
	m=1;
	do
	{
		i++;
		j=0;
		do
		{
		if((*(r+j*3))==(*(p+i*8))&&(*(r+j*3+1))==(*(p+i*8+1)))
		{
		*(r+j*3+2)=*(r+j*3+2)+1;
		break;
		}
		else
		{
			if(j!=(m-1))
			j++;
			else
			{
				j++;
				m++;
				*(r+j*3)=*(p+i*8);
				*(r+j*3+1)=*(p+i*8+1);
				*(r+j*3+2)='1';
				break;
			}
		
		}
		}while (j!=(m-1));
	}while(i!=(n-1));
	max=*(r+2);
	n=0;
	for(i=0;i<m;i++)
	{
		if(max<*(r+i*3+2))
		{
		max=*(r+i*3+2);
		n=i;	
		}
		
	}
	printf("%c%c %c",*(r+n*3),*(r+n*3+1),*(r+n*3+2));
}

int main()
{
	int i=0,j=0;
	char x;
	char *p;
	FILE *f;
	do
	{
		x=getchar ();
 		switch(x)
 		{
 			case 'v':f=vypis(f);i=1;break;
 			case 'o':if(i==1)odmeny(f);break;
 			case 'n':if(i==1) {p=neviem_co(f);j=1;}break;
 			case 's':if(j==1) spz(p,f);else printf("pole nie je vytvorene");break;
 			case 'p':if(j==1) palindrom(p,f);else printf("pole nie je vytvorene");break;
 			case 'z':if(j==1) pocet(p,f);else printf("pole nie je vytvorene");break;													//nefunguje tak ako ma
 			default:break;
 		}
	}while (x!='k');
	if(i==1)
	fclose(f);
return 0;	
}