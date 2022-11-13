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
            //printf("%c %c,", (c1), (c2));                            //NOTE IS COMMENTED OUT JUST FOR WHILE I MAKE UI
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
void Graphics1(){
printf("\n|-----------------------------------------------------------------------------------------------|");
printf("\n|                                                                                               |");
printf("\n|                                    WELCOME TO CRYPTOMAGIC                                     |");
printf("\n|                                  Created by: Jacob and Paul                                   |");
printf("\n|                                                                                               |");
printf("\n| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |");
printf("\n|                                                                                               |");
printf("\n|             Here Are Your Options:                                                            |");
printf("\n|                      1. -E Will Encrypt Your File                                             |");
printf("\n|                      2. -D Will Decrypt Your Enrypted File                                    |");
printf("\n|                      3. Not Choosing Will Encrpt Your File                                    |");
printf("\n|                                                                                               |");
printf("\n|             Please Enter In This Format:                                                      |");
printf("\n|                      <Option> <Filename>                                                      |");
printf("\n|             OR                <Filename> (Only Do This If You Wish To Encrypt File)           |");
printf("\n|                                                                                               |");
printf("\n| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |");
printf("\n|                                                                                               |");
printf("\n|                                                                                               |");
}

void Graphics2(){
    printf("|                                                                                               |");
    printf("\n| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |");
    printf("\n|                                                                                               |");
}

void GraphicE(){
    printf("\n|                       You Chose To Encrypt Your File                                          |");
    printf("\n|                         Please Wait A Short While                                             |");
    printf("\n|                                                                                               |");
}
void GraphicD(){
    printf("\n|                       You Chose To Decrypt Your File                                          |");
    printf("\n|                         Please Wait A Short While                                             |");
    printf("\n|                                                                                               |");
}
void GraphicERROR(){
    printf("\n|===============================================================================================|");
    printf("\n|                                                                                               |");
    printf("\n|                               ERROR: UNKOWN FUNCTION                                          |");
    printf("\n|                                                                                               |");
    printf("\n|                               PLEASE TRY AGAIN LATER                                          |");
    printf("\n|                                                                                               |");
    printf("\n|===============================================================================================|");

}
void GraphicEXITMESSAGE(){
    printf("\n|===============================================================================================|");
    printf("\n|                                                                                               |");
    printf("\n|                                  THANK YOU FOR USING                                          |");
    printf("\n|                                                                                               |");
    printf("\n|                                      CRYPTOMAGIC                                              |");
    printf("\n|                                                                                               |");
    printf("\n|===============================================================================================|");

}

int main(){
    Graphics1();
    char fname[100],EOD, Extension;
    int i = 0;
    FILE* Outputtxt;
    memset(fname, 0, 100); 



    
   
    printf("\n|                Please Enter What You'd Like to Do: ");
    scanf("-%c ",&EOD);//asks user for Utility Type
    gets(fname);//asks user for filename
    Graphics2();
    //printf("           |");
if (EOD == 'E' || EOD == '\0'){
    GraphicE();
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
    GraphicD(); //putt decrytion stuff right after this line
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
    GraphicERROR();
    return 0;
}
     
    Outputtxt = fopen(fname, "w");//Opens the file from where the text will be written.
    FILE *Inputtxt = fopen("data.txt", "r");
    decrypt(Inputtxt, Outputtxt);
GraphicEXITMESSAGE();
}