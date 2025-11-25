#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#pragma comment(lib, "Comdlg32.lib")
#define XOR_KEY 0x5A

void xorEncryptDecrypt(const char *inputPath, const char *outputPath) {
    FILE *fin = fopen(inputPath, "rb");
    if (!fin) { printf("❌ Cannot open input file!\n"); return; }
    FILE *fout = fopen(outputPath, "wb");
    if (!fout) { printf("❌ Cannot create output file!\n"); fclose(fin); return; }
    int byte;
    while ((byte = fgetc(fin)) != EOF) fputc(byte ^ XOR_KEY, fout);
    fclose(fin);
    fclose(fout);
    printf("✔ File processed successfully: %s\n", outputPath);
}

int main() {
    system("chcp 65001 >nul");
    printf("===============================================\n");
    printf("         FILE ENCRYPTION & DECRYPTION TOOL     \n");
    printf("===============================================\n\n");

    OPENFILENAME ofn;
    char inputFile[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = inputFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "All Files\0*.*\0";
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;

    if (!GetOpenFileName(&ofn)) { printf("❌ No file selected.\n"); return 0; }
    printf("📄 Selected file: %s\n\n", inputFile);

    int choice;
    printf("Choose an option:\n1. Encrypt File\n2. Decrypt File\nEnter choice: ");
    scanf("%d", &choice);

    char outputFile[MAX_PATH];
    if (choice == 1) {
        snprintf(outputFile, MAX_PATH, "%s.encrypted", inputFile);
        xorEncryptDecrypt(inputFile, outputFile);
    } else if (choice == 2) {
        snprintf(outputFile, MAX_PATH, "%s.decrypted", inputFile);
        xorEncryptDecrypt(inputFile, outputFile);
    } else printf("❌ Invalid choice.\n");

    printf("\n🔚 Program finished.\n");
    return 0;
}
