#include "agenda.h"

int main() {
    void *pBuffer = NULL;

    pBuffer = malloc(METADATA_SIZE);

    if (!pBuffer) {
        printf(C_RED "Failed to allocate buffer.\n" C_RESET);
        return 0;
    }

    memset(pBuffer, 0, METADATA_SIZE);

    while (BUFFER_OPTION_VAL(pBuffer) != 5) {
        printf(
            C_BLUE
            "\n1 - Add Person\n2 - Remove Person\n3 - Search Person\n4 - List "
            "People\n5 - Exit\n" C_RESET);
        printf("\nChoose an option: ");
        if (scanf(" %d", BUFFER_OPTION_PTR(pBuffer)) != 1) {
            BUFFER_OPTION_VAL(pBuffer) = 0;
        }

        switch (BUFFER_OPTION_VAL(pBuffer)) {
        case 1:
            addPerson(&pBuffer);
            break;
        case 2:
            removePerson(&pBuffer);
            break;
        case 3:
            searchPerson(&pBuffer);
            break;
        case 4:
            listPeople(pBuffer);
            break;
        case 5:
            break;
        default:
            printf(C_YELLOW "\nIsn't a valid option... Try again.\n" C_RESET);
        }
    }

    clearMemory(&pBuffer);

    return 0;
}
