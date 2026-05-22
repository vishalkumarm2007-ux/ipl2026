#include<stdio.h>

union decision{
unsigned char flags;

struct field{
int your_choice:1;
int your_mothers_choice:1;
int your_fathers_choice:1;
int socially_acceptable:1;
int financially_viable:1;
int do_you_have_aptitude:1;
int do_you_like_it:1;
int decision:1;
}field;
};

union decision input();
void make_decision(union decision *d);
void print_decision(union decision d);
void print_conclusion_based_on_flags(union decision d);

int main(){
union decision d;

d=input();

make_decision(&d);

print_decision(d);

print_conclusion_based_on_flags(d);

return 0;
}

union decision input(){
union decision d;

d.flags=0;

printf("Enter 1 for YES and 0 for NO\n");

printf("Does your mother support it? ");
scanf("%d",&d.field.your_mothers_choice);

printf("Does your father support it? ");
scanf("%d",&d.field.your_fathers_choice);

printf("Is it socially acceptable? ");
scanf("%d",&d.field.socially_acceptable);

printf("Is it financially viable? ");
scanf("%d",&d.field.financially_viable);

printf("Do you have aptitude for it? ");
scanf("%d",&d.field.do_you_have_aptitude);

printf("Do you like it? ");
scanf("%d",&d.field.do_you_like_it);

return d;
}

void make_decision(union decision *d){

d->field.your_choice=
d->field.do_you_have_aptitude&&
d->field.do_you_like_it;

d->field.decision=
d->field.your_choice&&
d->field.financially_viable&&
(
d->field.your_mothers_choice||
d->field.your_fathers_choice
)&&
d->field.socially_acceptable;
}

void print_decision(union decision d){

printf("\n=====DECISION REPORT=====\n");

printf("Mother's opinion:%s\n",
d.field.your_mothers_choice?"Supportive":"Not supportive");

printf("Father's opinion:%s\n",
d.field.your_fathers_choice?"Supportive":"Not supportive");

printf("Social acceptance:%s\n",
d.field.socially_acceptable?"Acceptable":"Questionable");

printf("Financial viability:%s\n",
d.field.financially_viable?"Viable":"Risky");

printf("Your aptitude:%s\n",
d.field.do_you_have_aptitude?"Good":"Weak");

printf("Your interest:%s\n",
d.field.do_you_like_it?"You like it":"You dislike it");

printf("Your internal choice:%s\n",
d.field.your_choice?"Positive":"Negative");

printf("\nFINAL DECISION:%s\n",
d.field.decision?"GO AHEAD":"RECONSIDER");
}

void print_conclusion_based_on_flags(union decision d){

printf("\n=====FLAGS ANALYSIS=====\n");

printf("Raw flags value=%u\n",d.flags);

if(d.flags==255){
printf("Perfect alignment.\n");
}
else if(d.flags>200){
printf("Very strong positive indicators.\n");
}
else if(d.flags>100){
printf("Mixed signals.\n");
}
else{
printf("Weak support overall.\n");
}

printf("Binary pattern interpretation:\n");

if(d.field.decision)
printf("-Final decision bit is ON.\n");
else
printf("-Final decision bit is OFF.\n");

if(d.field.your_choice)
printf("-Your heart supports this choice.\n");

if(!d.field.financially_viable)
printf("-Financial risk detected.\n");

if(!d.field.socially_acceptable)
printf("-Possible social resistance.\n");
}