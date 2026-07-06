#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "[Error] Please give path of .b file\n");
        exit(-1);
    }
    if (argc > 2) {
        fprintf(stderr, "[Error] Too many arguments\n");
        exit(-1); 
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "[Error] Cannot find %s\n", argv[1]);
        exit(-1);
    }

    unsigned char buffer[BUFFER_SIZE] = {0};
    unsigned int ptr = 0;
    char c = (char)fgetc(f);

    int brackets = 0;
    while (c != EOF) {
        if (c == '[') {
            brackets++;
        } else if (c == ']') {
            brackets--;
        }
        c = (char)fgetc(f);
    }
    if (brackets != 0) {
        fprintf(stderr, "[Error] Too many or missing brackets\n");
        fclose(f);
        exit(-1);
    }
    fseek(f, 0, SEEK_SET);

    c = (char)fgetc(f);
    while (c != EOF) {
        switch (c) {
        case '+':
            buffer[ptr]++;
            break;
        case '-':
            buffer[ptr]--;
            break;
        case '>':
            if (ptr == BUFFER_SIZE - 1) {
                ptr = 0;
                break;
            }
            ptr++;
            break;
        case '<':
            if (ptr == 0) {
                ptr = BUFFER_SIZE - 1;
                break;
            }
            ptr--;
            break;
        case ',':
            buffer[ptr] = getchar();
            break;
        case '.':
            putchar(buffer[ptr]);
            break;
        case '[':
            if (buffer[ptr] == 0) {
                int loop_cnt = 1;
                while (loop_cnt > 0) {
                    c = (char)fgetc(f);
                    if (c == '[') loop_cnt++;
                    if (c == ']') loop_cnt--;
                }
            }
            break;
        case ']':
            if (buffer[ptr]) {
                int loop_cnt = 1;
                fseek(f, -1, SEEK_CUR);
                while (loop_cnt > 0) {
                    fseek(f, -1, SEEK_CUR);
                    c = (char)fgetc(f);
                    if (c == ']') loop_cnt++;
                    if (c == '[') loop_cnt--;
                    ungetc(c, f);
                }
            }
            break;
        default:
            break;
        }
        c = (char)fgetc(f);
    }
    fclose(f);
}
