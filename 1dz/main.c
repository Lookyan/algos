#include "module.h"

int main(int argc, char *argv[])
{
    int counter = 0;
    char *buffer = malloc(buf_size * sizeof(char));
    int *quantity_of_subs = malloc(mini_buf * sizeof(int));
    double *variance_arr = malloc(mini_buf * (sizeof(double)));
/////////////////////////////////////////
/////////////////////////////////////////
    FILE *to_read;
    to_read = fopen (argv[2], "r");
    while ((buffer[counter] = fgetc (to_read)) != EOF){
        ++counter;
    }
    buffer[counter] = '\0';
    fclose(to_read);
    printf("%s\n", "--------------------------THE TEXT-------------------------");
    printf("%s\n", buffer);
    printf("%s\n", "-----------------------------------------------------------");
    printf("%s\t", "Quantity of characters in text :");
    printf("%d\n", counter);
/////////////////////////////////////////
/////////////////////////////////////////
    char *sub_str = argv[1];
    printf("%s\t\t\t", "The word to find is :");
    printf("%s\n", sub_str);
    int size_of_sub_str = 0;
    while (sub_str[size_of_sub_str] != '\0'){
        ++size_of_sub_str;
    }
/////////////////////////////////////////
///////////////////////////////////////////
    int sum_of_met = 0, num_of_sentances = 0, num = 0, metSubs = 0, sub_counter = 0;
    while(num < counter)
    {
        if(buffer[num] == '!' || buffer[num] == '?' || buffer[num] == '.'){
            ++num_of_sentances;
            quantity_of_subs[num_of_sentances-1] = metSubs;
            metSubs = 0;
        }
        if( buffer[num] == sub_str[sub_counter] ){
            if(num == 0 || isspace( buffer[num-1] ) || ispunct( buffer[num-1] )){
                while((sub_counter != size_of_sub_str) && ( buffer[num] == sub_str[sub_counter] )){
                    ++sub_counter;
                    ++num;
                }
            }
            if(sub_counter == size_of_sub_str) {
                if(ispunct( buffer[num] ) || isspace( buffer[num] )) {
                    ++metSubs;
                    sub_counter = 0;
                }else sub_counter = 0;
            } else {
                sub_counter = 0;
            }
        }
        ++num;
    }

    free (buffer);
/////////////////////////////////////////
/////////////////////////////////////////
    printf("%s\n","-----------------------------------------------------------");
    int i = 0;
    for(; i < num_of_sentances; ++i){
        printf("%s", "In ");
        printf("%d\t", i + 1);
        printf("%s\t", "sentence the word was found");
        printf("%d", quantity_of_subs[i]);
        printf("%s\n", " times");
        sum_of_met += quantity_of_subs[i];
    }
    printf("\n");
    printf("%d\n", sum_of_met);
    double expected_value = (double)sum_of_met / (double)num_of_sentances;
    double variance_sum = 0;
    for(i=0; i<num_of_sentances; ++i){
        variance_arr[i] = quantity_of_subs[i]-expected_value;
        variance_sum += variance_arr[i] * variance_arr[i] ;
    }
    printf("%f\n", variance_sum);
    double variance = (double)variance_sum / (double)(num_of_sentances-1);
    double target = sqrt(variance);
    printf("%s\t","The varfirugiugiance equals ");
    printf("%f\n",target);
/////////////////////////////////////////
/////////////////////////////////////////
    free(quantity_of_subs);
    free(variance_arr);
    return 0;
}
