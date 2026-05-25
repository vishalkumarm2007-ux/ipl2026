#include <stdio.h>

union decision {
    unsigned char flags;
    struct {
        unsigned int your_choice:1;
        unsigned int your_mothers_choice:1;
        unsigned int your_fathers_choice:1;
        unsigned int socially_acceptable:1;
        unsigned int financially_viable:1;
        unsigned int do_you_aptitude:1;
        unsigned int do_you_likeit:1;
        unsigned int decision:1;
    } bits;
};

union decision input();
void make_decision(union decision *d);
void print_decsion(union decision d);
void print_conclusion_based_on_flags( union decision d);

static unsigned int ask_bit(const char *prompt)
{
    unsigned int value = 0;
    int read = 0;

    do {
        printf("%s (0 or 1): ", prompt);
        read = scanf("%u", &value);
        while (getchar() != '\n') {
            ;
        }
    } while (read != 1 || (value != 0 && value != 1));

    return value;
}

int main(void)
{
    union decision d = input();
    make_decision(&d);
    print_decsion(d);
    print_conclusion_based_on_flags(d);
    return 0;
}

union decision input()
{
    union decision d = { .flags = 0 };

    puts("Please answer the following questions to build your decision profile.");
    d.bits.your_choice = ask_bit("Do you want it?");
    d.bits.your_mothers_choice = ask_bit("Does your mother want it for you?");
    d.bits.your_fathers_choice = ask_bit("Does your father want it for you?");
    d.bits.socially_acceptable = ask_bit("Is it socially acceptable?");
    d.bits.financially_viable = ask_bit("Is it financially viable?");
    d.bits.do_you_aptitude = ask_bit("Do you have the aptitude for it?");
    d.bits.do_you_likeit = ask_bit("Do you actually like it?");

    return d;
}

void make_decision(union decision *d)
{
    d->bits.decision =
        d->bits.your_choice &&
        ((d->bits.your_mothers_choice && d->bits.your_fathers_choice)
         || d->bits.socially_acceptable) &&
        d->bits.financially_viable &&
        d->bits.do_you_aptitude &&
        d->bits.do_you_likeit;
}

void print_decsion(union decision d)
{
    puts("\nDecision narrative:");
    printf("  You want it: %s\n", d.bits.your_choice ? "yes" : "no");
    printf("  Mother's opinion: %s\n", d.bits.your_mothers_choice ? "support" : "no support");
    printf("  Father's opinion: %s\n", d.bits.your_fathers_choice ? "support" : "no support");
    printf("  Socially acceptable: %s\n", d.bits.socially_acceptable ? "yes" : "no");
    printf("  Financially viable: %s\n", d.bits.financially_viable ? "yes" : "no");
    printf("  Aptitude: %s\n", d.bits.do_you_aptitude ? "yes" : "no");
    printf("  Do you like it: %s\n", d.bits.do_you_likeit ? "yes" : "no");

    if (d.bits.decision) {
        puts("  Final decision: yes. The conditions align well enough to move forward.");
    } else {
        puts("  Final decision: no. At least one required condition failed, so it's safer to wait.");
    }
}

static unsigned int count_bits(unsigned char value)
{
    unsigned int count = 0;

    while (value) {
        count += value & 1;
        value >>= 1;
    }

    return count;
}

void print_conclusion_based_on_flags( union decision d)
{
    unsigned char flags = d.flags;
    unsigned int set_bits = count_bits(flags);

    printf("\nFlags interpretation:\n");
    printf("  Raw flags value: 0x%02X (%u)\n", flags, flags);
    printf("  This value encodes your seven inputs plus the computed decision bit.\n");
    printf("  Active factors: %u out of 8 bits set.\n", set_bits);

    if (flags == 0) {
        puts("  Interpretation: no inputs were positive; the profile is completely neutral.");
    } else if (flags == 0xFF) {
        puts("  Interpretation: every reason and the final decision are positive. A unanimous thumbs-up.");
    } else if (d.bits.decision) {
        puts("  Interpretation: the decision bit is set; the overall profile is supportive.");
    } else {
        puts("  Interpretation: the profile has mixed signals. Some influences are positive, but not enough to seal the decision.");
    }

    if ((flags & 1) && (flags & 0x80)) {
        puts("  Extra note: you want it personally and the computed conclusion also agrees.");
    }
}
