#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE *file = fopen("/sys/kernel/debug/os2/file", "r+");
    if (file == NULL) {
	    std::cout << "can't open file\n";
	    return 1;
    }

    std::cout << "opened file\n";

    fclose(file);
    return 0;
}

