#include <stdio.h>
#include <stdlib.h>

#define FIFO_FILE       "MYFIFO"

int main(int argc, char *argv[])
{
        FILE *fp = fopen(FIFO_FILE, "w");
        fputs(argv[1], fp);
        fclose(fp);
}

