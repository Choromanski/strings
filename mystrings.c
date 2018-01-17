#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){
	FILE *f = fopen(argv[1], "rb");
	long position, size;     //long so it can handle rediculious large files 
	int count;
	char currentChar;
	char temp[3];

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);

	for(position = 0; position < size; ){
		fread(&currentChar, sizeof(currentChar), 1, f);
		int start = ftell(f);
		count = 0;
		while(((currentChar >= 32 && currentChar <= 126)||currentChar == 9)&& position < size){
            if(count < 3){
                temp[count] = currentChar;
            }else if(count == 3){
                printf("%c%c%c%c", temp[0], temp[1], temp[2], currentChar);
            }
            if(count > 3){
                printf("%c",currentChar);
            }
            fread(&currentChar, sizeof(currentChar), 1, f);
			position = ftell(f);
            count++;
		}
        if(position == size && ((currentChar >= 32 && currentChar <= 126)||currentChar == 9)){
            if(count == 3){
				printf("%c%c%c%c\n", temp[0], temp[1], temp[2], currentChar);
            }else if(count > 3){
                printf("%c\n", currentChar);
            }
			count++;
        }else if(count > 3){
            printf("\n");
        }
		position = ftell(f);
	}
	fclose(f);
	return 0;
}
