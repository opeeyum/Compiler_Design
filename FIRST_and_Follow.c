#include <stdio.h>
#include <ctype.h>
#include <string.h>

int nofpro=0, opptr=0, varptr=0, terptr=0;
char op[10], variables[20];
char productions[20][20], first_val[30][30], follow_val[30][30];

void first(char);
void find_variables();
void duprev(char*);
void follow(char, int);
void cpy_wo_dollar(char*, char*);
int find_index(char*, char);

int main()
{
    printf("____________________________________First & Follow_______________________________");
    printf("\n\n");
    FILE *fptr;
    fptr = fopen("C:\\Users\\Omprakash\\Desktop\\Python\\file1.txt", "r");
    int i=0;
    while(!feof(fptr))
    {
        printf("Production no. %2d : ", i+1);
        fgets(productions[i], 20, fptr);
        printf("%s", productions[i]);
        i++;
    }
    printf("\n");
    nofpro=i;
    find_variables();

    for(i=0; i<varptr; i++)
    {
        first(variables[i]);
        duprev(op);
        strcpy(first_val[i], op);

        printf("\nFIRST of %c : { ", variables[i]);
        for(int j=0; first_val[i][j] != '\0'; j++)
            printf("% c, ", first_val[i][j]);
        printf("}");

        opptr=0;
        memset(op,0,strlen(op));
    }
    printf("\n");

    for(i=0; i<varptr; i++)
    {
        follow(variables[i], i);
        duprev(follow_val[i]);

        printf("\nFOLLOW of %c : { ", variables[i]);
        for(int j=0; follow_val[i][j] != '\0'; j++)
            printf("% c, ", follow_val[i][j]);
        printf("}");
    }
    printf("\n");

    fclose(fptr);
    return 0;
}

void first(char t)
{
    for(int i=0; i<nofpro; i++)
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
                    if(productions[i][j+1] != '\n'&&strchr(op, '^'))
                    {
                        opptr--;
                    }
                    else
                    {
                        break;
                    }
                }
                j++;
            }
        }
    }
}

void follow(char t, int fvptr)
{
    follow_val[0][0] = '$';
    for(int i=0; i<nofpro; i++)
    {
        for(int j=2;productions[i][j]!='\0'; j++)
        {
            if(productions[i][j]==t  && productions[i][j+1]!='\n')
            {
                while(productions[i][++j]!='\n')
                {
                    if(!isupper(productions[i][j]))
                    {
                        char c = productions[i][j];
                        strncat(follow_val[fvptr], &c, 1);
                        break;
                    }
                    int temptr = find_index(variables, productions[i][j]);
                    if(!strchr(first_val[temptr], '^'))
                    {
                        strcat(follow_val[fvptr], first_val[temptr]);
                        break;
                    }
                    else if(productions[i][j+1]!='\n')
                    {
                       cpy_wo_dollar(follow_val[fvptr], first_val[temptr]);
                    }
                    else
                    {
                        cpy_wo_dollar(follow_val[fvptr], first_val[temptr]);
                        temptr = find_index(variables, productions[i][0]);
                        strcat(follow_val[fvptr], follow_val[temptr]);
                    }
                }
            }
            else if(productions[i][j]==t  && productions[i][j+1]=='\n')
            {
                int temptr = find_index(variables, productions[i][0]);
                strcat(follow_val[fvptr], follow_val[temptr]);
            }
        }
    }
}

void find_variables()
{
    for(int i=0; i<nofpro; i++)
    {
        int flag=0;
        for(int j=0; j<varptr; j++)
        {
            if(variables[j] == productions[i][0])
            {
                flag=1;
                break;
            }
        }
        if (flag != 1)
        {
            variables[varptr++] = productions[i][0];
        }
    }
}

void duprev(char *arr)
{
    for (int i = 0; arr[i]!='\0'; i++)
	{
		for(int j = i + 1; arr[j]!='\0'; j++)
		{
    		if(arr[i] == arr[j])
    		{
    			for(int k = j; arr[k]!='\0'; k++)
    			{
    				arr[k] = arr[k + 1];
				}
				j--;
			}
		}
	}
}

void cpy_wo_dollar(char*dest, char*src)
{
   for(int k=0; src[k] != '\0'; k++)
   {
       if(src[k] == '^')
       {
           continue;
       }
       char c = *&src[k];
       strncat(dest, &c, 1);
   }
}

int find_index(char* arr, char t)
{
    for(int k=0; arr[k]!='\0'; k++)
    {
        if(arr[k]==t)
        {
            return k;
        }
    }
    return -1;
}
