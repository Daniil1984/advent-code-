#include <stdio.h>

int main(void)
{   
    int count = 0;
    int first;
    int second;
    int third;
    int sum;
    int changes = 0;
    if (scanf("%d", &first) != 1 || scanf("%d", &second) != 1 || scanf("%d", &third) != 1) {
        return -1;
    }
    if (second > first) {
        count++;
    }
    sum = first + second + third;
    first = second;
    second = third;
    while (scanf("%d", &third) == 1) {
        if (second > first) {
            count++;
        }
        if (first + second + third > sum) {
            changes++;
        }
        sum = first + second + third; 
        first = second;
        second = third;
    }
    if (second > first) {
        count++;
    }
    printf("%d\n%d\n", count, changes);
    return 0;
}
