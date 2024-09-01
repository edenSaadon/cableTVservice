//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Address.h"
#include "General.h"


void	initAddress(Address* pAd)
{
	pAd->city=getStrExactName("Enter city name:");
	pAd->street = getStrExactName("Enter street name:");
    // Use the getIntFromUser function to ensure the input is an integer
    pAd->building = getIntFromUser("Enter building number: ");
    pAd->apartment = getIntFromUser("Enter apartment number: ");  

}
int getIntFromUser(const char* prompt)
{
    int input;
    int result;

    while (1) { // Infinite loop that will only break when a valid input is received
        printf("%s", prompt); // Display the prompt passed as an argument
        result = scanf("%d", &input); // Try to read an integer

        if (result == 1) { // If an integer was successfully read
            break; // Exit the loop
        }
        else { // If the input was not an integer
            printf("Invalid input, please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }

    return input; // Return the validated integer
}
void printAddress(const Address* pAd)
{
	printf("The address is: city: %s, street:%s, building: %d, apartment:%d \n", pAd->city, pAd->street, pAd->building, pAd->apartment);
}
void freeAddress(Address* address)
{
        if (address != NULL) {
            free(address->street);
            free(address->city);
        }
        
}