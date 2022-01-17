#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

/*
 * checkForDigits Function: check the password passed to make sure there is atleast 1 digit
 */
bool checkForDigits(const char* password) {
    for (int i = 0; i < strlen(password); i++) {
        // as long as we find 1 digit, return true
        if (*(password + i) >= 48 && *(password + i) <= 57) {
            return true;
        }
    }
    return false;
}

/*
 * checkForUpperCase Function: check the password passed to make sure there is atleast 1 uppercase letter
 */
bool checkForUpperCase(const char* password) {
    for (int i = 0; i < strlen(password); i++) {
        // as long as we find 1 uppercase letter, return true
        if (*(password + i) >= 'A' && *(password + i) <= 'Z') {
            return true;
        }
    }
    return false;
}

/*
 * checkForLowerCase Function: check the password passed to make sure there is atleast 1 lowercase letter
 */
bool checkForLowerCase (const char* password) {
    for (int i = 0; i < strlen(password); i++) {
        // as long as we find 1 lowercase letter, return true
        if (*(password + i) >= 'a' && *(password + i) <= 'z') {
            return true;
        }
    }
    return false;
}

/*
 * fourConsecutiveLetters Function: check the password passed to make sure there are 4 consecutive letters
 */
bool fourConsecutiveLetters (const char* password) {
    int consecutiveLetterCount = 0;
    // iterate through the password
    for (int i = 0; i < strlen(password); i++) {
        // if we find a lowercase or uppercase letter, increment a count. If we hit 4 consec letters, return true
        if ( (*(password + i) >= 'a' && *(password + i) <= 'z') || (*(password + i) >= 'A' && *(password +i) <= 'Z') ) {
            consecutiveLetterCount++;
            if (consecutiveLetterCount == 4) {
                return true;
            }
        }
        // if the current character is not a lowercase or uppercase letter, reset the count to 0
        else {
            consecutiveLetterCount = 0;
        }
    }
    return false;
}


/*
 * CheckForSpecialChars Function: check the password passed to make sure there are no other characters besides letters and numbers
 */
int checkForSpecialChars(const char* password) {
    int specialCounter = 0;
    while (*password > 0) {
        // if the character hits a special character... increase a counter
        if ((*password >= *" " && *password <= *"/") || (*password >= *":" && *password <= *"@") || (*password >= *"[" && *password <= *"`") || (*password >= *"{" && *password <= *"~")){
            specialCounter++;
        }
        password++;
    }
    return specialCounter;
}

/*
 * toLower Function: This function takes a character and converts it to lowercase if it is uppercase
 */ 
int toLower(char character) {
    if (character >= 'A' && character <= 'Z') {
        return character + 32;
    }
    return character;
}

/*
 * checkUserInPass: check the password passed to make sure the username is not in the password
 */
bool checkUserInPass (const char* username, const char* password) {
    int sameCharCount = 0;
    const char* userChar = username;
    // iterate through the password
    while(*password > 0) {
        // compare current char of user and pass to eachother and increment a counter if they are the same
        if (toLower(*userChar) == toLower(*password)) {
            userChar++;
            sameCharCount++;
            // if we hit the end of the username, return true
            if(*userChar == 0) {
                return true;
            }
        } 
        // if the characters don't match, then reassign the pointer to start at the beginning
        else {
            sameCharCount = 0;
            userChar = username;
        }
        password++;
    }
    return false;
}

/*
 *
 * A password strength meter and a default password generator, 
 * as defined in the CS221 course website for Project 1.
 *
 */
bool isStrongPassword (const char* username, const char* password ) {
    // if password is less than 8 characters, false
    if (strlen(password) < 8) {
        return false;
    }
    // if password has at least 1 digit, 1 uppercase, 1 lowercase, 4 consecutive letters, only nums and chars, and user NOT IN pass
    if (checkForDigits(password) == 1 && checkForUpperCase(password) == 1 && 
        checkForLowerCase(password) == 1 && fourConsecutiveLetters(password) == 1 && checkForSpecialChars(password) == 0 
        && checkUserInPass(username, password) == 0) {
        return true;
    }
    return false;
}

/*
 * Example: isStrongDefaultPassword("vahab", "Taher3h") returns false
 */
bool isStrongDefaultPassword(const char* username, const char* password) {
    if (strlen(password) < 8 || strlen(password) > 15) {
        return false;
    }
    // if password has at least 1 digit, 1 uppercase, 1 lowercase, only nums and chars, and user NOT IN pass
    if (checkForDigits(password) == 1 && checkForUpperCase(password) == 1 && 
        checkForLowerCase(password) == 1 && checkForSpecialChars(password) == 0 &&
        checkUserInPass(username, password) == 0) {
        return true;
    }
	return false;
}

/*
 * This function may *not* call isStrongPassword(). 
 * This function must call isStrongDefaultPassword().
 */
void generateDefaultPassword(char * default_password, const char * username) {
	srand(time(0));
    int lower = 8;
    int upper = 15;
    char choices[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    bool findValidPassword = true;

    while (findValidPassword) {
        // generates number between 1 and 16 to determine random pass length
        int randPassLength = (rand() % (upper - lower + 1)) + lower; 
        char generatedPassword[randPassLength]; 

        // iterate through the length of new string and assign a randomchar to each index
        for (int i = 0; i < randPassLength; i++) {
            int randomCharIndex = rand() % strlen(choices);
            generatedPassword[i] = choices[randomCharIndex];
        }
        generatedPassword[randPassLength] = '\0';

        // if the generated password is strong, set the default password to the generated password
        if (isStrongDefaultPassword(username, generatedPassword) == 1) {
            // strcopy (destination, source),
            strcpy(default_password, generatedPassword);
            findValidPassword = false;
        }
    }
}

int main (void) {
    // declare username, password, and default_password
    char username[51];
    char password[51];
    char default_password[16];

    // ask user to enter a username and password
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // check to see if the password is strong
    if (isStrongPassword(username, password) == 1) {
        printf("Your password is strong!\n");
    }
    else {
        printf("Your password is weak! Try again!\n");
    }

    // generate the default password for the user
    printf("Generating your default password... \n");
    generateDefaultPassword(default_password, username);
    printf("Generated default password: %s\n", default_password);

    return 0;
}