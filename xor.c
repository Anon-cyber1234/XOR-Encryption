#include <stdio.h>
#include <string.h>

void xor_encrypt_decrypt(const char* filename, const char* key, const char* message, int mode) {

	if (filename[0] == '\0') {
		printf("Error: filename cannot be empty.\n");
		return;
	}

	if (key[0] == '\0') {
		printf("Error: key cannot be empty.\n");
		return;
	}

	FILE* file = fopen(filename, mode == 0 ? "rb" : "wb");
	if (!file) {
		printf("Error opening file.\n");
		return;
	}

	size_t key_len = strlen(key);

	if (mode == 1) {
		size_t message_len = strlen(message);

		for (size_t i = 0; i < message_len; i++)
		{
			char encrypted = message[i] ^ key[i % key_len];
			fwrite(&encrypted, 1, 1, file);
		}
	}
	else {
		char ch;
		size_t pos = 0;
		while (fread(&ch, 1, 1, file) == 1) {
			char decrypted = ch ^ key[pos % key_len];
			printf("%c", decrypted);
			pos++;
		}
		printf("\n");
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

		xor_encrypt_decrypt(filename, key, message, 1);

	}
	else if (choice == 'd')
	{
		printf("Enter the filename to read encrypted data: ");
		fgets(filename, sizeof(filename), stdin);
		filename[strcspn(filename, "\n")] = '\0';

		printf("Enter the decryption key: ");
		fgets(key, sizeof(key), stdin);
		key[strcspn(key, "\n")] = '\0';

		xor_encrypt_decrypt(filename, key, NULL, 0);
	}

	return 0;
}