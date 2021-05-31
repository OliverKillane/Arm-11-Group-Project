#include <stdbool.h>
// #include <assemble.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "assemble_utils.h"
// #include "tokenizer.h"
#include "commandgentests.c"

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

bool toksEqual(Token tok1, Token tok2) {
    
    switch (TokenType(tok1)) {
        case TOKEN_LABEL:
            return TokenType(tok2) == TOKEN_LABEL 
                && strcmp(TokenLabel(tok1), TokenLabel(tok2)) == 0; 

        case TOKEN_REGISTER:
            return TokenType(tok2) == TOKEN_REGISTER 
                && TokenRegisterNumber(tok1) == TokenRegisterNumber(tok2);

        case TOKEN_CONSTANT:
            return TokenType(tok2) == TOKEN_CONSTANT 
                && TokenConstantType(tok1) == TokenConstantType(tok2)
                && TokenConstantValue(tok1) == TokenConstantValue(tok2); 
        
        case TOKEN_INSTRUCTION:
            return TokenType(tok2) == TOKEN_INSTRUCTION 
                && TokenInstructionConditionType(tok1) == TokenInstructionConditionType(tok2)
                && TokenInstructionType(tok1) == TokenInstructionType(tok2); 
        
        case TOKEN_SIGN:
            return TokenType(tok2) == TOKEN_SIGN 
                && TokenIsPlus(tok1) == TokenIsPlus(tok2);

        case TOKEN_BRACE:
            return TokenType(tok2) == TOKEN_BRACE 
                && TokenIsOpenBracket(tok1) == TokenIsOpenBracket(tok2);

        default:
            return false;
            break;
    }
}

bool listOfTokensAreEqual(List list1, List list2) {
    ListIterator list2iter = ListBegin(list2);
    ListIterator list1iter = ListBegin(list1);


    while (!ListIteratorEqual(list1iter, ListEnd(list1)) 
        && !ListIteratorEqual(list2iter, ListEnd(list2)) ) {

        Token str1 = ListIteratorGet(list1iter);
        Token str2 = ListIteratorGet(list2iter);

        if (!toksEqual(str1, str2)) {
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

bool listOfListsOfTokensAreEqual(List list1, List list2) {
    ListIterator list2iter = ListBegin(list2);
    ListIterator list1iter = ListBegin(list1);


    while (!ListIteratorEqual(list1iter, ListEnd(list1)) 
        && !ListIteratorEqual(list2iter, ListEnd(list2)) ) {

        List subList1 = ListIteratorGet(list1iter);
        List subList2 = ListIteratorGet(list2iter);

        if (!listOfTokensAreEqual(subList1, subList2)) {
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

// void testRemoveColon() {
//     assert(stringsAreEqual("hello", "hello:"));
//     assert(stringsAreEqual("hello", "hello"));
//     assert(!stringsAreEqual(":hello", "hello"));
// }

void testTokenize() {
    List lines = readFileLines("./tokenTests.s");
    Map symbolTable = NewEmptyMap(StringHash, StringEq);
    int totalInstructions = 0;

    List tokens = tokenize(lines, symbolTable, &totalInstructions);

    List expectedTokens = NewEmptyList();

    List lineTokens = NewEmptyList();
    ListPushBack(lineTokens, NewInstructionToken(COND_AL, INSTR_MOV));
    ListPushBack(lineTokens, NewRegisterToken(0));
    ListPushBack(lineTokens, NewBraceToken(true));
    ListPushBack(lineTokens, NewRegisterToken(2));
    ListPushBack(lineTokens, NewSignToken(true));
    ListPushBack(lineTokens, NewRegisterToken(3));
    ListPushBack(lineTokens, NewConstantToken(CONST_HASH, 4));
    ListPushBack(lineTokens, NewBraceToken(false));
    ListPushBack(expectedTokens, lineTokens);

    lineTokens = NewEmptyList();
    ListPushBack(lineTokens, NewInstructionToken(COND_AL, INSTR_MUL));
    ListPushBack(lineTokens, NewRegisterToken(2));
    ListPushBack(lineTokens, NewRegisterToken(1));
    ListPushBack(lineTokens, NewRegisterToken(0));
    ListPushBack(expectedTokens, lineTokens);

    lineTokens = NewEmptyList();
    ListPushBack(lineTokens, NewInstructionToken(COND_NE, INSTR_BRN));
    ListPushBack(lineTokens, NewLabelToken("loop"));
    ListPushBack(expectedTokens, lineTokens);

    lineTokens = NewEmptyList();
    ListPushBack(lineTokens, NewInstructionToken(COND_AL, INSTR_MOV));
    ListPushBack(lineTokens, NewRegisterToken(3));
    ListPushBack(lineTokens, NewConstantToken(CONST_HASH, 256));
    ListPushBack(expectedTokens, lineTokens);

    assert(listOfListsOfTokensAreEqual(expectedTokens, tokens));

    MAPFOR(symbolTable, iter) {
 	    free((char*)(MapIteratorGet(iter).key));
  	}
	DeleteMap(symbolTable);

	LISTFOR(lines, iter) {
		free(ListIteratorGet(iter));
	}
	DeleteList(lines);

	LISTFOR(tokens, iter1) {
		List line = ListIteratorGet(iter1);
		LISTFOR(line, iter2) {
			Token token = ListIteratorGet(iter2);
			DeleteToken(token);
		}
		DeleteList(line);
	}
	DeleteList(tokens);

    LISTFOR(expectedTokens, iter1) {
		List line = ListIteratorGet(iter1);
		LISTFOR(line, iter2) {
			Token token = ListIteratorGet(iter2);
			DeleteToken(token);
		}
		DeleteList(line);
	}
	DeleteList(expectedTokens);

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

    MAPFOR(symbolTable, iter) {
 	    free((char*)(MapIteratorGet(iter).key));
  	}
	DeleteMap(symbolTable);

	LISTFOR(lines, iter) {
		free(ListIteratorGet(iter));
	}
	DeleteList(lines);

	LISTFOR(tokens, iter1) {
		List line = ListIteratorGet(iter1);
		LISTFOR(line, iter2) {
			Token token = ListIteratorGet(iter2);
			DeleteToken(token);
		}
		DeleteList(line);
	}
	DeleteList(tokens);
    DeleteVector(binaryTokens);
}

void testMatchAlpha() {
    for (char i='0'; i<= '9'; i++) {
        assert(!matchAlpha(i));
    }

    for (char i='a'; i<= 'z'; i++) {
        assert(matchAlpha(i));
    }

    for (char i='A'; i<= 'Z'; i++) {
        assert(matchAlpha(i));
    }
    assert(matchAlpha('a'));
    assert(matchAlpha('d'));
    assert(!matchAlpha(']'));
}

void testIsHex() {
    for (char i='0'; i<= '9'; i++) {
        assert(isHex(i));
    }
    for (char i='a'; i<='f'; i++) {
        assert(isHex(i));
    }
    for (char i='A'; i<='F'; i++) {
        assert(isHex(i));
    }

    assert(!isHex('g'));
    assert(!isHex(']'));
}


void testMatchConditionType() {
    assert(matchConditionType("ne") == COND_NE);
    assert(matchConditionType("ne ") == COND_FAIL);
    assert(matchConditionType("") == COND_AL);
    assert(matchConditionType("hello") == COND_FAIL);
    assert(matchConditionType("eq") == COND_EQ);
    assert(matchConditionType("eqa") == COND_FAIL);
    assert(matchConditionType("le") == COND_LE);
}

void testMatchInstructionToken() {
    Token instr = matchInstructionToken("hello");
    assert(instr == NULL);

    instr = matchInstructionToken("mov");
    assert(TokenInstructionType(instr) == INSTR_MOV);
    assert(TokenInstructionConditionType(instr) == COND_AL); 
    DeleteToken(instr);

    instr = matchInstructionToken("beq");
    assert(TokenInstructionType(instr) == INSTR_BRN);
    assert(TokenInstructionConditionType(instr) == COND_EQ);
    DeleteToken(instr);

    instr = matchInstructionToken("beqe");
    assert(instr == NULL);
}

void testMatchDecimal() {
    assert(matchDecimal("121") == 121);
    assert(matchDecimal("5") == 5);
    assert(matchDecimal("-0") == 0);
    assert(matchDecimal("-15") == -15);
}

void testMatchHex() {
    assert(matchHex("FF") == 255);
    assert(matchHex("5") == 5);
    assert(matchHex("-0") == 0);
    assert(matchHex("-15") == -21);
}

void testMatchRegister() {
    Token reg = matchRegister("hello");
    assert(reg == NULL);

    reg = matchRegister("r0");
    assert(TokenRegisterNumber(reg) == 0);
    DeleteToken(reg);

    reg = matchRegister("r16");
    assert(TokenRegisterNumber(reg) == 16);
    DeleteToken(reg);

    reg = matchRegister("r17");
    assert(reg == NULL);
    reg = matchRegister("r177");
    assert(reg == NULL);
    reg = matchRegister("r-1");
    assert(reg == NULL);
}

void testMatchConstant() {
    Token con = matchConstant("hello");
    assert(con == NULL);

    con = matchConstant("#0xff");
    // printf("1\n");
    assert(TokenConstantValue(con) == 255);
    assert(TokenConstantType(con) == CONST_HASH);
    DeleteToken(con);
    // printf("1\n");

    con = matchConstant("12312");
    // printf("2\n");
    assert(TokenConstantValue(con) == 12312);
    assert(TokenConstantType(con) == CONST_PURE);
    DeleteToken(con);

    con = matchConstant("=-12312");
    // printf("3\n");
    assert(TokenConstantValue(con) == -12312);
    assert(TokenConstantType(con) == CONST_EQUALS);
    DeleteToken(con);

    con = matchConstant("#ff");
    assert(con == NULL);
    // printf("Hello there");
    con = matchConstant("#-0xFF");
    assert(TokenConstantValue(con) == -255);
    assert(TokenConstantType(con) == CONST_HASH);
    DeleteToken(con);
}

int main(void) {
    runCommandGenTests();

    //testRemoveColon();
    //printf("Remove colon tests passed\n");

    testMatchAlpha();
    testIsHex();
    testMatchConditionType();
    testMatchConstant();
    testMatchInstructionToken();
    testMatchRegister();
    printf("bruh\n");
    testMatchHex();
    // printf("bruh\n");
    testMatchDecimal();

    testReadFileLines();
    printf("Read file lines tests passed\n");

    testTokenize();
    printf("Tokenize tests passed\n");

    testTokensToBinary();
    printf("Tokens to binary tests passed\n");

    printf("Assemble tests passed\n");
}