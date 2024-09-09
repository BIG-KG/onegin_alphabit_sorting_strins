#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

enum{
     MAX_LEN_OF_STRING = 50,
     MAX_NUM_OF_STRINGS = 30,
};

void replace_str(char *str1, char *str2){
    char buffer[MAX_LEN_OF_STRING] = {};
    strcpy(buffer, str1);
    strcpy(str1, str2);
    strcpy(str2, buffer);
}

void print_all_strings(char mass_strings[][MAX_LEN_OF_STRING], int num_of_strings){
    for(int i = 0; i < num_of_strings; i ++){
        printf("%d = %s\n", i + 1, mass_strings[i]);
    }
}

int enter_text(char mass_strings[][MAX_LEN_OF_STRING], FILE *inputfile){

    assert(mass_strings);
    assert(inputfile);

    int current_string = 0;


    while(fscanf(inputfile, "%[^\n]%*[\n]", mass_strings[current_string]) > 0){
        //printf("%s\n",  mass_strings[current_string]);
        current_string ++;
    }

    return --current_string;

}

int compare_strings(char *first_str, char *second_str){

    assert(first_str);
    assert(second_str);

    int curr_symb_first = 0;
    int curr_symb_second = 0;

    int sameRegist_1str = 0;
    int sameRegist_2str = 0;

    while(first_str[curr_symb_first] != '\0' && second_str[curr_symb_second] != '\0'){
        if( not(isalpha(first_str[curr_symb_first]) )){
            curr_symb_first++;
            continue;
        }
        if( not(isalpha(second_str[curr_symb_second]))){
            curr_symb_second++;
            continue;
        }

        sameRegist_1str = tolower(first_str[curr_symb_first]);
        sameRegist_2str = tolower(second_str[curr_symb_second]);

        if(sameRegist_1str < sameRegist_2str){
            return 1;
        }
        else if(sameRegist_1str > sameRegist_2str){
            return -1;
        }
        curr_symb_first ++;
        curr_symb_second ++;

    }

    if(first_str[curr_symb_first] == '\0' && second_str[curr_symb_second] == '\0'){
        if (curr_symb_first < curr_symb_second){
            return 1;
        }
        if (curr_symb_first < curr_symb_second){
            return -1;
        }
        else{
            return 0;
        }
    }
    if (first_str[curr_symb_first] == '\0'){
        return 1;
    }
    if (second_str[curr_symb_second]  == '\0'){
        return -1;
    }
}

void sort_strings_bubble(char mass_strings[][MAX_LEN_OF_STRING], int num_of_strings){
    int curr_el;
    for(int i = 1; i < num_of_strings; i ++){
        curr_el = i;
        while(curr_el > 0 && 0 < compare_strings(mass_strings[curr_el], mass_strings[curr_el - 1])){
            replace_str(mass_strings[curr_el], mass_strings[curr_el - 1]);
            curr_el--;
        }
    }
}

int main(){
    char mass_strings[MAX_NUM_OF_STRINGS][MAX_LEN_OF_STRING] = {};
    char file_name[50] = {};


    FILE *inputFile = fopen("input.txt", "r");

    int num_of_strings = enter_text(mass_strings, inputFile) + 1;

    sort_strings_bubble(mass_strings, num_of_strings);

    print_all_strings(mass_strings, num_of_strings);

    return 0;
}
