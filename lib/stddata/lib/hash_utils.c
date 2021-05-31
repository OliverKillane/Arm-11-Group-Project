#include <hash_utils.h>
#include <stdbool.h>
#include <string.h>

const long long BASE = 257;
unsigned long long StringHash(void* string_ptr) {
    char* string = (char*)string_ptr;
    unsigned long long sum = 0;
    for(int i = 0; i < strlen(string); i++) {
        sum *= BASE;
        sum += string[i];
    }
    return sum;
}

bool StringEq(void* str_a, void* str_b) {
    return strcmp((char*)str_a, (char*)str_b) == 0;
}

unsigned long long IntHash(void* int_ptr) {
    return *(int*)int_ptr;
}

bool IntEq(void* int_a, void* int_b) {
    return *(int*)int_a == *(int*)int_b;
}

unsigned long long UnsafeIntHash(void* int_ptr) { /* purposfeully illegal conversion */
    return int_ptr;
}

bool UnsafeIntEq(void* int_a, void* int_b) {
    return int_a == int_b;
}
unsigned long long UnsafeIntHash(void* int_ptr) { /* purposfeully illegal conversion */
    return int_ptr;
}

bool UnsafeIntEq(void* int_a, void* int_b) {
    return int_a == int_b;
}