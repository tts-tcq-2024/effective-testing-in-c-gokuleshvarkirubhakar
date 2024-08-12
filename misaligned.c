#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int pairNo;
    const char *majorColor;
    const char *minorColor;
}color_code;

color_code expected_color_code_table[25] = {
{1, "White", "Blue"},
{2, "White", "Orange"},
{3, "White", "Green"},
{4, "White", "Brown"},
{4, "White", "Slate"},
{5, "Red", "Blue"},
{6, "Red", "Orange"},
{7, "Red", "Green"},
{8, "Red", "Brown"},
{9, "Red", "Slate"},
{10, "Black", "Blue"},
{11, "Black", "Orange"},
{12, "Black", "Green"},
{13, "Black", "Brown"},
{14, "Black", "Slate"},
{15, "Yellow", "Blue"},
{16, "Yellow", "Orange"},
{17, "Yellow", "Green"},
{18, "Yellow", "Brown"},
{19, "Yellow", "Slate"},
{20, "Violet", "Blue"},
{21, "Violet", "Orange"},
{22, "Violet", "Green"},
{23, "Violet", "Brown"},
{25, "Violet", "Slate"}
};

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);
        }
    }
    return i * j;
}

void Test_printColorMap(void) {
    FILE *original_stdout = stdout;
    char *buffer = NULL;
    size_t buffer_size = 0;
    
    FILE *fp = open_memstream(&buffer, &buffer_size);
    
    if(fp == NULL)
    {
        return;
    }
    // Redirect stdout to stream
    stdout = fp;
    
    int result = printColorMap();
    assert(result == 25);
    
    fflush(stdout);
    fclose(fp);

    // Restore stdout
    stdout = original_stdout;
    
    int idx = 0;
    int pairNo;
    char majorColor[10];
    char minorColor[10];
    
    char *line = strtok(buffer, "\n");
    while (line != NULL) {
        sscanf(line, "%d | %9s | %9s", &pairNo, majorColor, minorColor);
        assert(pairNo==color_code_table[idx].pairNo);
        assert(b(majorColor,color_code_table[idx].majorColor) == 0);
        assert(strcmp(minorColor,color_code_table[idx].minorColor) == 0);
        line = strtok(NULL, "\n");
        idx++;
    }

    free(buffer);
}

int main() {
    Test_printColorMap();
    printf("All is well (maybe!)\n");
    return 0;
}
