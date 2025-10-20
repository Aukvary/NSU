#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t  id_length;
    uint8_t  color_map_type;
    uint8_t  image_type;
    uint16_t color_map_origin;
    uint16_t color_map_length;
    uint8_t  color_map_depth;
    uint16_t x_origin;
    uint16_t y_origin;
    uint16_t width;
    uint16_t height;
    uint8_t  pixel_depth;
    uint8_t  image_descriptor;
} TGAHeader;

typedef struct {
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
} BMPFileHeader;

typedef struct {
    uint32_t header_size;
    uint16_t width;
    uint16_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
} BMPInfoHeader;
#pragma pack(pop)

void decode_rle(FILE* file, uint8_t* output, uint32_t width, uint32_t height, uint8_t pixel_size) {
    uint32_t total_pixels = width * height;
    uint32_t decoded = 0;
    
    while (decoded < total_pixels) {
        uint8_t packet_header;
        if (fread(&packet_header, 1, 1, file) != 1) {
            break;
        }
        
        uint8_t packet_type = packet_header & 0x80;
        uint8_t packet_count = (packet_header & 0x7F) + 1;
        
        if (packet_type) {
            uint8_t pixel[4];
            if (fread(pixel, pixel_size, 1, file) != 1) {
                break;
            }
            
            for (int i = 0; i < packet_count; i++) {
                if (pixel_size == 4) {
                    output[0] = pixel[2];
                    output[1] = pixel[1];
                    output[2] = pixel[0];
                } else {
                    output[0] = pixel[2];
                    output[1] = pixel[1];
                    output[2] = pixel[0];
                }
                output += 3;
                decoded++;
            }
        } else {
            for (int i = 0; i < packet_count; i++) {
                uint8_t pixel[4];
                if (fread(pixel, pixel_size, 1, file) != 1) {
                    break;
                }
                
                if (pixel_size == 4) {
                    output[0] = pixel[2];
                    output[1] = pixel[1];
                    output[2] = pixel[0];
                } else {
                    output[0] = pixel[2];
                    output[1] = pixel[1];
                    output[2] = pixel[0];
                }
                output += 3;
                decoded++;
            }
        }
    }
}

void read_uncompressed_tga(FILE* file, uint8_t* output, uint32_t width, uint32_t height, uint8_t pixel_size) {
    uint32_t total_pixels = width * height;
    
    for (uint32_t i = 0; i < total_pixels; i++) {
        uint8_t pixel[4];
        if (fread(pixel, pixel_size, 1, file) != 1) {
            break;
        }
        
        if (pixel_size == 4) {
            output[0] = pixel[2];
            output[1] = pixel[1];
            output[2] = pixel[0];
        } else {
            output[0] = pixel[2];
            output[1] = pixel[1];
            output[2] = pixel[0];
        }
        output += 3;
    }
}

int main() {
    FILE* input = fopen("input.txt", "rb");


    TGAHeader tga_header;
    if (fread(&tga_header, sizeof(TGAHeader), 1, input) != 1) {
        fprintf(stderr, "Cannot read TGA header\n");
        fclose(input);
        return 1;
    }

    if (tga_header.color_map_type != 0) {
        fprintf(stderr, "Unsupported color map type: %d\n", tga_header.color_map_type);
        fclose(input);
        return 1;
    }

    if (tga_header.image_type != 2 && tga_header.image_type != 10) {
        fprintf(stderr, "Unsupported image type: %d\n", tga_header.image_type);
        fclose(input);
        return 1;
    }

    if (tga_header.pixel_depth != 24 && tga_header.pixel_depth != 32) {
        fprintf(stderr, "Unsupported pixel depth: %d\n", tga_header.pixel_depth);
        fclose(input);
        return 1;
    }

    if (tga_header.id_length > 0) {
        fseek(input, tga_header.id_length, SEEK_CUR);
    }

    uint16_t width = tga_header.width;
    uint16_t height = tga_header.height;
    uint8_t pixel_size = tga_header.pixel_depth / 8;

    uint32_t pixel_count = width * height;
    uint8_t* pixel_data = (uint8_t*)malloc(pixel_count * 3);
    if (!pixel_data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(input);
        return 1;
    }

    if (tga_header.image_type == 2) {
        read_uncompressed_tga(input, pixel_data, width, height, pixel_size);
    } else if (tga_header.image_type == 10) {
        decode_rle(input, pixel_data, width, height, pixel_size);
    }

    fclose(input);

    int is_top_down = (tga_header.image_descriptor & 0x20) == 0;
    if (!is_top_down) {
        uint32_t row_size = width * 3;
        uint8_t* temp_row = (uint8_t*)malloc(row_size);
        if (!temp_row) {
            fprintf(stderr, "Memory allocation failed\n");
            free(pixel_data);
            return 1;
        }

        for (uint32_t i = 0; i < height / 2; i++) {
            uint8_t* row1 = pixel_data + i * row_size;
            uint8_t* row2 = pixel_data + (height - 1 - i) * row_size;
            memcpy(temp_row, row1, row_size);
            memcpy(row1, row2, row_size);
            memcpy(row2, temp_row, row_size);
        }
        free(temp_row);
    }

    FILE* output = fopen("output.txt", "wb");

    uint32_t row_size = (width * 3 + 3) & ~3;
    uint32_t image_size = row_size * height;
    uint32_t file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + image_size;

    BMPFileHeader bmp_file_header = {
        .signature = 0x4D42,
        .file_size = file_size,
        .reserved1 = 0,
        .reserved2 = 0,
        .data_offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader)
    };

    BMPInfoHeader bmp_info_header = {
        .header_size = 12,
        .width = width,
        .height = height,
        .planes = 1,
        .bits_per_pixel = 24
    };

    if (fwrite(&bmp_file_header, sizeof(BMPFileHeader), 1, output) != 1) {
        fprintf(stderr, "Cannot write BMP file header\n");
        fclose(output);
        free(pixel_data);
        return 1;
    }

    if (fwrite(&bmp_info_header, sizeof(BMPInfoHeader), 1, output) != 1) {
        fprintf(stderr, "Cannot write BMP info header\n");
        fclose(output);
        free(pixel_data);
        return 1;
    }

    uint8_t* row_buffer = (uint8_t*)malloc(row_size);
    if (!row_buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(output);
        free(pixel_data);
        return 1;
    }
    memset(row_buffer, 0, row_size);

    for (int32_t y = height - 1; y >= 0; y--) {
        uint8_t* src_row = pixel_data + y * width * 3;
        memcpy(row_buffer, src_row, width * 3);
        
        if (fwrite(row_buffer, row_size, 1, output) != 1) {
            fprintf(stderr, "Cannot write pixel data\n");
            fclose(output);
            free(pixel_data);
            free(row_buffer);
            return 1;
        }
    }

    free(row_buffer);
    free(pixel_data);
    fclose(output);

    return 0;
}