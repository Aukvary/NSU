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
                    output[0] = pixel[0];
                    output[1] = pixel[1];
                    output[2] = pixel[2];
                } else {
                    output[0] = pixel[0];
                    output[1] = pixel[1];
                    output[2] = pixel[2];
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
                    output[0] = pixel[0];
                    output[1] = pixel[1];
                    output[2] = pixel[2];
                } else {
                    output[0] = pixel[0];
                    output[1] = pixel[1];
                    output[2] = pixel[2];
                }
                output += 3;
                decoded++;
            }
        }
    }
}

void read_uncompressed_tga(FILE* file, uint8_t* output, uint32_t width, uint32_t height, uint8_t pixel_size, int is_top_down) {
    uint32_t row_size = width * pixel_size;
    uint8_t* row_buffer = (uint8_t*)malloc(row_size);
    
    for (uint32_t y = 0; y < height; y++) {
        if (fread(row_buffer, row_size, 1, file) != 1) {
            break;
        }
        
        uint32_t target_y = is_top_down ? y : (height - 1 - y);
        uint8_t* target_row = output + target_y * width * 3;
        
        for (uint32_t x = 0; x < width; x++) {
            uint8_t* src_pixel = row_buffer + x * pixel_size;
            uint8_t* dst_pixel = target_row + x * 3;
            
            if (pixel_size == 4) {
                dst_pixel[0] = src_pixel[0];
                dst_pixel[1] = src_pixel[1];
                dst_pixel[2] = src_pixel[2];
            } else {
                dst_pixel[0] = src_pixel[0];
                dst_pixel[1] = src_pixel[1];
                dst_pixel[2] = src_pixel[2];
            }
        }
    }
    
    free(row_buffer);
}

int main() {
    FILE* input = fopen("input.txt", "rb");
    
    FILE* output = fopen("output.txt", "wb");

    TGAHeader tga_header;
    fread(&tga_header, sizeof(TGAHeader), 1, input);

    if (tga_header.id_length > 0) {
        fseek(input, tga_header.id_length, SEEK_CUR);
    }

    uint16_t width = tga_header.width;
    uint16_t height = tga_header.height;
    uint8_t pixel_size = tga_header.pixel_depth / 8;

    int is_top_down = (tga_header.image_descriptor & 0x20) != 0;

    uint32_t pixel_count = width * height;
    uint8_t* pixel_data = malloc(pixel_count * 3);

    if (tga_header.image_type == 2) {
        read_uncompressed_tga(input, pixel_data, width, height, pixel_size, is_top_down);
    } else if (tga_header.image_type == 10) {
        decode_rle(input, pixel_data, width, height, pixel_size);
        if (!is_top_down) {
            uint32_t row_size = width * 3;
            uint8_t* temp_row = (uint8_t*)malloc(row_size);
            
            for (uint32_t i = 0; i < height / 2; i++) {
                uint8_t* row1 = pixel_data + i * row_size;
                uint8_t* row2 = pixel_data + (height - 1 - i) * row_size;
                memcpy(temp_row, row1, row_size);
                memcpy(row1, row2, row_size);
                memcpy(row2, temp_row, row_size);
            }
            free(temp_row);
        }
    }

    fclose(input);

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

    fwrite(&bmp_file_header, sizeof(BMPFileHeader), 1, output);
    fwrite(&bmp_info_header, sizeof(BMPInfoHeader), 1, output);

    uint8_t* row_buffer = (uint8_t*)malloc(row_size);
    memset(row_buffer, 0, row_size);

    for (int32_t y = height - 1; y >= 0; y--) {
        uint8_t* src_row = pixel_data + y * width * 3;
        memcpy(row_buffer, src_row, width * 3);
        fwrite(row_buffer, row_size, 1, output);
    }

    free(row_buffer);
    free(pixel_data);
    fclose(output);

    return 0;
}