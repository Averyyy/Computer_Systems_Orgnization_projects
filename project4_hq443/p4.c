#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* hex2bin(char hexNum[14]) //hex to binary implementation
{
	long int count=0;
    char * returnbin = (char*) malloc (14*sizeof(char));
    for (int i=0; i<(3-strlen(hexNum)); i++){
        strcat(returnbin, "0000");
    }
	while(hexNum[count])
	{
		switch(hexNum[count])
		{
			case '0' : strcat(returnbin, "0000");
				break;
			case '1' : strcat(returnbin, "0001");
				break;
			case '2' : strcat(returnbin, "0010");
				break;
			case '3' : strcat(returnbin, "0011");
				break;
			case '4' : strcat(returnbin, "0100");
				break;
			case '5' : strcat(returnbin, "0101");
				break;
			case '6' : strcat(returnbin, "0110");
				break;
			case '7' : strcat(returnbin, "0111");
				break;
			case '8' : strcat(returnbin, "1000");
				break;
			case '9' : strcat(returnbin, "1001");
				break;
			case 'A' : strcat(returnbin, "1010");
				break;
			case 'B' : strcat(returnbin, "1011");
				break;
			case 'C' : strcat(returnbin, "1100");
				break;
			case 'D' : strcat(returnbin, "1101");
				break;
			case 'E' : strcat(returnbin, "1110");
				break;
			case 'F' : strcat(returnbin, "1111");
				break;
			case 'a' : strcat(returnbin, "1010");
				break;
			case 'b' : strcat(returnbin, "1011");
				break;
			case 'c' : strcat(returnbin, "1100");
				break;
			case 'd' : strcat(returnbin, "1101");
				break;
			case 'e' : strcat(returnbin, "1110");
				break;
			case 'f' : strcat(returnbin, "1111");
				break;
			default : printf("\nInvalid Entry, Please Try Again  %c",hexNum[count]);
		}
		count++;
	}
    return returnbin;
    free(returnbin);
}
char* bin2hex(char binNum[20]){ //bin to hex implementation only 1 digit
        char* binaryString = binNum;
        // convert binary string to integer
        int value = (int)strtol(binaryString, NULL, 2);

        // convert integer to hex string
        char hexString[12]; // long enough for any 32-bit value, 4-byte aligned
        sprintf(hexString, "%X", value);

        char *returnhex = &hexString[0];
        return returnhex;
}
char* bin2hex2(char binNum[20]){ //two digits
        char* binaryString = binNum;
        // convert binary string to integer
        int value = (int)strtol(binaryString, NULL, 2);
        // convert integer to hex string
        char hexString[12]; 
        sprintf(hexString, "%X", value);
        char temp[4]="0";
        strcat(&temp[0], &hexString[0]);
        char *returnhex = temp;
        return returnhex;
}

int main(){
    char address[14];
    scanf("Enter Virtual Address:%s", address); //get the input
    char* returnaddress = hex2bin(address); //convert to binary
    char tlbt[10], tlbi[5], ci[10], co[5], vpn[20], ppn[20]; //define parameters
    memcpy(tlbt, returnaddress,4);  //get different parameters for later use
    memcpy(tlbi, returnaddress+4,2);
    memcpy(vpn, returnaddress, 6);
    memcpy(ci, returnaddress+6, 4);
    memcpy(co, returnaddress+10,2);
    char* htlbt = bin2hex2(tlbt);   //convert to heximal
    char* htlbi = bin2hex(tlbi);
    char* hvpn = bin2hex(vpn);
    char* hci = bin2hex(ci);
    char* hco = bin2hex(co);
    char final[5] = ""; //define final result


    //access the file
    FILE *filePointer;
    char tmp[50];
    filePointer = fopen("Project4Input.txt", "r");
    if (filePointer == NULL){printf("Requested file does not exists in system or not found. \n");return 0;}
    while (fscanf(filePointer, "%s", tmp)>0){
        if (tmp[0]=='T'){
            char set[5];
            memcpy(set, &tmp[4],1);     //get set numeber
            if (strcmp(&set[0], htlbi) == 0){   //compare the set number with the input
                char tag[10];
                memcpy(tag, &tmp[6], 2);        //get tag
                if (strcmp(&tag[0],htlbt) == 0){ //compare tag
                    memcpy(ppn, &tmp[9], 2);    //get ppn
                }
            }
        }

        if (tmp[0] == 'P'){
            char pagevpn[5];
            memcpy(pagevpn, &tmp[5],1); //get page number
            if (strcmp(&pagevpn[0], hvpn) == 0) //compare page number with vpn
            {
                memcpy(ppn, &tmp[7],2); //get ppn
            }
        }

        //final step, get cache
        if (tmp[0] == 'C'){
            char cacheci[5];
            memcpy(cacheci, &tmp[6],1); //get index
            if (strlen(&ppn[0]) != 0){  //check if ppn is found
                if (strcmp(hci, &cacheci[0])){  //check set with ci number and select
                    switch (*hco)   //find the final result with offset
                    {
                    case '0':
                        memcpy(final, &tmp[8],2); //get the value
                        break;
                    case '1':
                        memcpy(final, &tmp[11],2);
                        break;
                    case '2':
                        memcpy(final, &tmp[14],2);
                        break;
                    case '3':
                        memcpy(final, &tmp[17],2);
                        break;
                    case '4':
                        memcpy(final, &tmp[20],2);
                        break;
                    default:
                        // printf("%s", "Can't be determined\n"); //can't find a result
                        break;
                    }
                }else{
                    printf("Can't be determined\n"); //can't find a result since no ppn
                }
            }
        }
    
    };
    if (strlen(&final[0])==0){
        printf("Can't be determined.\n");
    }else{
    printf("The result is: %s\n", final); //print the result
    }
    return 0;
}