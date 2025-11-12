#include <stdio.h>

int main() {
    // Байты в точности как в вашем формате
    unsigned char bytes[] = {
        0x0A, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0xF2, 0xFF, 0xFF, 0xFF,
        0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00,
        0xFD, 0xFF, 0xFF, 0xFF, 0x1E, 0x00, 0x00, 0x00, 0xF6, 0xFF, 0xFF, 0xFF,
        0x0A, 0x00, 0x00, 0x00, 0xF4, 0xFF, 0xFF, 0xFF
    };
    
    int bytes_count = sizeof(bytes);
    
    FILE* file = fopen("input.txt", "wb");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }
    
    size_t written = fwrite(bytes, 1, bytes_count, file);
    
    if (written != bytes_count) {
        printf("Ошибка записи в файл!\n");
        fclose(file);
        return 1;
    }
    
    fclose(file);
    printf("Успешно записано %d байт в файл 'output.bin'\n", bytes_count);
    
    return 0;
}