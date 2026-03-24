#include <stdio.h>
#include <string.h>

int main() {
    char input[256];

    while (fgets(input, sizeof(input), stdin)) {
        if (strncmp(input, "---", 3) == 0) {
            break;
        }

        // TODO: implement logic
    }

    return 0;
}