#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int n, opptr=0;
char productions[20][20];
char op[10];

void first(char);
void duprev();

int main()
{
    FILE *fptr;
    fptr = fopen("C:\\Users\\file1.txt", "r"); // file path
    int i=0;
    while(!feof((FILE*)fptr))
    {
        printf("Production no. %d : ", i+1);
        fgets(productions[i], 20, (FILE*)fptr);
        printf("%s", productions[i]);
        i++;
    }
    n=i;
    char t, recur;
    do
    {
        printf("\nEnter the Terminal to find FIRST: ");
        scanf("%c", &t);

        first(t);
        duprev();
        printf("\nFIRST of %c : { ", t);
        for(int i=0; i<strlen(op); i++)
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
    fclose(fptr);
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

void duprev()
{
    for(int i = 0; i < strlen(op); i++)
  	{
  		for(int j = i + 1; op[j] != '\0'; j++)
  		{
  			if(op[j] == op[i])  
			{
  				for(int k = j; op[k] != '\0'; k++)
				{
					op[k] = op[k + 1];
				}
 			}
		}
	}
}

