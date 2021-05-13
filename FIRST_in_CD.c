#include <stdio.h>
#include <ctype.h>

int n, opptr=0;
char productions[20][20];
char op[10];

void first(char);

int main()
{
    printf("How many productions are there? ");
    scanf("%i", &n);
    getchar();
    printf("\n");
    for(int i=0; i<n; i++)
    {
        printf("Enter production no. %d : ", i+1);
        fgets(productions[i], 20, stdin);
    }
    char t, recur;
    do
    {
        printf("\nEnter the Terminal to find FIRST: ");
        scanf("%c", &t);

        first(t);
        printf("\nFIRST of %c : { ", t);
        for(int i=0; i<opptr; i++)
        {
            printf("%c, ",op[i]);
        }
        printf("}\n");
        opptr = 0;
        op[0]= '\0';

        printf("\nPress C to continue. ");
        getchar();
        scanf("%c", &recur);
        getchar();
    }while(recur=='c' || recur=='C');
    return 0;
}

void first(char t)
{
    for(int i=0; i<n; i++)
    {
        if (productions[i][0]== t)
        {
            int j=2;
            while(productions[i][j] != '\n')
            {
                if(!isupper(productions[i][j]))
                {
                    op[opptr++] = productions[i][j];
                    break;
                }
                else
                {
                    first(productions[i][j]);
                    if(productions[i][j+1] != '\n')
                    {
                        opptr--;
                    }
                }
                j++;
            }
        }
    }
}
