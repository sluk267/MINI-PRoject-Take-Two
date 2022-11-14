#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(FILE *input, FILE *output){
    int c1;
    //creates encrypted output file (prints to keys.txt for now)
    FILE *encryptedOutput;
    encryptedOutput = output;
    
    //cycles through characters in file one at a time
    for(c1 = fgetc(input); c1 != EOF; c1 = fgetc(input)){
        //prints all characters to console for convenience 
        //printf("%c", c1);
        if(c1 == 10) {
            //check for linux carriage return
            fprintf(output, "\n");
        } else if(c1 == 9) {
            //check for TAB
            fprintf(output, "TT");
        } else if((c1-16) < 32) {
            //encryption condition 1 (printing with %X prints the hex value instead of decimal, also capital letters)
            fprintf(output, "%X",((c1 - 16) - 32) + 144);
        } else {
            //encryption normal case
            fprintf(output, "%X",(c1 - 16));
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
        if(c1 == '\n'){
            fprintf(decryptedOutput, "\n");
            c1 = c2;
            c2 = fgetc(input);
        }
        if((c1 == 'T')&&(c2=='T')) {
            fprintf(decryptedOutput, "\t");
        } else if((c2 >= 65) && (c2 <= 90)) {
            //printf("%c %c,", (c1), (c2));      
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
void Graphics1(){ //UI for welcome Message
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
    printf("\n|                     cryptoMagic <Option> <Filename>                                           |");
    printf("\n|             OR      cryptoMagic <Filename> (Only Do This If You Wish To Encrypt File)         |");
    printf("\n|                                                                                               |");
    printf("\n| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |");
    printf("\n|                                                                                               |");
    printf("\n|                                                                                               |");
}
void Graphics2(){//UI for connection
    printf("|                                                                                               |");
    printf("\n| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |");
    printf("\n|                                                                                               |");
}
void GraphicE(){//UI for encryption wait
    printf("\n|                                   You Chose To Encrypt Your File                              |");
    printf("\n|                                     Please Wait A Short While                                 |");
    printf("\n|                                                                                               |");
}
void GraphicD(){//UI for decryption wait
    printf("\n|                                   You Chose To Decrypt Your File                              |");
    printf("\n|                                     Please Wait A Short While                                 |");
    printf("\n|                                                                                               |");
}
void GraphicERROR(){//UI for error message
    printf("\n|===============================================================================================|");
    printf("\n|                                                                                               |");
    printf("\n|                                     ERROR: UNKOWN FUNCTION                                    |");
    printf("\n|                                                                                               |");
    printf("\n|                                     PLEASE TRY AGAIN LATER                                    |");
    printf("\n|                                                                                               |");
    printf("\n|                             Please Press Enter To Close This Window                           |");
    printf("\n|                                                                                               |");
    printf("\n|===============================================================================================|");
}
void GraphicEXITMESSAGE(){//UI for exit message
    printf("\n|===============================================================================================|");
    printf("\n|                                                                                               |");
    printf("\n|                                       THANK YOU FOR USING                                     |");
    printf("\n|                                                                                               |");
    printf("\n|                                           CRYPTOMAGIC                                         |");
    printf("\n|                                                                                               |");
    printf("\n|                             Please Press Enter To Close This Window                           |");
    printf("\n|                                                                                               |");
    printf("\n|===============================================================================================|");
}

int main(){
    Graphics1(); // UI for Welcome Message
    char fname[100],EOD, Extension, EXIT;
    int i = 0;

    memset(fname, 0, 100); 

    FILE *Inputtxt = fopen(fname, "r");

    
   
    printf("\n|                Please Enter What You'd Like to Do: cryptoMagic ");
    scanf("-%c ",&EOD);//asks user for Utility Type
    gets(fname);//asks user for filename

    Graphics2(); //UI
    

if (EOD == 'E' || EOD == '\0'){ // Runs encryption algorythm
    GraphicE(); //Wait message for encrytion
    FILE *Inputtxt = fopen(fname, "r"); // reads data from specified file

while ((fname[i] != '.') &&(fname[i] !='\0')){
      i++;
}
if (fname[i] == '.'){ //changes file Extension to .crp
   strcpy(fname+i, ".crp");
}
else{
    strcat(fname,".crp");
}
    FILE *Outputtxt = fopen(fname, "w+"); //prepares file to be written to
    encrypt(Inputtxt, Outputtxt); // encrypts data
}




else if (EOD == 'D'){ // runs if user wanted to decrypt data

   FILE *Inputtxt = fopen(fname, "r"); // opens file
    
    GraphicD(); //Wait message for decryption
while ((fname[i] != '.') &&(fname[i] !='\0')){
      i++;
}
if (fname[i] == '.'){
   strcpy(fname+i, ".txt"); // changes file extension
}
else{
    strcat(fname,".txt");
}
    FILE *Outputtxt = fopen(fname, "w+");//creates decrypted file (empty) location
    decrypt(Inputtxt, Outputtxt); // decrypts data
}
else{
    GraphicERROR(); // shows error with input
    scanf("%c",&EXIT);// exit sequence (press enter to exit)
    return 0;
}
     
    //Opens the file from where the text will be written.
GraphicEXITMESSAGE(); // friendly exit message
scanf("%c",&EXIT);// exit sequence (press enter to exit)
return 0;
}