#include <stdio.h>
#include <string.h>
#include <limits.h>

#define ALPHABET_SIZE 256


void badCharHeuristic(const char *str, int size, int badchar[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}


void search(const char *txt, const char *pat) {
    int m = strlen(pat);
    int n = strlen(txt);
    int badchar[ALPHABET_SIZE];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else {
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
}

int main() {
    char txt[] = "ABAAABCDBBABCDDEBCABC";
    char pat[] = "ABC";
    search(txt, pat);
    return 0;
}
