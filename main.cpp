#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* vypis(FILE *subor)																							//pointer na txt subor, ktory je v zlozke
{
	char znak;
	int cisrad=1;																							// cislo riadku
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
		
		do
		{
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
	int cislo_riadku=1,cislo_zaznamu;
	int *typ_auta;																// toto pole obsahuje informaciu o type auta daneho zaznamu neskor bude obsahovat hodnoty 1/2/0 podla kt program vyrata,aku odmenu zakaznik dostane
	long int zadany_datum,datum_zo_zaznamu,pocet_zaznamov;
	float odmena;
	
	scanf("%li",&zadany_datum);	
	do
	{
		
		do
		{
			
			znak =getc(subor);
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n'));
		
		pocet_zaznamov++;
	}while (znak!=EOF);
	
	pocet_zaznamov=pocet_zaznamov/6;
	typ_auta=(int*) malloc(sizeof(pocet_zaznamov));
	rewind(subor);
	
	cislo_riadku=1;
	do
	{
		
		switch (cislo_riadku%6) 	
		{
			
			case 3:
			{
				znak =getc(subor);
				if(znak=='0')
				*(typ_auta+(cislo_riadku/6))=1;
				else
				*(typ_auta+(cislo_riadku/6))=2;
				cislo_riadku++;
				znak =getc(subor);
			};break;
			
			case 5:
			{
				fscanf(subor,"%li",&datum_zo_zaznamu);
				if(zadany_datum<(datum_zo_zaznamu+10000))
				*(typ_auta+(cislo_riadku/6))=0;									// ->2 nove auto 1 stare auto 0 nedostane odmenu
				cislo_riadku++;
				znak =getc(subor);
			};break;		
		
			default:
			{
				do
				{
					znak =getc(subor);
					if(znak ==EOF)  
					break;             
				}while (znak!=('\n')) ;
				cislo_riadku++;
			}break;
			
		}
	}while (znak!=EOF);
	rewind(subor);
	
	cislo_riadku=0;
	do
	{	
		if(*(typ_auta+(cislo_riadku/6))==0)
		{
			do
			{
				znak =getc(subor);
				if(znak ==EOF)  
					break;             
			}while (znak!=('\n')) ;
			cislo_riadku++;
		}
			else
		{
			switch (cislo_riadku%6) 	
			{
				case 0:
				{
					do
					{
						znak =getc(subor);
						if(znak =='\n')  
							break;  
    					putchar(znak); 
						if(znak ==EOF)  
							break; 			              
					}while (znak!=('\n')) ;
					cislo_riadku++;
					printf(" ");
				}break;
				
				case 1:
				{
					do
					{
						znak =getc(subor);
						if(znak =='\n')  
							break;         
    					putchar(znak); 
						if(znak ==EOF)  
						break; 		       
					}while (znak!=('\n')) ;
					cislo_riadku++;
					printf(" ");
				}break;
				
				case 3:
				{
					do	
					{
						fscanf(subor,"%f",&odmena);
						if(*(typ_auta+(cislo_riadku/6))==1) 
						printf("%.2f",(odmena*0.022));
						else
						printf("%.2f",(odmena*0.015));
						if(znak ==EOF)  
						break; 
						znak=getc(subor);
						putchar(znak)	;		           
					}while (znak!=('\n')) ;
					cislo_riadku++;
				}break;
				
				default:
				{
					do
					{
						znak =getc(subor);
						if(znak ==EOF)  
							break;             
					}while (znak!=('\n')) ;
					cislo_riadku++;
				}break;
			}
		}
	}while (znak!=EOF);
}

char* nacitaj(FILE *subor)
{
	char znak;
	int riadok,poradie_znaku,pocet_riadkov,velkost_pola; 																
	char *pole_SPZ;	
			
	rewind(subor);
	if (sizeof(*pole_SPZ)!=1)
		free(pole_SPZ);
	do
	{
		do
		{
			znak=getc(subor);
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
		pocet_riadkov++;
	}while (znak!=EOF);	
	velkost_pola=pocet_riadkov/6*8+1;
	pole_SPZ = (char*) malloc(velkost_pola*sizeof(char));
	riadok=0;
	poradie_znaku=-1;
	rewind(subor);
	
	do
	{
		switch (riadok%6) 	
		{
			case 1:
			{	
				do
				{
					poradie_znaku++;
					*(pole_SPZ+poradie_znaku) =getc(subor);
					if(*(pole_SPZ+poradie_znaku) ==EOF)  
						break; 	            																
				}while (*(pole_SPZ+poradie_znaku)!=('\n')) ;
				riadok++;
			}break;
		
			default:
			{	
				do
				{
					znak =getc(subor);	
					if(znak ==EOF)  
						break;  	           
				}while (znak!=('\n')) ;	
				riadok++;
			}break;	
		}	
	}while(znak!=EOF);
	return(pole_SPZ);
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
 			case 'n':if(i==1) {p=nacitaj(f);j=1;}break;
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
