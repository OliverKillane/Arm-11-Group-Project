#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Pretty output colours */
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define DEFAULT "\x1b[0m"

#define PADLEN 50

/* simplifying checking two of same type are equal using void pointers, type */
#define EQUALS(exp, result, typ) (*((typ*) exp) == *((typ*) result))
#define COMP(exp, result, typ, disp) printf("F -> Result should have been: " disp " but was: " disp DEFAULT, *((typ*) exp), *((typ*) result))

/* types used in tests */
typedef enum {CHAR, INT32, INT16, BOOL} type;

/* ints for section number and test (within a section) number */
unsigned int sectionno, testno, nopassed, nofailed;

/* setup tests with starting message */
void starttests(char * testfile) {
    printf(YELLOW "Starting Tests for: " BLUE "%s" DEFAULT, testfile);
    sectionno = 0;
    testno = 0;
}

/* setup the section */
void testsection(char *name) {
    sectionno++;
    testno = 0;
    printf(MAGENTA "\n\n%i. Test Section: %s" DEFAULT, sectionno, name);
}

void testsubsection(char *name) {
    testno = 0;
    printf(BLUE "\n\n Test Subsection: %s\n" DEFAULT, name);
}

void runtest(void* expected, void* result, type typ, char * description) {
    testno++;
    bool passed;

    /* use type to determine equality */
    switch(typ) {
        case CHAR:
            passed = EQUALS(expected, result, char); 
            break;
        case INT32:
            passed = EQUALS(expected, result, uint32_t); 
            break;
        case INT16:
            passed = EQUALS(expected, result, uint16_t); 
            break;
        case BOOL:
            passed = EQUALS(expected, result, bool); 
            break;
        default:
            passed = false;
    }

    /* switch to pass/fail colour */
    printf(passed?GREEN:RED);

    /*print result*/
    printf("\n    %-3i: %-50s  ", testno, description);

    if (passed) {

        /* if passed, increment nopassed and print P */
        printf("P" DEFAULT);
        nopassed++;
    } else {

        /* if failed, increment failed and print expected, result */
        nofailed++;
        if (typ == CHAR) {
            COMP(expected, result, char, "%c");
        } else {
            COMP(expected, result, int, "%i");
        }
    }
    /* reset colours */
    printf(DEFAULT);
}

void int32test(uint32_t expected, uint32_t result, char * description) {
    runtest(&expected, &result, INT32, description);
}

void booltest(uint32_t expected, uint32_t result, char * description) {
    runtest(&expected, &result, BOOL, description);
}

void printResult(){
    printf(MAGENTA "\n\nUnit Test results: " GREEN "%i passed " RED "%i failed\n\n" DEFAULT, nopassed, nofailed);
}