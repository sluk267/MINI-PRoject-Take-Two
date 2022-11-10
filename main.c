#include <stdio.h>
#include <string.h>

void encrypt(FILE *input){
    int c1;
    //creates encrypted output file (prints to keys.txt for now)
    FILE *encryptedOutput;
    encryptedOutput = fopen("keys.txt", "w");
    //cycles through characters in file one at a time
    for(c1 = fgetc(input); c1 != EOF; c1 = fgetc(input)){
        //prints all characters to console for convenience 
        printf("%c", c1);
        if(c1 == 10) {
            //check for linux carriage return
            fprintf(encryptedOutput, "\n");
        } else if(c1 == 9) {
            //check for TAB
            fprintf(encryptedOutput, "TT");
        } else if((c1-16) < 32) {
            //encryption condition 1 (printing with %X prints the hex value instead of decimal, also capital letters)
            fprintf(encryptedOutput, "%X",((c1 - 16) - 32) + 144);
        } else {
            //encryption normal case
            fprintf(encryptedOutput, "%X",(c1 - 16));
        }
    }
    //close both files when finished editing 
    fclose(input);
    fclose(encryptedOutput);
}

void decrypt(FILE *input, FILE *output) {

    char c1, c2;
    int outChar;
    //opens files and begin editing the output file (keys.txt)
    FILE *decryptedOutput;
    decryptedOutput = output;

    // grabs 2 integer values in a row and prints the corresponding character 
    for(c1 = fgetc(input), c2 = fgetc(input); (c1 != EOF)&&(c2 != EOF); c1 = fgetc(input),c2 = fgetc(input)){
        printf("%d %d,", ((c1 -'0') * 16), (c2 - '0'));
        if((c1 == 'T')&&(c2=='T')) {
            fprintf(decryptedOutput, "\t");
        } else {
            //decryption scheme
            outChar = (((c1 - '0') * 16) + (c2-'0')) + 16;
            if(outChar > 127){
                outChar = (outChar - 144) + 32;
            }
            fprintf(decryptedOutput, "%d,", outChar);
        }
        
    }
    fclose(input);
    fclose(decryptedOutput);

}

int main(){
//     char choice, filename[100], extension[100];
//     printf("Would you like to enrypt (-E) or decrypt (-D)\n also what nam: ");
//     scanf("-%c %c.%c", &choice, &filename, &extension);
// printf ("\n\n-%c %c.%c\n\n\n", choice, filename, extension);

//printf("%c\n", filename);
    

    FILE *Inputtxt = fopen("data.txt", "r");
    char name;
    // printf("What would you like to call your data: ");
    // scanf("%c", &name);
    // int rename(const char * oldname, const char * newname);
    FILE *Outputxt;
    Outputxt = fopen("output.txt","w");
    decrypt(Inputtxt, Outputxt);

}