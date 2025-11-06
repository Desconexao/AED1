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
// performance, but there are no unnecessary variables in the functions. I plan
// to make some changes to this code yet

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

#define BUFFER_PCURRENT_PTR(buffer)                                            \
    ((char **)((char *)(buffer) + 3 * sizeof(int) + 1 * sizeof(size_t)))
#define BUFFER_PCURRENT_VAL(buffer) (*(BUFFER_PCURRENT_PTR(buffer)))

#define METADATA_SIZE                                                          \
    ((size_t)(3 * sizeof(int) + sizeof(size_t) + sizeof(char *)))

// NOTE: METADATA AUX MACROS
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

// NOTE :DATA MACRO
#define BUFFER_PEOPLE_PTR(buffer) ((char *)((char *)(buffer) + METADATA_SIZE))

// NOTE: SKETCH MACROS
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

// NOTE: NEW PERSON MACRO

#define NEXT_PERSON(buffer)                                                    \
    ((char *)BUFFER_PCURRENT_VAL(buffer) +                                     \
     CURRENT_PERSON_SIZE(BUFFER_PCURRENT_VAL(buffer)))

#define NEW_PERSON_PTR(buffer)                                                 \
    ((char *)BUFFER_PEOPLE_PTR(buffer) + BUFFER_DATASIZE_VAL(buffer))

// NOTE :NEW PERSON MACRO
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
void clearMemory(void **pBuffer);
