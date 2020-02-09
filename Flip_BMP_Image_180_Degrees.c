#include <stdio.h>
#include <stdlib.h>

void newlineRemover();
int ext_id();
int img_in_error(FILE *a);

main(){
    //declared variables
    char header[54], location[1000];
    int width, i=0, j;
    
    do{
        printf("Enter the file name including its extention \"bmp\": ");
        fgets(location, 1000, stdin);//stores input in array
        newlineRemover(location);//removes newline from input and puts end
        
        //checks for extention
        if(ext_id(location) == 0){
            printf("     Wrong Extention try again\n\n");
        }
        
        else break;
        
    }while(1);//loop ends if location and extention are correct
    
    //declared files for in and out
    FILE *img_in, *img_out;
    img_in = fopen(location, "rb");
    img_in_error(img_in);
    img_out = fopen("flipped.bmp", "wb");
    
    //read input image header and write it to the output image
    fread(header, 54, 1, img_in);
    fwrite(header, 54, 1, img_out);
    
    //place the cursor at the end of the input immage
    fseek(img_in, 0, SEEK_END);
    j = ftell(img_in);//tells me how many items in file so if image has 200 bytes then tell returns 200
    
    //loops the fseek backwards from the end
    while(i < j){//i = 0 and j could be 200
        i++;//continues and stops when i could be 200
        fseek(img_in, -i, SEEK_END);//counts backwards
        fprintf(img_out, "%c", fgetc(img_in));//frints the i character to the output image
    }
    
    //close all files
    fclose(img_in);
    fclose(img_out);
    
    system("pause");
    return 0;
}

//function to remove newline from user input and replace with end('\0")
void newlineRemover(char *arr){
    int i, length;
    length = strlen(arr);
    for(i=0; i<length; i++){
        if(arr[i] == '\n'){
             arr[i] = '\0';
        }
    }
}

//function to see if extention is correct
int ext_id(char *arr){
    char *iret;
    
    iret = strrchr(arr, '.');
    
    if(iret == NULL){
        return 0;
    }
    else if(strcmp(iret, ".bmp") == 0){
        return 1;
    }
    else if(strcmp(iret, ".BMP") == 0){
        return 1;
    }
    else if(strcmp(iret, ".Bmp") == 0){
        return 1;
    }
    else if(strcmp(iret, ".bMp") == 0){
        return 1;
    }
    else if(strcmp(iret, ".bmP") == 0){
        return 1;
    }
    else if(strcmp(iret, ".BMp") == 0){
        return 1;
    }
    else if(strcmp(iret, ".bMP") == 0){
        return 1;
    }
    else if(strcmp(iret, ".BmP") == 0){
        return 1;
    }
    else{
        return 0;
    }
}

//fuction to make sure user image can be opened
int img_in_error(FILE *a){
    if (a == NULL){ 
                printf("\n          Image was not found.\n");
                printf("Make sure the location of the image is correct.\n\n");
                return (0);
        }
    else printf("\nPlease wait flipping image\n");
        return 1;
}
