#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER_SIZE 128
int main(int argc, char *argv[]) {
    FILE *file = fopen("/sys/kernel/debug/os2/file", "r+");
    if (file == NULL) {
	    std::cout << "can't open file\n";
	    return 1;
    }

    std::cout << "opened file\n";

	if (strcmp(argv[1],"--help")==0) {
        printf("first arg: vendor_id\n");
        printf("second arg: device_id\n");
        fclose(file);
        return 0;
    }

	unsigned int vendor_id;
    unsigned int device_id;
	if (sscanf(argv[1], "%x", &vendor_id) && sscanf(argv[2], "%x", &device_id)) {
        char buffer[BUFFER_SIZE];
        fprintf(file, "vendor_id: %x, device_id: %x", vendor_id, device_id);
        while (true) {
            char *result = fgets(buffer, BUFFER_SIZE, file);
            if (feof(file)) break;
            printf(result);
        }
    } else {
        printf("Аргументов много!!!");
    }
    
    fclose(file);
    return 0;
}

