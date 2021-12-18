#include <stdio.h>

int main(void)
{
    int count = 0;
    int v1;
    int v2;
    int v3;
    int sum;
    int changes = 0;
    int scan1;
    int scan2;
    int scan3;
    scan1 = scanf("%d", &v1);
    scan2 = scanf("%d", &v2);
    scan3 = scanf("%d", &v3);

    if (scan1 != 1 || scan2 != 1 || scan3 != 1) {
        return -1;
    }
    if (v2 > v1) {
        count++;
    }
    sum = v1 + v2 + v3;
    v1 = v2;
    v2 = v3;
    while (scanf("%d", &v3) == 1) {
        if (v2 > v1) {
            count++;
        }
        if (v1 + v2 + v3 > sum) {
            changes++;
        }
        sum = v1 + v2 + v3;
        v1 = v2;
        v2 = v3;
    }
    if (v2 > v1) {
        count++;
    }
    printf("%d\n%d\n", count, changes);
    return 0;
}
