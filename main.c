#include <stdio.h>
#include <stdlib.h>
#include "input/file_reading.h"


int main() {
    CFU_Cards* head = card_reading();
    if (head == NULL) {
        return 1;
    }

    print_cards(head);

    // Free the memory when you're done
    free_cards(head);
    return 0;
}
