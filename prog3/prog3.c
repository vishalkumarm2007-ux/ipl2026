#include <stdio.h>
#include <stdint.h>

/* Print bits of an integer */
void printIntBits(int n)
{
    int bits = sizeof(int) * 8;

    printf("Integer value: %d\n", n);
    printf("Bits: ");

    for (int i = bits - 1; i >= 0; i--)
    {
        printf("%d", (n >> i) & 1);

        if (i % 8 == 0)
            printf(" ");
    }

    printf("\n");
}

/* Count number of 1 bits */
int countSetBits(int n)
{
    int count = 0;
    unsigned int x = (unsigned int)n;

    while (x)
    {
        x = x & (x - 1);
        count++;
    }

    return count;
}

/* Detect endianess */
void checkEndian()
{
    int x = 1;
    char *p = (char *)&x;

    printf("\n===== Endian Check =====\n");

    if (*p == 1)
        printf("System is Little Endian\n");
    else
        printf("System is Big Endian\n");
}

/* Print memory bytes */
void printBytes(void *ptr, int size)
{
    unsigned char *p = (unsigned char *)ptr;

    printf("Memory bytes: ");

    for (int i = 0; i < size; i++)
    {
        printf("%02X ", p[i]);
    }

    printf("\n");
}

/* Print float bits */
void printFloatBits(float f)
{
    union
    {
        float f;
        uint32_t i;
    } u;

    u.f = f;

    printf("Float value: %f\n", f);

    printf("Bits: ");

    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (u.i >> i) & 1);

        if (i == 31 || i == 23)
            printf(" ");
    }

    printf("\n");

    printf("Sign Bit : %d\n", (u.i >> 31) & 1);

    printf("Exponent : ");
    for (int i = 30; i >= 23; i--)
        printf("%d", (u.i >> i) & 1);

    printf("\n");

    printf("Mantissa : ");
    for (int i = 22; i >= 0; i--)
        printf("%d", (u.i >> i) & 1);

    printf("\n");
}

int main()
{
    int n;
    float f;

    printf("Enter an integer: ");
    scanf("%d", &n);

    printf("\n===== Integer Information =====\n");
    printIntBits(n);

    printf("Number of 1 bits: %d\n", countSetBits(n));

    printf("\n===== Integer Memory Layout =====\n");
    printBytes(&n, sizeof(n));

    checkEndian();

    printf("\nEnter a floating point number: ");
    scanf("%f", &f);

    printf("\n===== Float Information =====\n");
    printFloatBits(f);

    return 0;
}