#include "agenda.h"

// TODO: commment all functions

void getDataSize(void *pBuffer) {
    if (!pBuffer)
        return;

    BUFFER_I_VAL(pBuffer) = 0;
    BUFFER_DATASIZE_VAL(pBuffer) = 0;
    BUFFER_PCURRENT_VAL(pBuffer) = BUFFER_PEOPLE_PTR(pBuffer);

    while (BUFFER_I_VAL(pBuffer) < BUFFER_PEOPLE_COUNT_VAL(pBuffer)) {
        BUFFER_DATASIZE_VAL(pBuffer) +=
            CURRENT_PERSON_SIZE(BUFFER_PCURRENT_VAL(pBuffer));
        BUFFER_PCURRENT_VAL(pBuffer) =
            (char *)BUFFER_PCURRENT_VAL(pBuffer) +
            CURRENT_PERSON_SIZE(BUFFER_PCURRENT_VAL(pBuffer));
        BUFFER_I_VAL(pBuffer)++;
    }

    BUFFER_I_VAL(pBuffer) = 0;
}

void findPersonByEmail(void *pBuffer) {
    BUFFER_I_VAL(pBuffer) = 0;
    BUFFER_OPTION_VAL(pBuffer) = 0;
    BUFFER_PCURRENT_VAL(pBuffer) = BUFFER_PEOPLE_PTR(pBuffer);

    while (BUFFER_I_VAL(pBuffer) < BUFFER_PEOPLE_COUNT_VAL(pBuffer)) {
        if (strcmp(CURRENT_EMAIL_PTR(BUFFER_PCURRENT_VAL(pBuffer)),
                   TEMP_EMAIL_PTR(pBuffer, BUFFER_DATASIZE_VAL(pBuffer))) ==
            0) {
            BUFFER_OPTION_VAL(pBuffer) = 1;
            break;
        }

        BUFFER_PCURRENT_VAL(pBuffer) +=
            CURRENT_PERSON_SIZE(BUFFER_PCURRENT_VAL(pBuffer));

        BUFFER_I_VAL(pBuffer)++;
    }
}

void clearMemory(void **pBuffer) {

    if (pBuffer == NULL || *pBuffer == NULL)
        return;

    memset(*pBuffer, 0, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer));

    free(*pBuffer);

    *pBuffer = NULL;
}

// TODO: search all people with the same name???
void addPerson(void **pBuffer) {

    getDataSize(*pBuffer);

    *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer) +
                                     SKETCH_SIZE);
    if (!*pBuffer) {
        printf("Error allocating the stack\n");
        exit(1);
    }

    memset((char *)*pBuffer + METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer), 0,
           SKETCH_SIZE);

    printf("Name: ");
    scanf(" %49[^\n]", TEMP_NAME_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

    printf("Age: ");
    scanf(" %d", TEMP_AGE_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

    printf("Email: ");
    scanf(" %49[^\n]", TEMP_EMAIL_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

    TEMP_NAME_LEN_VAL(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)) =
        strlen(TEMP_NAME_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer))) + 1;
    TEMP_EMAIL_LEN_VAL(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)) =
        strlen(TEMP_EMAIL_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer))) + 1;

    BUFFER_I_VAL(*pBuffer) = NEW_PERSON_BLOCK_SIZE(
        TEMP_NAME_LEN_VAL(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)),
        TEMP_EMAIL_LEN_VAL(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

    *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer) +
                                     SKETCH_SIZE + BUFFER_I_VAL(*pBuffer));
    if (!*pBuffer) {
        printf("Realloc error 2.\n");
        exit(1);
    }

    memmove((char *)*pBuffer + METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer) +
                BUFFER_I_VAL(*pBuffer),
            (char *)*pBuffer + METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer),
            SKETCH_SIZE);

    BUFFER_PCURRENT_VAL(*pBuffer) =
        (char *)*pBuffer + METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer);

    BUFFER_DATASIZE_VAL(*pBuffer) += BUFFER_I_VAL(*pBuffer);

    memcpy(BUFFER_PCURRENT_VAL(*pBuffer),
           TEMP_NAME_LEN_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)),
           sizeof(int));
    BUFFER_PCURRENT_VAL(*pBuffer) += sizeof(int);

    memcpy(BUFFER_PCURRENT_VAL(*pBuffer),
           TEMP_NAME_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)),
           TEMP_NAME_LEN_VAL(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));
    BUFFER_PCURRENT_VAL(*pBuffer) +=
        TEMP_NAME_LEN_VAL(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer));

    memcpy(BUFFER_PCURRENT_VAL(*pBuffer),
           TEMP_AGE_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)), sizeof(int));
    BUFFER_PCURRENT_VAL(*pBuffer) += sizeof(int);

    memcpy(BUFFER_PCURRENT_VAL(*pBuffer),
           TEMP_EMAIL_LEN_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)),
           sizeof(int));
    BUFFER_PCURRENT_VAL(*pBuffer) += sizeof(int);

    memcpy(BUFFER_PCURRENT_VAL(*pBuffer),
           TEMP_EMAIL_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)),
           TEMP_EMAIL_LEN_VAL(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

    BUFFER_PEOPLE_COUNT_VAL(*pBuffer)++;

    getDataSize(*pBuffer);

    *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer));
    if (!*pBuffer) {
        printf("Error allocating a person\n");
        exit(1);
    }

    printf("\n> Person registered successfully <\n");

    BUFFER_DATASIZE_VAL(*pBuffer) = 0;
    BUFFER_I_VAL(*pBuffer) = 0;
}

void removePerson(void **pBuffer) {
    if (BUFFER_PEOPLE_COUNT_VAL(*pBuffer) == 0) {
        printf("\n>>> Theres no person to remove. <<<\n");
        return;
    }

    getDataSize(*pBuffer);

    *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer) +
                                     SKETCH_SIZE);
    if (!*pBuffer) {
        printf("Realloc error 1.\n");
        exit(1);
    }

    memset((char *)*pBuffer + METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer), 0,
           SKETCH_SIZE);

    printf("Type an Email to remove person: ");
    scanf(" %49[^\n]", TEMP_EMAIL_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

    findPersonByEmail(*pBuffer);

    if (!BUFFER_OPTION_VAL(*pBuffer)) {
        printf("\n>>> The person was not found. <<<\n");
    } else {

        BUFFER_I_VAL(*pBuffer) =
            CURRENT_PERSON_SIZE(BUFFER_PCURRENT_VAL(*pBuffer));

        BUFFER_PCURRENT_VAL(*pBuffer) += BUFFER_I_VAL(*pBuffer);

        BUFFER_DATASIZE_VAL(*pBuffer) =
            (size_t)(BUFFER_PEOPLE_PTR(*pBuffer) +
                     BUFFER_DATASIZE_VAL(*pBuffer)) -
            (size_t)(BUFFER_PCURRENT_VAL(*pBuffer));

        memmove(BUFFER_PCURRENT_VAL(*pBuffer) - BUFFER_I_VAL(*pBuffer),
                BUFFER_PCURRENT_VAL(*pBuffer), BUFFER_DATASIZE_VAL(*pBuffer));

        BUFFER_PEOPLE_COUNT_VAL(*pBuffer)--;
        printf("\n>>> The person was successfully removed. <<<\n");
    }

    getDataSize(*pBuffer);

    *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer));

    if (!*pBuffer) {
        printf("Falha (realloc 3)\n");
        exit(1);
    }

    BUFFER_DATASIZE_VAL(*pBuffer) = 0;
    BUFFER_I_VAL(*pBuffer) = 0;
    BUFFER_OPTION_VAL(*pBuffer) = 0;
}

void searchPerson(void **pBuffer) {
    if (BUFFER_PEOPLE_COUNT_VAL(*pBuffer) == 0) {
        printf("\n>>> Theres no person to search. <<<\n");
        return;
    }

    getDataSize(*pBuffer);
    *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer) +
                                     SKETCH_SIZE);
    if (!*pBuffer) {
        printf("Realloc error 1.\n");
        exit(1);
    }
    memset((char *)*pBuffer + METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer), 0,
           SKETCH_SIZE);

    printf("Email to search: ");
    scanf(" %49[^\n]", TEMP_EMAIL_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

    findPersonByEmail(*pBuffer);

    if (BUFFER_OPTION_VAL(*pBuffer) == 0) {
        printf("\n>>> The person was not found. <<<\n");
    } else {
        printf("--------- Person Found ---------\n");
        printf("\tPerson: %d\n", BUFFER_I_VAL(*pBuffer) + 1);
        printf("\tName: %s\n", CURRENT_NAME_PTR(BUFFER_PCURRENT_VAL(*pBuffer)));
        printf("\tAge: %d\n",
               *(CURRENT_AGE_PTR(BUFFER_PCURRENT_VAL(*pBuffer))));
        printf("\tEmail: %s\n",
               CURRENT_EMAIL_PTR(BUFFER_PCURRENT_VAL(*pBuffer)));
        printf("--------------------------------\n");
    }

    *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer));
    if (!*pBuffer) {
        printf("Realloc error 2.\n");
        exit(1);
    }

    BUFFER_DATASIZE_VAL(*pBuffer) = 0;
    BUFFER_I_VAL(*pBuffer) = 0;
    BUFFER_OPTION_VAL(*pBuffer) = 0;
}

void listPeople(void *pBuffer) {
    if (BUFFER_PEOPLE_COUNT_VAL(pBuffer) == 0) {
        printf("\n>>> The are no people to list. <<<\n");
        return;
    }

    BUFFER_I_VAL(pBuffer) = 0;
    BUFFER_PCURRENT_VAL(pBuffer) = BUFFER_PEOPLE_PTR(pBuffer);
    printf("----------- PEOPLE ----------\n");

    while (BUFFER_I_VAL(pBuffer) < BUFFER_PEOPLE_COUNT_VAL(pBuffer)) {
        printf("PERSON: %d\n", BUFFER_I_VAL(pBuffer) + 1);
        printf("\tNAME: %s\n", CURRENT_NAME_PTR(BUFFER_PCURRENT_VAL(pBuffer)));
        printf("\tAGE: %d\n", CURRENT_AGE_VAL(BUFFER_PCURRENT_VAL(pBuffer)));
        printf("\tEMAIL: %s\n",
               CURRENT_EMAIL_PTR(BUFFER_PCURRENT_VAL(pBuffer)));
        BUFFER_PCURRENT_VAL(pBuffer) = NEXT_PERSON(pBuffer);
        BUFFER_I_VAL(pBuffer)++;
        printf("\n");
    }
    printf("--------- END PEOPLE ---------\n");

    BUFFER_I_VAL(pBuffer) = 0;
    printf("\n");
}
