#include <map_utils.h>
#include <stdbool.h>

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
    return strcmp(str_a, str_b) == 0;
}

unsigned long long IntPtrHash(void* int_ptr) {
    return *(int*)int_ptr;
}

bool IntPtrEq(void* int_a, void* int_b) {
    return *(int*)int_a == *(int*)int_b;
}

unsigned long long IntHash(void* int_val) { /* purposefull illegal conversion */
    return int_val;
}

bool IntEq(void* int_a, void* int_b) { /* purposefull illegal conversion */
    return int_a == int_b;
}