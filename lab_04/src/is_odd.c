#include <stdio.h>
#define N 10

int odd_summ(int* pa, int* plen);
int main()
{
    int a[N];
    int len = 0;

    printf(" Input lenthh of array s: ");
    int rc = scanf("%d", &len);
    int res = 0;
    if ((rc == 1) && (len > 0) && (len <= N)) {
        int* pa = &a[0];
        int* plen = pa + len;
        for (int* pcur = pa; pcur < plen; pcur++) {
            printf("Input value of element : ");
            rc += scanf("%d", pcur);
        }

        if (rc == 1 + len) {
            int s = odd_summ(pa, plen);
            if (s != -1)
                printf(" Odd sum is %d ", s);

            else

                res = 1;
        }
        else
            res = 1;
    }
    else
        res = 1;

    return res;
}
int odd_summ(int* pa, int* plen)
{
    int s = 0, k = -1, res = -1;
    for (int* pcur = pa; pcur < plen; pcur++)
        if (*pcur % 2 == 0) {
            s += *pcur;
            k += 1;
        }
    if (k != -1)

        res = s;

    return res;
}