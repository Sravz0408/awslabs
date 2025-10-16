#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 10
#define WORD_LEN  50

// a small sample dictionary
char *dictionary[] = {"this", "is", "a", "simple", "text", "example", "program", "spellchecker", "using", "c"};
int dict_size = 10;

// function to compute edit distance (Levenshtein)
int edit_distance(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++)
        for (int j = 0; j <= len2; j++) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (tolower(s1[i - 1]) == tolower(s2[j - 1]))
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + fmin(dp[i - 1][j - 1],
                                fmin(dp[i - 1][j], dp[i][j - 1]));
        }
    return dp[len1][len2];
}

char* suggest_word(const char *word) {
    int min_dist = 999, dist;
    char *best = NULL;
    for (int i = 0; i < dict_size; i++) {
        dist = edit_distance(word, dictionary[i]);
        if (dist < min_dist) {
            min_dist = dist;
            best = dictionary[i];
        }
    }
    return best;
}

int main() {
    char text[200];
    printf("Enter a sentence: ");
    fgets(text, sizeof(text), stdin);

    char *token = strtok(text, " ,.\n");
    printf("\nSuggestions:\n");
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < dict_size; i++) {
            if (strcasecmp(token, dictionary[i]) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Word '%s' not found. Did you mean '%s'?\n", token, suggest_word(token));
        }
        token = strtok(NULL, " ,.\n");
    }
    return 0;
}
