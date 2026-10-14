#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LINE_LENGTH 50

void bytes_to_hex_sprintf(const unsigned char *bytes, unsigned int length, char *output)
{
    for (unsigned int i = 0; i < length; ++i)
    {
        sprintf(&output[i * 2], "%02x", bytes[i]);
    }
}

int main()
{

    FILE *wordlist_ptr;
    char line[MAX_LINE_LENGTH];
    unsigned char hash_output[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    char hexdecimal_result[65];

    char hashed_string[] = "177ca70f42def1238e36da329473263ed3feadd14094c079a2230be0193436f5";
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (ctx == NULL)
    {
        return 1;
    }

    char file[] = "wordlist.txt";
    wordlist_ptr = fopen(file, "r");

    if (wordlist_ptr == NULL)
    {
        printf("The file named %s doesn't exist", file);
        EVP_MD_CTX_free(ctx);
        return 1;
    }

    bool found_string = false;

    while (fgets(line, MAX_LINE_LENGTH, wordlist_ptr) && !found_string)
    {
        // printf("%s", line);
        line[strcspn(line, "\r\n")] = 0;

        if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1)
        {
            continue;
        }

        EVP_DigestUpdate(ctx, line, strlen(line));
        EVP_DigestFinal_ex(ctx, hash_output, &hash_len);

        bytes_to_hex_sprintf(hash_output, hash_len, hexdecimal_result);

        if (strcmp(hexdecimal_result, hashed_string) == 0)
        {
            found_string = true;
            printf("Found the string! Password is: %s\n", line);
        }
    }

    EVP_MD_CTX_free(ctx);
    fclose(wordlist_ptr);

    if (!found_string)
    {
        printf("Password hash not found in the wordlist.\n");
    }

    return 0;
}