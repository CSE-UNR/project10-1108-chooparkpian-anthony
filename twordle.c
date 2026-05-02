//anthony chooparkpian
//project10
//4/23/26

#include <stdio.h>
#include <stdbool.h>

void fetchSecretWord(char target[]);
int getStringLength(char s[]);
void makeLowercase(char s[]);
bool isValidInput(char s[]);
void processGuess(char guess[], char target[]);
void showGameHistory(char history[6][6], char target[], int attempts);
bool isCorrect(char guess[], char target[]);

int main() {
	char targetWord[6];
	char guessHistory[6][6];
	int attempts = 0;
	bool hasWon = false;

	fetchSecretWord(targetWord);
	makeLowercase(targetWord);

	printf("--- TWORDLE ---\n");

	while (attempts < 6 && !hasWon) {
		printf("\nEnter guess (%d/6): ", attempts + 1);
		char currentInput[100];
		scanf("%s", currentInput);

		if (isValidInput(currentInput)) {
			for(int i = 0; i < 6; i++){
				guessHistory[attempts][i] = currentInput[i];
			}
				makeLowercase(guessHistory[attempts]);
            
				attempts++;
            			showGameHistory(guessHistory, targetWord, attempts);

            			if (isCorrect(guessHistory[attempts - 1], targetWord)) {
                			hasWon = true;
            			}
       			 
       		}else {
			printf("Error: Use 5 letters (no numbers/symbols).\n");
		}
	}

	if (hasWon) {
		printf("\nSuccess! You found the word in %d tries.\n", attempts);
	} else {
		printf("\nOut of turns! The word was: %s\n", targetWord);
	}

	return 0;
}

void fetchSecretWord(char target[]) {
	FILE *f = fopen("mystery.txt", "r");
	if (f == NULL) {
		printf("can't open file\n");
		return;	
    }
	fscanf(f, "%5s", target);
	fclose(f);
}

int getStringLength(char s[]) {
	int count = 0;
	while (s[count] != '\0') count++;
	return count;
}

bool isValidInput(char s[]) {
	if (getStringLength(s) != 5){
		return false;
	}
	for (int i = 0; i < 5; i++) {
        if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))) {
		return false;
        }
	}
	return true;
}

void makeLowercase(char s[]) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 32;
		}
	}
}

bool isCorrect(char guess[], char target[]) {
    for (int i = 0; i < 5; i++) {
        if (guess[i] != target[i]) return false;
    }
    return true;
}

void showGameHistory(char history[6][6], char target[], int attempts) {
	printf("\nBoard State:\n");
	for (int i = 0; i < attempts; i++) {
		char markers[6] = "     ";

		for (int j = 0; j < 5; j++) {
			char currentLetter = history[i][j];
			if (currentLetter == target[j]) {
   				printf("%c", currentLetter - 32);
			} else {
                		printf("%c", currentLetter);
				for (int k = 0; k < 5; k++) {
					if (currentLetter == target[k]) {
  						markers[j] = '^';
   						break;
					}
				}
  			}
		}
	printf("\n%s\n", markers);
	}
}

