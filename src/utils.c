#include "utils.h"

int romanToArabic(const char* roman, int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        switch (roman[i]) {
            case 'N': return 0;
            case 'I': result += 1; break;
            case 'V': result += 5; break;
            case 'X': result += 10; break;
            case 'L': result += 50; break;
            case 'C': result += 100; break;
            case 'D': result += 500; break;
            case 'M': result += 1000; break;
        }
        if (i > 0) {
            if ((roman[i] == 'V' || roman[i] == 'X') && roman[i-1] == 'I') result -= 2;
            if ((roman[i] == 'L' || roman[i] == 'C') && roman[i-1] == 'X') result -= 20;
            if ((roman[i] == 'D' || roman[i] == 'M') && roman[i-1] == 'C') result -= 200;
        }
    }
    return result;
}
