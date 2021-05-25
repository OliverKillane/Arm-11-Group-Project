#include <stdbool.h>
// #include <assemble.h>
#include <stdio.h>
#include <assert.h>
#include "assemble_utils.h"

bool stringsAreEqual(char *str1, char *str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);
    // printf("Comparing: '%s' to '%s'\n", str1, str2);
    for (; *str1 != '\0' && *str2 != '\0'; str1++, str2++) {
        if (*str1 != *str2) {
            return false;
        }
    }

    return true;

}

bool listOfStringsAreEqual(List list1, List list2) {
    ListIterator list2iter = ListBegin(list2);
    ListIterator list1iter = ListBegin(list1);


    while (!ListIteratorEqual(list1iter, ListEnd(list1)) 
        && !ListIteratorEqual(list2iter, ListEnd(list2)) ) {

        char *str1 = ListIteratorGet(list1iter);
        char *str2 = ListIteratorGet(list2iter);

        if (!stringsAreEqual(str1, str2)) {
            return false;
        }

        ListIteratorIncr(&list1iter);
        ListIteratorIncr(&list2iter);
    }

    if (!ListIteratorEqual(list1iter, ListEnd(list1)) 
        || !ListIteratorEqual(list2iter, ListEnd(list2)) ) {
        return false;
    }

    return true;
}

bool listOfListsOfStringsAreEqual(List list1, List list2) {
    ListIterator list2iter = ListBegin(list2);
    ListIterator list1iter = ListBegin(list1);


    while (!ListIteratorEqual(list1iter, ListEnd(list1)) 
        && !ListIteratorEqual(list2iter, ListEnd(list2)) ) {

        List subList1 = ListIteratorGet(list1iter);
        List subList2 = ListIteratorGet(list2iter);

        if (!listOfStringsAreEqual(subList1, subList2)) {
            return false;
        }

        ListIteratorIncr(&list1iter);
        ListIteratorIncr(&list2iter);
    }

    if (!ListIteratorEqual(list1iter, ListEnd(list1)) 
        || !ListIteratorEqual(list2iter, ListEnd(list2)) ) {
        return false;
    }

    return true;
}

void testReadFileLines() {

    List expected = NewEmptyList();

    ListPushBack(expected, "mov r0,#1\n");
    ListPushBack(expected, "mov r1,#5\n");
    ListPushBack(expected, "loop:\n");
    ListPushBack(expected, "mul r2,r1,r0\n");
    ListPushBack(expected, "mov r0,r2\n");
    ListPushBack(expected, "sub r1,r1,#1\n");
    ListPushBack(expected, "cmp r1,#0\n");
    ListPushBack(expected, "bne loop\n");
    ListPushBack(expected, "mov r3,#0x100\n");
    ListPushBack(expected, "str r2,[r3]\n");


    List test = readFileLines("./fact.s");

    assert(listOfStringsAreEqual(expected, test));

    DeleteList(expected);
    LISTFOR(test, iter) {
        free(ListIteratorGet(iter));
    }
    DeleteList(test);
}

void testRemoveColon() {
    assert(stringsAreEqual("hello", "hello:"));
    assert(stringsAreEqual("hello", "hello"));
    assert(!stringsAreEqual(":hello", "hello"));
}

void testTokenize() {
    List lines = readFileLines("./tokenTests.s");
    Map symbolTable = NewEmptyMap(StringHash, StringEq);
    int totalInstructions = 0;

    List tokens = tokenize(lines, symbolTable, &totalInstructions);

    List expectedTokens = NewEmptyList();

    List lineTokens = NewEmptyList();
    ListPushBack(lineTokens, "mov");
    ListPushBack(lineTokens, "r0");
    ListPushBack(lineTokens, "[");
    ListPushBack(lineTokens, "r2");
    ListPushBack(lineTokens, "+r3");
    ListPushBack(lineTokens, "#4");
    ListPushBack(lineTokens, "]");
    ListPushBack(expectedTokens, lineTokens);

    lineTokens = NewEmptyList();
    ListPushBack(lineTokens, "mul");
    ListPushBack(lineTokens, "r2");
    ListPushBack(lineTokens, "r1");
    ListPushBack(lineTokens, "r0");
    ListPushBack(expectedTokens, lineTokens);

    lineTokens = NewEmptyList();
    ListPushBack(lineTokens, "bne");
    ListPushBack(lineTokens, "loop");
    ListPushBack(expectedTokens, lineTokens);

    lineTokens = NewEmptyList();
    ListPushBack(lineTokens, "mov");
    ListPushBack(lineTokens, "r3");
    ListPushBack(lineTokens, "#0x100");
    ListPushBack(expectedTokens, lineTokens);

    assert(totalInstructions == 4);
    assert(MapGet(symbolTable, "loop") == 1);
    assert(MapGet(symbolTable, "bruh") == 3);
    assert(listOfListsOfStringsAreEqual(expectedTokens, tokens));

    LISTFOR(expectedTokens, iter) {
        DeleteList(ListIteratorGet(iter));
    }
    DeleteList(tokens);
    DeleteList(lines);
    DeleteList(expectedTokens);
    DeleteMap(symbolTable);

}

void testTokensToBinary() {
    Map symbolTable = NewEmptyMap(StringHash, StringEq);
    List lines = readFileLines("./fact.s");
    int totalInstructions = 0;
    List tokens = tokenize(lines, symbolTable, &totalInstructions);
    Vector binaryTokens = tokensToBinary(symbolTable, tokens, totalInstructions);

    const int factBinary[] =
        { 0xe3a00001, 0xe3a01005, 0xe0020091,
        0xe1a00002, 0xe2411001,
        0xe3510000, 0x1afffffa, 
        0xe3a03c01, 0xe5832000};

    assert(binaryTokens -> size == 9);
    bool correct = true;
    for (int i=0; i<8; i++) {
        correct = correct && (factBinary[i] == VectorGet(binaryTokens, i));
    }

    assert(correct);

    DeleteMap(symbolTable);
    LISTFOR(lines, iter) {
        free(ListIteratorGet(iter));
    }
    DeleteList(lines);
    LISTFOR(tokens, iter) {
        List toks = ListIteratorGet(iter);
        LISTFOR(tokens, iter2) {
            free(ListIteratorGet(iter2));
        }
        DeleteList(ListIteratorGet(iter));
    }
    DeleteList(tokens);
    DeleteVector(binaryTokens);
}

int main(void) {
    // runCommandGenTests();

    testRemoveColon();
    printf("Remove colon tests passed\n");

    testReadFileLines();
    printf("Read file lines tests passed\n");

    testTokenize();
    printf("Tokenize tests passed\n");

    testTokensToBinary();
    printf("Tokens to binary tests passed\n");

    printf("Assemble tests passed\n");
} 