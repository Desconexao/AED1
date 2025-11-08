#include "agenda.h"

/*
 * Sets 'BUFFER_DATASIZE_VAL' with the current size of the DATA, always making
 * the program knows the real size of DATA.
 * This is practically the most important function of the program
 * */
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

/*
 * Search for a person by email and set `BUFFER_PCURRENT_VAL` to point to that
 * person.
 */
void findPersonByEmail(void *pBuffer) {
  BUFFER_I_VAL(pBuffer) = 0;
  BUFFER_OPTION_VAL(pBuffer) = 0;
  BUFFER_PCURRENT_VAL(pBuffer) = BUFFER_PEOPLE_PTR(pBuffer);

  while (BUFFER_I_VAL(pBuffer) < BUFFER_PEOPLE_COUNT_VAL(pBuffer)) {
    if (strcmp(CURRENT_EMAIL_PTR(BUFFER_PCURRENT_VAL(pBuffer)),
               TEMP_EMAIL_PTR(pBuffer, BUFFER_DATASIZE_VAL(pBuffer))) == 0) {
      BUFFER_OPTION_VAL(pBuffer) = 1;
      break;
    }

    BUFFER_PCURRENT_VAL(pBuffer) +=
        CURRENT_PERSON_SIZE(BUFFER_PCURRENT_VAL(pBuffer));

    BUFFER_I_VAL(pBuffer)++;
  }
}

/*
 * Set the entire buffer area to zero and free it.
 * Also set the pointer to `NULL`.
 * It should be called at the end of program.
 * */
void clearMemory(void **pBuffer) {

  if (pBuffer == NULL || *pBuffer == NULL)
    return;

  memset(*pBuffer, 0, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer));

  free(*pBuffer);

  *pBuffer = NULL;
}

// TODO: search all people with the same name???

/*
 * Adds a person to the `end` of the DATA area.
 * This allocates the size for the new person and then moves all the memory to
 * the right, inserting the new person at the end of the DATA.
 * */
void addPerson(void **pBuffer) {

  getDataSize(*pBuffer);

  *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer) +
                                   SKETCH_SIZE);
  if (!*pBuffer) {
    printf(C_RED "Error allocating the stack\n" C_RESET);
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
    printf(C_RED "Realloc error 2.\n" C_RESET);
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
    printf(C_RED "Error allocating a person\n" C_RESET);
    exit(1);
  }

  printf(C_GREEN "\n> Person registered successfully <\n" C_RESET);

  BUFFER_DATASIZE_VAL(*pBuffer) = 0;
  BUFFER_I_VAL(*pBuffer) = 0;
}

/*
 * It searches for the person and moves the memory after them to the `left`,
 * overwriting the person to be removed.
 *
 * */
void removePerson(void **pBuffer) {
  if (BUFFER_PEOPLE_COUNT_VAL(*pBuffer) == 0) {
    printf(C_YELLOW "\n>>> Theres no person to remove. <<<\n" C_RESET);
    return;
  }

  getDataSize(*pBuffer);

  *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer) +
                                   SKETCH_SIZE);
  if (!*pBuffer) {
    printf(C_RED "Realloc error 1.\n" C_RESET);
    exit(1);
  }

  memset((char *)*pBuffer + METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer), 0,
         SKETCH_SIZE);

  printf("Type an Email to remove person: ");
  scanf(" %49[^\n]", TEMP_EMAIL_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

  findPersonByEmail(*pBuffer);

  if (!BUFFER_OPTION_VAL(*pBuffer)) {
    printf(C_YELLOW "\n>>> The person was not found. <<<\n" C_RESET);
  } else {

    BUFFER_I_VAL(*pBuffer) = CURRENT_PERSON_SIZE(BUFFER_PCURRENT_VAL(*pBuffer));

    BUFFER_PCURRENT_VAL(*pBuffer) += BUFFER_I_VAL(*pBuffer);

    BUFFER_DATASIZE_VAL(*pBuffer) =
        (size_t)(BUFFER_PEOPLE_PTR(*pBuffer) + BUFFER_DATASIZE_VAL(*pBuffer)) -
        (size_t)(BUFFER_PCURRENT_VAL(*pBuffer));

    memmove(BUFFER_PCURRENT_VAL(*pBuffer) - BUFFER_I_VAL(*pBuffer),
            BUFFER_PCURRENT_VAL(*pBuffer), BUFFER_DATASIZE_VAL(*pBuffer));

    BUFFER_PEOPLE_COUNT_VAL(*pBuffer)--;
    printf(C_GREEN "\n>>> The person was successfully removed. <<<\n" C_RESET);
  }

  getDataSize(*pBuffer);

  *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer));

  if (!*pBuffer) {
    printf(C_RED "Realloc error 2.\n" C_RESET);
    exit(1);
  }

  BUFFER_DATASIZE_VAL(*pBuffer) = 0;
  BUFFER_I_VAL(*pBuffer) = 0;
  BUFFER_OPTION_VAL(*pBuffer) = 0;
}

/*
 * Searches for a person by email and returns information about them.
 * */
void searchPerson(void **pBuffer) {
  if (BUFFER_PEOPLE_COUNT_VAL(*pBuffer) == 0) {
    printf(C_YELLOW "\n>>> Theres no person to search. <<<\n" C_RESET);
    return;
  }

  getDataSize(*pBuffer);
  *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer) +
                                   SKETCH_SIZE);
  if (!*pBuffer) {
    printf(C_RED "Realloc error 1.\n" C_RED);
    exit(1);
  }
  memset((char *)*pBuffer + METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer), 0,
         SKETCH_SIZE);

  printf("Email to search: ");
  scanf(" %49[^\n]", TEMP_EMAIL_PTR(*pBuffer, BUFFER_DATASIZE_VAL(*pBuffer)));

  findPersonByEmail(*pBuffer);

  if (BUFFER_OPTION_VAL(*pBuffer) == 0) {
    printf(C_YELLOW "\n>>> The person was not found. <<<\n" C_RESET);
  } else {
    printf(C_CYAN "--------- Person Found ---------\n" C_RESET);
    printf("PERSON: %d\n", BUFFER_I_VAL(*pBuffer) + 1);
    printf("\tName: %s\n", CURRENT_NAME_PTR(BUFFER_PCURRENT_VAL(*pBuffer)));
    printf("\tAGE: %d\n", *(CURRENT_AGE_PTR(BUFFER_PCURRENT_VAL(*pBuffer))));
    printf("\tEMAIL: %s\n", CURRENT_EMAIL_PTR(BUFFER_PCURRENT_VAL(*pBuffer)));
    printf(C_CYAN "--------------------------------\n" C_RESET);
  }

  *pBuffer = realloc(*pBuffer, METADATA_SIZE + BUFFER_DATASIZE_VAL(*pBuffer));
  if (!*pBuffer) {
    printf(C_RED "Realloc error 2.\n" C_RED);
    exit(1);
  }

  BUFFER_DATASIZE_VAL(*pBuffer) = 0;
  BUFFER_I_VAL(*pBuffer) = 0;
  BUFFER_OPTION_VAL(*pBuffer) = 0;
}

/*
 * Lists all information for all people
 * */
void listPeople(void *pBuffer) {
  if (BUFFER_PEOPLE_COUNT_VAL(pBuffer) == 0) {
    printf(C_YELLOW "\n>>> The are no people to list. <<<\n" C_RESET);
    return;
  }

  BUFFER_I_VAL(pBuffer) = 0;
  BUFFER_PCURRENT_VAL(pBuffer) = BUFFER_PEOPLE_PTR(pBuffer);
  printf(C_CYAN "----------- PEOPLE ----------\n" C_RESET);

  while (BUFFER_I_VAL(pBuffer) < BUFFER_PEOPLE_COUNT_VAL(pBuffer)) {
    printf("PERSON: %d\n", BUFFER_I_VAL(pBuffer) + 1);
    printf("\tNAME: %s\n", CURRENT_NAME_PTR(BUFFER_PCURRENT_VAL(pBuffer)));
    printf("\tAGE: %d\n", CURRENT_AGE_VAL(BUFFER_PCURRENT_VAL(pBuffer)));
    printf("\tEMAIL: %s\n", CURRENT_EMAIL_PTR(BUFFER_PCURRENT_VAL(pBuffer)));
    BUFFER_PCURRENT_VAL(pBuffer) = NEXT_PERSON(pBuffer);
    BUFFER_I_VAL(pBuffer)++;
    printf("\n");
  }
  printf(C_CYAN "--------- END PEOPLE ---------\n" C_RESET);

  BUFFER_I_VAL(pBuffer) = 0;
  printf("\n");
}
