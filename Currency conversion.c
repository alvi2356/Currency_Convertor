#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert(char from[], char to[], float amount) {
    float rate_from = 0.0, rate_to = 0.0;
    FILE *file;
    char line[100];

    file = fopen("currencies.txt", "r");
    if (file == NULL) {
        printf("Error! Could not open file\n");
        exit(0);
    }

    int found_from = 0, found_to = 0;

    while (fgets(line, sizeof(line), file)) {
        char currency[100], value[100];
        sscanf(line, "%s %s", currency, value);
        if (strcmp(currency, from) == 0) {
            rate_from = atof(value);
            found_from = 1;
        }
        if (strcmp(currency, to) == 0) {
            rate_to = atof(value);
            found_to = 1;
        }
        if (found_from && found_to) {
            break;
        }
    }

    fclose(file);

    if (!found_from || !found_to) {
        printf("Error! Currency codes not found in the file.\n");
        return;
    }

    float converted_amount = (amount / rate_from) * rate_to;
    printf("%.2f %s = %.2f %s\n", amount, from, converted_amount, to);
}

int main() {
    float amount;
    char from[100], to[100];
    printf("Currently Available Currencies: USD,EUR,GBP,BDT,CAD,JPY,AUD,CHF,CNY,INR,PKR\n \n \n");

    printf("Enter the currency to convert from: ");
    fgets(from, sizeof(from), stdin);
    from[strlen(from) - 1] = '\0';

    printf("Enter the currency to convert to: ");
    fgets(to, sizeof(to), stdin);
    to[strlen(to) - 1] = '\0';

    printf("Enter the amount to convert: ");
    scanf("%f", &amount);

    convert(from, to, amount);

    return 0;
}
