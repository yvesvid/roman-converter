#include <iostream>
#include <stdio.h>
#include <cstring>

#define MAX_ALOWED_SIZE 256

typedef struct roman_numerals{
    char roman;
    int value;
}roman_numerals;

static const roman_numerals 
conversion_table[7] =
{
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000},
};

int 
convert_roman_string( const char * roman )
{
    static int roman_size = 0;
    static int roman_buffer[MAX_ALOWED_SIZE] = {0};
    memset(roman_buffer, 0, MAX_ALOWED_SIZE * sizeof(int));
    static int result_size = 0, result = 0;
    roman_size = strlen(roman);
    result_size = result = 0;
    if(roman_size <= MAX_ALOWED_SIZE && roman_size > 0)
    {
        static int i = 0, s = 0;
        for(i = 0; i < roman_size; i++)
        {
            roman_buffer[i] = -1;
            result_size++;
            for( s = 0; s < 7; s++)
            {
                if(
                    roman[i] == conversion_table[s].roman ||
                    roman[i] == tolower(conversion_table[s].roman)
                )
                    roman_buffer[i] = conversion_table[s].value;
            }
            if(roman_buffer[i] == -1)
            {
                return -1;
            }
        }
        for( i = 0; i < result_size; i++ )
        {
            if(i < result_size-1)
            {
                if(roman_buffer[i+1] > roman_buffer[i])
                {
                    result += roman_buffer[i+1] - roman_buffer[i];
                    i++;
                }
                else
                {
                    result += roman_buffer[i];
                }
            }
            else
            {
                result += roman_buffer[i];
            }
        }    
    }
    else
    {
        std::cout << "Exited here!\n";
        return -1;
    }

    return result;
}

int 
main(int argc, char const *argv[])
{
    char user_input[MAX_ALOWED_SIZE+1] = {0};
    int output = 0;
input:
    std::cout << "Please enter a roman number (or quit to exit): ";
    std::cin >> user_input;
    if(strcmp(user_input, "quit") == 0)
        return 0;
    output = convert_roman_string(user_input);
    if(output > 0)
    {
        std::cout << user_input << " = " << output << std::endl;
    }
    else
    {
        std::cout << "Input " << user_input << " not recognized.\n";
    }
    goto input;
    return 0;
}
