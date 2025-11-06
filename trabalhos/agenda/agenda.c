#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SKETCH SIZES
#define TEMP_NAME_SIZE 50
#define TEMP_EMAIL_SIZE 50

// pBuffer [METADATA][DATA (people)](""stack"" [SKETCH])

// people = person(nameLen, name, age, emailLen, emailLen)
// stack = temp_person(temp_nameLen, temp_name, temp_age, temp_emailLen,
// temp_emailLen)

// NOTE: The stack is added when there is a need to insert data, and then
// removed afterwards. There are many reallocs, which can be bad for
// performance, but there are no unnecessary variables in the functions.

// NOTE: METADATA MACROS

#define BUFFER_OPTION_PTR(buffer) ((int *)(buffer))
#define BUFFER_OPTION_VAL(buffer) (*(BUFFER_OPTION_PTR(buffer)))

#define BUFFER_PEOPLE_COUNT_PTR(buffer)                                        \
    ((int *)((char *)(buffer) + sizeof(int)))
#define BUFFER_PEOPLE_COUNT_VAL(buffer) (*(BUFFER_PEOPLE_COUNT_PTR(buffer)))

#define BUFFER_I_PTR(buffer) ((int *)((char *)(buffer) + 2 * sizeof(int)))
#define BUFFER_I_VAL(buffer) (*(BUFFER_I_PTR(buffer)))

#define BUFFER_DATASIZE_PTR(buffer)                                            \
    ((size_t *)((char *)(buffer) + 3 * sizeof(int)))
#define BUFFER_DATASIZE_VAL(buffer) (*(BUFFER_DATASIZE_PTR(buffer)))

#define BUFFER_OLDDATASIZE_PTR(buffer)                                         \
    ((size_t *)((char *)(buffer) + 3 * sizeof(int) + sizeof(size_t)))
#define BUFFER_OLDDATASIZE_VAL(buffer) (*(BUFFER_OLDDATASIZE_PTR(buffer)))

#define BUFFER_PCURRENT_PTR(buffer)                                            \
    ((char **)((char *)(buffer) + 3 * sizeof(int) + 2 * sizeof(size_t)))
#define BUFFER_PCURRENT_VAL(buffer) (*(BUFFER_PCURRENT_PTR(buffer)))

#define METADATA_SIZE                                                          \
    ((size_t)(3 * sizeof(int) + 2 * sizeof(size_t) + sizeof(char *)))

// METADATA AUX MACROS
#define CURRENT_NAME_LEN(current) (*(int *)(current))
#define CURRENT_NAME_PTR(current) ((char *)((char *)(current) + sizeof(int)))

#define CURRENT_AGE_PTR(current)                                               \
    ((int *)((char *)(current) + CURRENT_NAME_LEN(current) + sizeof(int)))
#define CURRENT_AGE_VAL(current) (*(CURRENT_AGE_PTR(current)))

#define CURRENT_EMAIL_LEN_PTR(current)                                         \
    ((int *)((char *)(CURRENT_AGE_PTR(current)) + sizeof(int)))
#define CURRENT_EMAIL_LEN(current) (*(CURRENT_EMAIL_LEN_PTR(current)))
#define CURRENT_EMAIL_PTR(current)                                             \
    ((char *)((char *)CURRENT_EMAIL_LEN_PTR(current) + sizeof(int)))

#define CURRENT_PERSON_SIZE(current)                                           \
    ((size_t)(sizeof(int) + CURRENT_NAME_LEN(current) + sizeof(int) +          \
              sizeof(int) + CURRENT_EMAIL_LEN(current)))

// DATA MACRO
#define BUFFER_PEOPLE_PTR(buffer) ((char *)((char *)(buffer) + METADATA_SIZE))

// SKETCH MACROS
#define SKETCH_BASE_PTR(buffer, dataSize)                                      \
    ((char *)((char *)(buffer) + METADATA_SIZE + dataSize))

#define TEMP_NAME_LEN_PTR(buffer, dataSize)                                    \
    ((int *)(SKETCH_BASE_PTR(buffer, dataSize)))
#define TEMP_NAME_LEN_VAL(buffer, dataSize)                                    \
    (*(TEMP_NAME_LEN_PTR(buffer, dataSize)))
#define TEMP_NAME_PTR(buffer, dataSize)                                        \
    ((char *)(SKETCH_BASE_PTR(buffer, dataSize) + sizeof(int)))

#define TEMP_AGE_PTR(buffer, dataSize)                                         \
    ((int *)(TEMP_NAME_PTR(buffer, dataSize) + TEMP_NAME_SIZE * sizeof(char)))
#define TEMP_AGE_VAL(buffer, dataSize) (*(TEMP_AGE_PTR(buffer, dataSize)))

#define TEMP_EMAIL_LEN_PTR(buffer, dataSize)                                   \
    ((int *)((char *)(TEMP_AGE_PTR(buffer, dataSize)) + sizeof(int)))
#define TEMP_EMAIL_LEN_VAL(buffer, dataSize)                                   \
    (*(TEMP_EMAIL_LEN_PTR(buffer, dataSize)))
#define TEMP_EMAIL_PTR(buffer, dataSize)                                       \
    ((char *)((char *)(TEMP_EMAIL_LEN_PTR(buffer, dataSize)) + sizeof(int)))

#define SKETCH_SIZE                                                            \
    ((size_t)(3 * sizeof(int) + TEMP_NAME_SIZE * sizeof(char) +                \
              TEMP_EMAIL_SIZE * sizeof(char)))

// SKETCH AUX MACROS
#define BUILD_PTR(buffer) SKETCH_BASE_PTR(buffer, BUFFER_DATASIZE_VAL(buffer))
#define BUILD_OFFSET_PTR(buffer)                                               \
    ((size_t *)((char *)BUILD_PTR(buffer) + SKETCH_SIZE - sizeof(size_t)))
#define BUILD_OFFSET_VAL(buffer) (*(BUILD_OFFSET_PTR(buffer)))

// NEW PERSON MACRO

#define NEXT_PERSON(buffer)                                                    \
    ((char *)BUFFER_PCURRENT_VAL(buffer) +                                     \
     CURRENT_PERSON_SIZE(BUFFER_PCURRENT_VAL(buffer)))

#define NEW_PERSON_PTR(buffer)                                                 \
    ((char *)BUFFER_PEOPLE_PTR(buffer) + BUFFER_DATASIZE_VAL(buffer))

// NEW PERSON MACRO
#define NEW_PERSON_BLOCK_SIZE(nameLen, emailLen)                               \
    (sizeof(int) + (nameLen) + sizeof(int) + sizeof(int) + (emailLen))

// main functions
void addPerson(void **pBuffer);
void removePerson(void **pBuffer);
void searchPerson(void **pBuffer);
void listPeople(void *pBuffer);

// aux functions
void getDataSize(void *pBuffer);
void findPersonByEmail(void *pBuffer);

int main() {
    void *pBuffer = NULL;

    pBuffer = malloc(METADATA_SIZE);

    if (!pBuffer) {
        printf("Failed to allocate buffer.\n");
        return 0;
    }

    memset(pBuffer, 0, METADATA_SIZE);

    BUFFER_OPTION_VAL(pBuffer) = 0;
    BUFFER_PEOPLE_COUNT_VAL(pBuffer) = 0;
    BUFFER_I_VAL(pBuffer) = 0;
    BUFFER_DATASIZE_VAL(pBuffer) = 0;
    BUFFER_OLDDATASIZE_VAL(pBuffer) = 0;
    BUFFER_PCURRENT_VAL(pBuffer) = NULL;

    // BUFFER_OPTION_VAL(pBuffer) = 0;
    // BUFFER_PEOPLE_COUNT_VAL(pBuffer) = 0;

    while (BUFFER_OPTION_VAL(pBuffer) != 5) {
        printf(
            "\n1 - Add Person\n2 - Remove Person\n3 - Search Person\n4 - List "
            "People\n5 - Exit\n");
        printf("Choose an option: ");
        if (scanf(" %d", BUFFER_OPTION_PTR(pBuffer)) != 1) {
            BUFFER_OPTION_VAL(pBuffer) = 0;
        }
        // scanf(" %d", BUFFER_OPTION_PTR(pBuffer));

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
            // clearMemmory(&pBuffer);
            break;
        default:
            printf("Isn't a valid option... Try again.\n");
        }
    }

    free(pBuffer);

    return 0;
}

void getDataSize(void *pBuffer) {
    if (!pBuffer)
        return;

    BUFFER_I_VAL(pBuffer) = 0;
    BUFFER_OLDDATASIZE_VAL(pBuffer) = BUFFER_DATASIZE_VAL(pBuffer);
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

// TODO: add people by name
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
        printf(">>> The person was successfully removed. <<<\n");
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
        printf("\tPERSON: %d\n", BUFFER_I_VAL(pBuffer) + 1);
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
