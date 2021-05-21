#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Colours
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define DEFAULT "\x1b[0m"

#define PADLEN 30

// simplifying checking two of same type are equal
#define EQUALS(exp, result, typ) (*((typ*) exp) == *((typ*) result))
#define COMP(exp, result, typ, disp) printf("F -> Result should have been: " disp " but was: " disp DEFAULT, *((typ*) exp), *((typ*) result))

// types used in tests
typedef enum {CHAR, INT32, INT16, BOOL} type;

// ints for section number and test (within a section) number
unsigned int sectionno, testno;

// setup the section, 
void starttests(char * testfile) {
    printf(YELLOW "Starting Tests for: " BLUE "%s" DEFAULT, testfile);
    sectionno = 0;
    testno = 0;
}

// get a set length of padding
char *charpadding(unsigned int length, char filler) {
    char *padding = malloc(length + 1);
    padding[length] = '\0';
    memset(padding, filler, length);
    return padding;
}

void testsection(char *name) {
    sectionno++;
    testno = 0;
    printf(MAGENTA "\n%i. Test Section: %s" DEFAULT, sectionno, name);
}

/* Take expected, result and their types, check they match and print out result.
    expected    <- 
*/
void runtest(void* expected, void* result, type typ, char * description) {
    testno++;
    bool passed;
    switch(typ) {
        case CHAR: passed = EQUALS(expected, result, char); break;
        case INT32: passed = EQUALS(expected, result, uint32_t); break;
        case INT16: passed = EQUALS(expected, result, uint16_t); break;
        case BOOL: passed = EQUALS(expected, result, bool); break;
    }


    int padlen = PADLEN - strlen(description);
    assert(padlen >= 0);

    char * descrpadding = charpadding(padlen, ' ');

    printf(passed?GREEN:RED);

    printf("\n    %i: %s%s  ", testno, description, descrpadding);

    free(descrpadding);

    if (passed) {
        printf("P" DEFAULT);
    } else {
        if (typ == CHAR) {
            COMP(expected, result, char, "%c");
        } else {
            COMP(expected, result, int, "%i");
        }
    }
    printf(DEFAULT);
}

void int32test(uint32_t expected, uint32_t result, char * description) {
    runtest(&expected, &result, INT32, description);
}

void booltest(uint32_t expected, uint32_t result, char * description) {
    runtest(&expected, &result, BOOL, description);
}