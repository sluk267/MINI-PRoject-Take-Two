#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
        //decryption scheme
        if((c1 == 'T')&&(c2=='T')) {
            fprintf(decryptedOutput, "\t");
        } else if((c2 >= 65) && (c2 <= 90)) {
            printf("%c %c,", (c1), (c2));
            outChar = (((c1 - '0') * 16) + (c2-55)) + 16;
            if(outChar > 127){
                outChar = (outChar - 144) + 32;
            }
            fprintf(decryptedOutput, "%c", outChar);
        } else {
            outChar = (((c1 - '0') * 16) + (c2-'0')) + 16;
            if(outChar > 127){
                outChar = (outChar - 144) + 32;
            }
            fprintf(decryptedOutput, "%c", outChar);
        }
        
    }
    fclose(input);
    fclose(decryptedOutput);

}

int main(){
    char fname[100],EOD, Extension;
    int i = 0;
    FILE* Outputtxt;
    memset(fname, 0, 100); 



    
   
    printf("Enter file name: ");
    scanf("-%c ",&EOD);//asks user for Utility Type
    gets(fname);//asks user for filename

if (EOD == 'E' || EOD == '\0'){
while ((fname[i] != '.') &&(fname[i] !='\0')){
      i++;
}
if (fname[i] == '.'){
   strcpy(fname+i, ".crp");
}
else{
    strcat(fname,".crp");
}
}

else if (EOD == 'D'){
while ((fname[i] != '.') &&(fname[i] !='\0')){
      i++;
}
if (fname[i] == '.'){
   strcpy(fname+i, ".txt");
}
else{
    strcat(fname,".txt");
}
}
else{
    printf("Sorry That Input Was Not Accepted\nPlease Re Run");
}
     
    Outputtxt = fopen(fname, "w");//Opens the file from where the text will be written.
    FILE *Inputtxt = fopen("data.txt", "r");
    decrypt(Inputtxt, Outputtxt);

}