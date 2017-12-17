#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* vypis(FILE *subor)																							//pointer na txt subor, ktory je v zlozke
{
	char znak;
	int cisrad=1;																								// cislo riadku
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
	printf("\n");
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

void spz (char*pole_SPZ,FILE *subor)
{
	int pocet_riadkov=1,pocet_zaznamov,poradie_znaku,pocet_znakov;
	char znak;
	rewind(subor);
	do{
		do{
			znak =getc(subor);
  		
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
	pocet_riadkov++;
	}while (znak!=EOF);
	pocet_zaznamov=pocet_riadkov/6;
	pocet_znakov=pocet_zaznamov*8;
	for(poradie_znaku=0;poradie_znaku<pocet_znakov;poradie_znaku++)
	{
	printf("%c",*(pole_SPZ+poradie_znaku));																			//4 funkcia
	if(poradie_znaku%8==1)
	printf(" ");
	if(poradie_znaku%8==4)
	printf(" ");
	}
}

void palindrom(char*pole_SPZ,FILE*subor)
{
	int pocet_riadkov=1,pocet_zaznamov,poradie_zaznamu;
	char znak;
	rewind(subor);
	
	do
	{
		do
		{
			znak =getc(subor);
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
		pocet_riadkov++;
	}while (znak!=EOF);
	pocet_zaznamov=pocet_riadkov/6;
	for(poradie_zaznamu=0;poradie_zaznamu<pocet_zaznamov;poradie_zaznamu++)
	{
	if((*(pole_SPZ+poradie_zaznamu*8))==(*(pole_SPZ+poradie_zaznamu*8+6))&&(*(pole_SPZ+poradie_zaznamu*8+1))==(*(pole_SPZ+poradie_zaznamu*8+5))&&(*(pole_SPZ+poradie_zaznamu*8+2))==(*(pole_SPZ+poradie_zaznamu*8+4)))			// 5 funkcia
	printf("%c%c\n",*(pole_SPZ+poradie_zaznamu*8),*(pole_SPZ+poradie_zaznamu*8+1));
	}	
}

void pocet (char*pole_SPZ,FILE*subor)
{
	int pocet_riadkov=1,velkost_histogramu,pocet_zaznamov,pocet_prv_his,poradie_SPZ_v_poli,poradie_max_prvku_v_his,poradie_SPZ_histogram,poradie_prv_v_hist,max;
	char znak;
	char *histogram;
	rewind(subor);
	
	do
	{
		do
		{
			znak =getc(subor);
			if(znak ==EOF)  
				break;             
		}while (znak!=('\n')) ;
		pocet_riadkov++;
	}while (znak!=EOF);
	pocet_zaznamov=pocet_riadkov/6;
	velkost_histogramu=pocet_zaznamov*3;
	histogram=(char*) malloc(velkost_histogramu*sizeof(char));
	
	*histogram=*pole_SPZ;
	*(histogram+1)=*(pole_SPZ+1);
	*(histogram+2)='1';
	poradie_SPZ_v_poli=0;
	pocet_prv_his=1;
	do
	{
		poradie_SPZ_v_poli++;
		poradie_SPZ_histogram=0;
		do
		{
			if((*(histogram+poradie_SPZ_histogram*3))==(*(pole_SPZ+poradie_SPZ_v_poli*8))&&(*(histogram+poradie_SPZ_histogram*3+1))==(*(pole_SPZ+poradie_SPZ_v_poli*8+1)))
			{
				*(histogram+poradie_SPZ_histogram*3+2)=*(histogram+poradie_SPZ_histogram*3+2)+1;
				break;
			}
			else
			{
				if(poradie_SPZ_histogram!=(pocet_prv_his-1))
					poradie_SPZ_histogram++;
				else
				{
					poradie_SPZ_histogram++;
					pocet_prv_his++;
					*(histogram+poradie_SPZ_histogram*3)=*(pole_SPZ+poradie_SPZ_v_poli*8);
					*(histogram+poradie_SPZ_histogram*3+1)=*(pole_SPZ+poradie_SPZ_v_poli*8+1);
					*(histogram+poradie_SPZ_histogram*3+2)='1';
					break;
				}
			}
		}while (poradie_SPZ_histogram!=(pocet_prv_his-1));
	}while(poradie_SPZ_v_poli!=(pocet_zaznamov-1));
	max=*(histogram+2);
	poradie_max_prvku_v_his=0;
	
	for(poradie_prv_v_hist=0;poradie_prv_v_hist<pocet_prv_his;poradie_prv_v_hist++)
	{
		if(max<*(histogram+poradie_prv_v_hist*3+2))
		{
			max=*(histogram+poradie_prv_v_hist*3+2);
			poradie_max_prvku_v_his=poradie_prv_v_hist;	
		}	
	}
	printf("%c%c %c \n",*(histogram+poradie_max_prvku_v_his*3),*(histogram+poradie_max_prvku_v_his*3+1),*(histogram+poradie_max_prvku_v_his*3+2));
}

int main()
{
	int otvoreny_subor=0,vytvorene_pole=0;
	char znak;
	char *pole_SPZ;
	FILE *subor;
	do
	{
		znak=getchar ();
 		switch(znak)
 		{
 			case 'v':subor=vypis(subor);otvoreny_subor=1;break;
 			case 'o':if(otvoreny_subor==1)odmeny(subor);break;
 			case 'n':if(otvoreny_subor==1) {pole_SPZ=nacitaj(subor);vytvorene_pole=1;}break;
 			case 's':if(vytvorene_pole==1) spz(pole_SPZ,subor);else printf("pole nie je vytvorene \n");break;
 			case 'p':if(vytvorene_pole==1) palindrom(pole_SPZ,subor);else printf("pole nie je vytvorene \n");break;
 			case 'z':if(vytvorene_pole==1) pocet(pole_SPZ,subor);else printf("pole nie je vytvorene \n");break;													//funguje tak ako ma
 			default:break;
 		}
	}while (znak!='k');
	if(otvoreny_subor==1)
		fclose(subor);
	return 0;	
}
