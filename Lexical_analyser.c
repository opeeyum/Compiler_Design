#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main()
{
    char instruction[300],temp,tmp[15];
    int pos=0,i,j,k,flagi,count=0;

    char separators[13]={'(',')','{','}','[',']','.',',',':',';','<','>','?'};
    char operators[6]={'+','-','=','/','*','^'};
    char keywords[8][10]={"main","if","else","switch","void","do","while","for"};
    char datatypes[6][10]={"int","char","float","double","string","long"};

    printf("\t\t\t------------------------------Lexical analyzer---------------------------------\n");

    printf("Enter instruction : ");
    fgets(instruction, 300, stdin);

    for(i=0;instruction[i]!='\0';i++)
    {
        if((instruction[i]!=' ')&&(instruction[i]!='\n'))
        {
            temp=instruction[i];
            /* Check for Separators */
            for(j=0;j<13;j++)
            {
                if(temp==separators[j])
                {
                    printf("\n %c \t : separator",temp);
                    count++;
                }
            }
            /* Check for operators*/
            for(j=0;j<6;j++)
            {
                if(temp==operators[j])
                {
                    printf("\n %c \t : Operator",temp);
                    count++;
                }
            }
            /* Check for integers*/
            if(isdigit(instruction[i]))
            {
                k=0;
                while((isdigit(instruction[i]))||instruction[i]=='.')
                    tmp[k++]=instruction[i++];
                tmp[k]='\0';i--;
                printf("\n %s \t : Number",tmp);
                count++;
            }
            /* Check for keywords, data types, identifiers */
            if(isalpha(instruction[i]))
            {
                k=0;
                while(isalpha(instruction[i]))
                    tmp[k++]=instruction[i++];
                tmp[k]='\0';i--;
                flagi=1;
                for(j=0;j<8;j++)
                {
                    if((strcmp(tmp,keywords[j]))==0)
                    {
                        printf("\n %s \t : Keyword",tmp);
                        count++;
                        flagi=0;
                        break;
                    }
                }
                for(j=0;j<6;j++)
                {
                    if((strcmp(tmp,datatypes[j]))==0)
                    {
                        printf("\n %s \t : Data-type",tmp);
                        count++;
                        flagi=0;
                        break;
                    }
                }
                if(flagi==1)
                {
                    printf("\n %s \t : User-defined-identifier",tmp);
                    count++;
                }
            }
        }
    }
    printf("\nTotal token identified: %d", count);
    printf("\n---------------------------------------------------------\n");
}
