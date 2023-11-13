#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#define SYS_OS "win"
#else
#define SYS_OS "lin"
#endif

int main(){
  int sys_clr;
	struct par_plain_cipher {
		char plaintext[100];
		char ciphertxt[250];
	} par;
	char cifras[6][21] = {"César", "Atbash", "Affine", "Morse", "Vigenère", "Quadrado de Políbio"};
	FILE *fptr = fopen("cifras.txt", "a");
  
	while (1) {
    printf("Selecione uma opção para cifrar sua frase:\n\
1. César;\n\
2. Atbash;\n\
3. Affine;\n\
4. Morse;\n\
5. Vigenère;\n\
6. Quadrado de Políbio;\n\
0. Sair do programa.\n");
    
    int choice;
    
    while (1) {
      int input_test = scanf("%d", &choice);
      getchar();
      
		  if (!(input_test) || ((choice < 0) || (choice > 6))) {
        printf("Opção inválida. Tente novamente.\n");
        fflush(stdin);
		  }
		  else if (choice == 0) {
		    printf("Ok. Até mais.\n");
        fclose(fptr);
        return 0;
		  }
  		else{
  			fflush(stdin);
  		  break;
  		}
    }
    
    if (SYS_OS == "win") {
      sys_clr = system("cls");
    }
    else {
      sys_clr = system("clear");
    }
    
  	printf("%s\n", cifras[choice - 1]);
    
  	char frase[100];
    
  	printf("digite a frase: ");
    
  	int teste_frase = scanf("%[^\n]", frase);
    
  	strcpy(par.plaintext, frase);
    getchar();
    
    if (SYS_OS == "win") {
      sys_clr = system("cls");
    }
    else {
      sys_clr = system("clear");
    }
    
    switch (choice) {
      case 1:
        printf("A frase \"%s\" em %s é: ", frase, cifras[choice - 1]);
        
        for (int i = 0; i < strlen(frase); i++) {
          int letter = (int)frase[i];
          
          if (65 <= letter && letter <= 90) {
            frase[i] = (char)((letter + 2 - 64) % 26 + 65);
          }
          else if (97 <= letter && letter <= 122) {
            frase[i] = (char)((letter + 2 - 96) % 26 + 97);
          }
          else {
            frase[i] = (char)(letter);
          }
        }
        
        printf("%s\n", frase);
        strcpy(par.ciphertxt, frase);
        break;
      
      case 2:
        printf("A frase \"%s\" em %s é: ", frase, cifras[choice - 1]);
        
        for (int i = 0; i < strlen(frase); i++) {
          int letter = (int)frase[i];
          
          if (65 <= letter && letter <= 90) {
            frase[i] = (char)(-letter + 155);
          }
          else if (97 <= letter && letter <= 122) {
            frase[i] = (char)(-letter + 219);
          }
          else {
            frase[i] = (char)letter;
          }
        }
        
        printf("%s\n", frase);
        strcpy(par.ciphertxt, frase);
        break;
      
      case 3:
        printf("Affine\n");
        printf("Insira valores inteiros para as chaves A e B: ");
        
        int chave_a, chave_b;
        int teste_scan = scanf("%d %d", &chave_a, &chave_b);
        
        getchar();
        
        if (SYS_OS == "win") {
          sys_clr = system("cls");
        }
        else {
          sys_clr = system("clear");
        }
        
        if (teste_scan != 2) {
          printf("Insira valores válidos.\n");
          break;
        }
        
        if (!(chave_a % 2 && chave_a % 13)) {
          printf("Sua chave A é inválida. Entre com um número cujo MDC entre ele e 26 seja 1.\n");
          break;
        }
        
        printf("A frase \"%s\" em %s é: ", frase, cifras[choice - 1]);
        
        for (int i = 0; i < strlen(frase); i++) {
          int letter = (int)frase[i];
          
          if (65 <= letter && letter <= 90) {
            frase[i] = (char)(((chave_a * (letter % 65) + chave_b) % 26) + 65);
          }
          else if (97 <= letter && letter <= 122) {
            frase[i] = (char)(((chave_a * (letter % 97) + chave_b) % 26) + 97);
          }
          else {
            frase[i] = (char)letter;
          }
        }
        
        printf("%s\n", frase);
        strcpy(par.ciphertxt, frase);
        break;
      
      case 4:
        printf("A frase \"%s\" em %s é: ", frase, cifras[choice - 1]);
        
        char morse[36][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", 
        "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", 
        ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
        char ciphertxt[250] = "";
        
        for (int i = 0; i < strlen(frase); i++) {
          int letter = (int)tolower(frase[i]);
          
          if (97 <= letter && letter <= 122) {
            strcat(ciphertxt, morse[letter % 97]);
            strcat(ciphertxt, " ");
          }
          else if (48 <= letter && letter <= 57) {
            strcat(ciphertxt, morse[letter - 22]);
            strcat(ciphertxt, " ");
          }
          else if (letter == 32) {
            strcat(ciphertxt, "/ ");
          }
        }
        
        printf("%s\n", ciphertxt);
        strcpy(par.ciphertxt, ciphertxt);
        break;
      
      case 5:
        printf("Vigenère\n");
        printf("Digite a palavra a ser usada como chave para cifrar a frase: ");
        
        char chave[46];
        int teste_vig = scanf("%s", chave);
        
        getchar();
        
        if (!teste_vig) {
          printf("Digite uma chave válida.\n");
          break;
        }
        
        if (SYS_OS == "win") {
          sys_clr = system("cls");
        }
        else {
          sys_clr = system("clear");
        }
        
        for (int i = 0; i < strlen(chave); i++) {
          chave[i] = tolower(chave[i]);
        }
        
        int delta = 0;
        
        printf("A frase \"%s\" em %s cifrada com a chave \"%s\" é: ", frase, cifras[choice - 1], chave);
        
        for (int i = 0; i < strlen(frase); i++) {
          int cripto = (frase[i] + chave[(i - delta) % strlen(chave)] - 1);
          
          if ((97 <= frase[i] && frase[i] <= 122)) {
            if (cripto > 218) {
              cripto -= 122;
            }
            else {
              cripto -= 96;
            }
            
            frase[i] = (char)cripto;
          }
          else if ((65 <= frase[i] && frase[i] <= 90)) {
            if (cripto >= 187) {
              cripto -= 122;
            }
            else {
              cripto -= 96;
            }
            
            frase[i] = (char)cripto;
          }
          else {
            delta++;
          }
        }
        
        printf("%s\n", frase);
        strcpy(par.ciphertxt, frase);
        break;
      
      case 6:
        printf("A frase \"%s\" em %s é: ", frase, cifras[choice - 1]);
        
        char polybius[26][3] = {"11", "12", "13", "14", "15", "21", "22", "23", "24", "24", "25", "31", "32", "33", 
        "34", "35", "41", "42", "43", "44", "45", "51", "52", "53", "54", "55"};
        char poly_ciphertxt[250] = "";
        
        for (int i = 0; i < strlen(frase); i++) {
          int letter = (int)tolower(frase[i]);
          
          if (97 <= letter && letter <= 122) {
            strcat(poly_ciphertxt, polybius[letter % 97]);
            strcat(poly_ciphertxt, " ");
          }
          else if (letter == 32) {
            strcat(poly_ciphertxt, "/ ");
          }
        }
        
        printf("%s\n", poly_ciphertxt);
        strcpy(par.ciphertxt, poly_ciphertxt);
        break;
    }
    
    fflush(stdin);
    fprintf(fptr, "%s: plaintext: \"%s\"; ciphertext: \"%s\"\n", cifras[choice - 1], par.plaintext, par.ciphertxt);
    printf("Continuar?(Y/n) ");
    
    char continuar;
    int cont_test = scanf("%c", &continuar);
    
    continuar = tolower(continuar);
    
    if (continuar == 'n') {
      printf("Ok. Até mais!\n");
      fclose(fptr);
      break;
    }
    
    if (SYS_OS == "win") {
      sys_clr = system("cls");
    }
    else {
      sys_clr = system("clear");
    }
  }
  
  return 0;
}