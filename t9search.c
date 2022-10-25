#include <stdlib.h>
#include <stdio.h>

#define MAX 101 

typedef struct{
    char jmeno[MAX];
    char cislo[MAX];
}TKontakt;

TKontakt kontakty[42];

// fce na porovnani retezcu
int strcomp(char *str1, char *str2){
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

// fce na kontrolu zadanych parametru
int arg_control(int argc, char* argv[]){
    if(argc > 2){
        return 1;
    }
    else{
        if(argc == 1){
            return 2; // vypise se vsechno
        }
        else {
            if(argc == 2){
                int i = 0;
                while (argv[1][i] != '\0'){
                    if(argv[1][i] < '0' || argv[1][i] > '9'){
                        return 1;
                    }
                    else i++;
                }
            }   
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

// fce na kopirovani retezcu
char* strcopy(char* str1, const char* str2){
    int i = 0; 
    while (str2[i] != '\0')
    {
        str1[i] = str2[i];
        i++;
    }
 
    // odstranime '\n' a nahradime ho '\0'
    str1[i-1] = '\0';
 
    return str1;
}

// fce na prevod retezce na mala pismena
char* lowercase(char *str){
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
        }
    }
    return str;
}

// fce na vyhledani podretezce ve jmene kontaktu
int search(char* radek, char* sub)
{
    char pole[] = "+ adgjmptw";

    int cislo, pocet;
    char znak[1];
    char kontrola;
    int nalezeno = 0;

    if(strdel(sub) == 0) return 1;

    for(int i = 0; i <strdel(radek); i++)
    {
        znak[0] = sub[0];
        cislo = atoi(znak);
        kontrola = pole[cislo];
        if(cislo == 9 || cislo == 7) pocet = 4;
        else if(cislo == 1) return 0; 
        else if(cislo == 0) return 0;
        else pocet = 3;

        nalezeno = 0;

        for(int j = 0; j < pocet; j++)
        {
            if(radek[i] == kontrola + j) {
                nalezeno = 1;             
                break;

            }
        }
        if(nalezeno == 1) //nalezen pocatek potencionalniho substringu
        {
            for(int k = 1; k < strdel(sub); k++) // tenhle cyklus nam hlida, aby se hledal cely zbytek substringu 
            {
                if(i + k >= strdel(radek)) return 0;
                znak[0] = sub[k]; 
                cislo = atoi(znak);
                kontrola = pole[cislo];
                nalezeno = 0; 

                if(cislo == 9 || cislo == 7) pocet = 4;
                else if(cislo == 1) return 0; 
                else if(cislo == 0) return 0; 
                else pocet = 3;

                for(int l = 0; l < pocet; l++)
                {
                    if(radek[i + k] == (kontrola + l))
                    {
                        nalezeno = 1;
                        break;
                    }  
                    else nalezeno = 0;
                }
                if (nalezeno == 0) break;                
            }
            if(nalezeno == 1) return 1;            
        }
    }
    return 0; 
}

// funkce na vyhledani substringu v cisle
int number_search(char* num, char* subnum){ 
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
                return 1; // vraci 1, pokud se substring v cisle nachazi
            }
        }
        p_1++;
    }
    return 0; // vrací 0, pokud se substring nenachazi v cisle
}

// void trim(char* radek)
// {
//   for(int i = 0; i <strdel(radek); i++)
//   { 
//     if (radek[i] == '\n') radek[i] = '\0';
//   }
// }

int main(int argc, char *argv[]){
    char radek[MAX];
    int i = 0, pocet_radku = 0, zmena = 0;

    if(arg_control(argc, argv) == 1){ // pokud funkce vrati 1, znamena to, ze nejaky z parametru je spatne zadany
        fprintf(stderr, "ERROR wrong ARGS");
        return 1;
    }
    else{
        while(fgets(radek, 150, stdin) != NULL){ //nacitani ze souboru
            if(strdel(radek) > MAX){ //moc dlouhe jmeno/cislo
                fprintf(stderr, "ERROR long NAME/NUMBER");
                    return 1;
            }
            else{    
                zmena = 0; // 0 -> jeste jsme nevypsali, 1 -> uz jsme vypsali
                if(pocet_radku % 2 == 0){
                    strcopy(kontakty[i].jmeno, lowercase(radek));
                //    trim(kontakty[i].jmeno);
                    pocet_radku++;                                  
                }
                else{
                    strcopy(kontakty[i].cislo, radek);
                    pocet_radku++;
                    i++;    
                }
            }
        }        
    }

    if(arg_control(argc, argv) == 2){ // pokud nam funkce vrati 2, tak se vypisuje cely seznam kontaktu
        for(i = 0; i < pocet_radku/2; i++){
            printf("%s, %s", kontakty[i].jmeno, kontakty[i].cislo);
            printf("\n");
        }
        return 0;        
    }

    for(i = 0; i < pocet_radku/2; i++){ 
        if(search(kontakty[i].jmeno, argv[1]) == 1){ // pokud nam funkce vrati 1, znamena to, ze kontakt obsahuje substring 
            printf("%s, %s", kontakty[i].jmeno, kontakty[i].cislo);
            printf("\n");
            zmena++;
            continue;
        }
        else{
            if(number_search(kontakty[i].cislo, argv[1]) == 1){ // pokud nam funkce vrati 1, znamena to, ze kontakt obsahuje substring 
                printf("%s, %s", kontakty[i].jmeno, kontakty[i].cislo);
                printf("\n");
                zmena++;
            }
        } 
    }

    if(zmena == 0){
        printf("Not found");
    }

    return 0;
}
