
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

enum{
     MAX_LEN_OF_STRING = 50,
     MAX_NUM_OF_STRINGS = 30,
     STEP_ADDING_STRING = 10,
};

void replace_str(char *str1, char *str2){
    char buffer[MAX_LEN_OF_STRING] = {};
    strcpy(buffer, str1);
    strcpy(str1, str2);
    strcpy(str2, buffer);
}

void myswap(char **dinamic_mass, int el1, int el2){
    char *buffer_point = dinamic_mass[el1];
    dinamic_mass[el1] = dinamic_mass[el2];
    dinamic_mass[el2] = buffer_point;
}

void print_all_strings(char **dinamic_mass_strings, int num_of_strings){
    for(int i = 0; i < num_of_strings; i ++){
        printf("%s\n", dinamic_mass_strings[i]);
        free(dinamic_mass_strings[i]);
    }
}

int enter_text(char **dinamic_mass_strings, FILE *inputfile, int max_number_of_strings){

    assert(dinamic_mass_strings);
    assert(inputfile);

    int current_string = 0;
    char buffer_string[MAX_LEN_OF_STRING] = {};

    printf("1.1\n");

    while(fscanf(inputfile, "%*[ .,\t\n]%[^\n]%*[\n]", buffer_string) > 0){

        dinamic_mass_strings[current_string] = (char*)calloc(sizeof(char), strlen(buffer_string));

        strcpy(dinamic_mass_strings[current_string], buffer_string);

        printf("1");
        current_string ++;


        if (current_string >= max_number_of_strings){

            dinamic_mass_strings = (char**)realloc( dinamic_mass_strings,
                                                    sizeof(char*) * (max_number_of_strings + STEP_ADDING_STRING));
            assert(dinamic_mass_strings);
            max_number_of_strings += STEP_ADDING_STRING;
        }
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

void sort_strings_bubble(char **dinamic_mass_strings, int num_of_strings){
    int curr_el;
    for(int i = 1; i < num_of_strings; i ++){
        curr_el = i;
        while(curr_el > 0 && 0 < compare_strings(dinamic_mass_strings[curr_el],
                                                 dinamic_mass_strings[curr_el - 1])){
            myswap(dinamic_mass_strings, curr_el, curr_el - 1);
            curr_el--;
        }
    }
}

int main(){
    char mass_strings[MAX_NUM_OF_STRINGS][MAX_LEN_OF_STRING] = {};
    char file_name[50] = {};
    int max_number_of_strings = MAX_NUM_OF_STRINGS;

    char **dinamic_mass_strings = (char**)calloc(sizeof(char*), max_number_of_strings);

    FILE *inputFile = fopen("input.txt", "r");
    int num_of_strings = enter_text(dinamic_mass_strings, inputFile, max_number_of_strings) + 1;


    sort_strings_bubble(dinamic_mass_strings, num_of_strings);



    print_all_strings(dinamic_mass_strings, num_of_strings);


    fclose(inputFile);
    free(dinamic_mass_strings);
    return 0;
}
