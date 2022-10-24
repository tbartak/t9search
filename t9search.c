#include <stdlib.h>
#include <stdio.h>
// #include <string.h>

#define MAX 101 

typedef struct{
    char jmeno[MAX];
    char cislo[MAX];
}TKontakt;

TKontakt kontakty[42];

// fce na porovnani retezcu
int strcmp(char *str1, char *str2){
    while( ( *str1 != '\0' && *str2 != '\0' ) && *str1 == *str2 )
    {
        str1++;
        str2++;
    }
    if(*str1 == *str2)
    {
        return 0; // retezce jsou stejne
    }
    else
    {
        return *str1 - *str2;
    }
}

int arg_control(int argc, char* argv[]){
    // kontrola jestli josu argumenty zadané správně
    if(argc > 3){
        return 1;
    }
    else{
        if(argc < 2){
            return 1;
        }
        else{
            if(argc == 2 && strcmp(argv[1], "seznam.txt") == 0){ // kdyžtak oddělat kontrolu názvu souboru
            // pokud jsou jen dva parametry a druhý je soubor, tak nám program vypíše všechny rádky v souboru
            // vyměnit potom za for cyklus, který nám projede celou strukturu a vypíše všechno
                return 2; // vypíše se všechno
	        }
	        else {
		        if(argc == 2 && strcmp(argv[1], "seznam.txt") != 0){
                    return 1;
                }
                else{
                    if(argc == 3 && strcmp(argv[2], "seznam.txt") == 0){
                        int i = 0;
		                while (argv[1][i] != '\0'){
			                if(argv[1][i] < '0' || argv[1][i] > '9'){
			        	        return 1;
			                }
                            else i++;
		                }
                    }
                    else{
                        int i = 0;
		                while (argv[1][i] != '\0'){
			                if(argv[1][i] < '0' || argv[1][i] > '9'){
			        	        return 1;
			                }
                            else i++;
		                }
                        return 1;
                    }    
                }
	        }    
        }
    }
    return 0;
}

// fce na urceni jestli je retezec tvoreny pismeny
int isalpha(char *str){
    int i = 0;
    while(str[i] != '\0'){
		if(str[i] <= 'a' && str[i] >= 'z') {
			return 1;
		}
    }    
    return 0;
}

// fce na delku retezce
int strdel(char *str){
	int i = 0;
	if(str[0] == '\0') return 0;
	else{
		while(str[i] != '\0'){
			i++;
		}
	}
	return i;
}

// Function to implement `strcpy()` function
char* strcpy(char* destination, const char* source)
{ 
    // take a pointer pointing to the beginning of the destination string
    char *p_destination = destination;
 
    // copy the C-string pointed by source into the array
    // pointed by destination
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // include the terminating null character
    *destination = '\0';
 
    // the destination is returned by standard `strcpy()`
    return p_destination;
}

char* lowercase(char *str){
    
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
        }
    }
    return str;
}

int search(char* radek, char* sub)
{
    char pole[] = "+ adgjmptw";

    int cislo, pocet;
    char znak[1];
    char kontrola;
    int nalezeno = 0;

    if(strdel(sub) == 0) return 1;

    //převést radek na mala pismena pro zjednoduseni

    for(int i = 0; i <strdel(radek); i++)
    {
        znak[0] = sub[0];
        cislo = atoi(znak);
        kontrola = pole[cislo];
        if(cislo == 9 || cislo == 7) pocet = 4;
        else if(cislo == 1) return 0; 
        else if(cislo == 0) return 0; //0
        else pocet = 3;

        nalezeno = 0;
        
        // printf("x1");

        for(int j = 0; j < pocet; j++)
        {
            if(radek[i] == kontrola + j) {
                nalezeno = 1;             
                break;

            }
        }
        if(nalezeno == 1) //nalezen počátek potenciálního podřetězce
        {
            // printf("x2");
            for(int k = 0; k < strdel(sub); k++) // tenhle cyklus nám hlídá, aby se hledal celej zbytek substringu 
            // změnil bych hodnotu k z 0 na 1, jinak by nedával řádek 199 smysl, protože bychom zkoumali znovu to stejné co už jsme našli
            {
                if(i + k >= strdel(radek)) return 0; // nevím, jestli by nemělo být jen >, protože když by to byli např. poslední dvě písmena řetězce, tak by se to pokazilo ? nejspíš xD, dalo by se napsat asi i jako i + strdel(sub) > strdel(radek)
                //zkontrolovat znaky radek[i+k] a sub[k]
                znak[0] = sub[k]; // v prvním průchodu cyklem se do znaku uloží první číslo argumentu, ale to už jsme našli
                cislo = atoi(znak);
                kontrola = pole[cislo];
                nalezeno = 0; // !!přidáno!!
                if(cislo == 9 || cislo == 7) pocet = 4;
                else if(cislo == 1) return 0; 
                else if(cislo == 0) return 0; //0
                else pocet = 3;
                
                // printf("x3");

                for(int l = 0; l < pocet; l++)
                {
                    // printf("x4");
                    // nalezeno = 0; 
                    if(radek[i + k] == (kontrola + l)) // správně imo
                    {
                        // printf("%c", (kontrola + l));
                        nalezeno = 1;
                        break;
                    }  
                    else nalezeno = 0; // !!přidáno!! // v podstatě pořád to samé jako předtím, akorát přemístěné a napsané o něco jinak
                }
                // někde by tady podle mě měla být podmínka, že pokud je nalezeno == 1, tak se pokračuje, jinak break; je zbytečný pokračovat dál, když písmeno po i už není ze substringu
                if (nalezeno == 0) break;                
            }
            if(nalezeno == 1) return 1;            
        }
    }
    return 0; 
}

int number_search(char* num, char* subnum){ // funkce na vyhledání argv[1] v řádku s číslem
    int i = 0, j = 0;
    char *p_1, *p_2, *p_3;
    p_1 = num;
    p_2 = subnum;
    for(i = 0; i < strdel(num); i++){
        if(*p_1 == *p_2){
            p_3 = p_1;
            for(j = 0; j < strdel(subnum); j++){
                if(*p_3 == *p_2){
                    p_2++;
                    p_3++;
                }
                else break;
            }
            p_2 = subnum;
            if(j == strdel(subnum)){
                return 1; // vrací 1 pokud se argv[1] v čísle nachází
            }
        }
        p_1++;
    }
    return 0; // vrací 0 pokud se argv[1] NEnachází v čísle
}

void trim(char* radek)
{
  for(int i = 0; i <strdel(radek); i++)
  { 
    if (radek[i] == '\n') radek[i] = '\0';
  }
}

int main(int argc, char *argv[]){
    char radek[MAX];
    int i = 0, pocet_radku = 0, zmena = 0;
    // printf("Pocet argumentu: %d\n", argc);    
    // printf("Prvni argument: %s\n", argv[0]);
    // printf("Druhy argument: %s\n", argv[1]);
    // printf("Treti argument: %s\n", argv[2]);
    // // char soubor[] = *argv[2];
    // FILE* f; 
    // f = fopen(argv[2], "r");

    if(arg_control(argc, argv) == 0){ // tohle potom předělat na 1
        fprintf(stderr, "ERROR wrong ARGS");
        return 1;
    }
    else{
        while(fgets(radek, 150, stdin) != NULL){ //nacitani ze souboru
            if(strdel(radek) > MAX){ //moc dlouhe jmeno/cislo
                fprintf(stderr, "ERROR long NAME/NUMBER");
                    return 1;
            }
            else{    // na sudych radcich zacinajicich na 0 jsou jmena kontaktu, na lichych radcich zacinajicich 1 jsou cisla kontaktu
            // přiřazení do struktury, podle toho, jestli je řádek tvořený písmeny nebo čísly
                zmena = 0; // pokud bude změna 0, tak můžeme vypsat celý kontakt, jak jméno, tak číslo, pokud bude != 0 tak už jsme toto číslo a jméno vypisovali, změna se mění v případě, že nám funkce vrátí pravdivé hodnoty, že se buďto ve jméně nebo čísle nachází podřetězec
                if(pocet_radku % 2 == 0){
                    strcpy(kontakty[i].jmeno, lowercase(radek));
                    trim(kontakty[i].jmeno);     
                    pocet_radku++;  
                                  
                }
                else{
                    strcpy(kontakty[i].cislo, radek);
            
                    pocet_radku++;
                    i++;    
                }
            }
        }        
    }

    if(arg_control(argc, argv) == 2){
        for(i = 0; i < pocet_radku/2; i++){
            printf("%s, %s", kontakty[i].jmeno, kontakty[i].cislo);

        }
        return 0;        
    }

    for(i = 0; i < pocet_radku/2; i++){
        if(search(kontakty[i].jmeno, argv[1]) == 1){
            printf("%s, %s", kontakty[i].jmeno, kontakty[i].cislo);
            zmena++;
            continue;
        }
        else{
            if(number_search(kontakty[i].cislo, argv[1]) == 1 /*&& zmena == 0*/){
                printf("%s, %s", kontakty[i].jmeno, kontakty[i].cislo);
            }
        } 
    }


    // for(i = 0; i < 2; i++){
    // printf("Jmeno a Prijmeni: %s", kontakty[i].jmeno);
    // printf("Cislo: %s", kontakty[i].cislo);
    // }  

    

    return 0;
}