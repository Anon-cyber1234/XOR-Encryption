#include <stdio.h>
#include <string.h>

void xor_encrypt_decrypt(const char *filename, const char *key, int mode) {
    FILE *file = fopen(filename, mode == 0 ? "rb" : "wb");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1024];
    size_t key_len = strlen(key);
    size_t pos = 0;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        for (size_t i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') break;
            buffer[i] ^= key[pos % key_len];
            pos++;
        }

        if (mode == 0) {
            fwrite(buffer, 1, strlen(buffer), file);
        } else {
            printf("%s", buffer);
        }
    }

    fclose(file);
}

int main() {
    char choice;
    printf("Enter 'e' to encrypt or 'd' to decrypt: ");
    scanf(" %c", &choice);
    getchar();

    if (choice != 'e' && choice != 'd') {
        printf("Invalid choice.\n");
        return 1;
    }

    char filename[256];
    char key[256];
    char message[1024];

    if (choice == 'e') {
        printf("Enter the message to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        printf("Enter the encryption key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        printf("Enter the filename to save encrypted data: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';

        xor_encrypt_decrypt(filename, key, 1);

    } else {
        printf("Enter the filename to read encrypted data: ");
        scanf("%s", filename);

        printf("Enter the decryption key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        xor_encrypt_decrypt(filename, key, 0);
    }

    return 0;
}