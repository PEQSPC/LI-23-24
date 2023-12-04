#include <stdio.h>
#include "input_output.h"

int lerInteiro(char questao[])
{int res, dado;
 do
 {printf("%s",questao);
  res = scanf("%d",&dado);
 } while(res==0);
 while ((getchar()) != '\n');
 return(dado);
}

float lerReal(char questao[])
{int res;
 float dado;
 do
 {printf("%s",questao);
  res = scanf("%f",&dado);
 } while(res==0);
 while ((getchar()) != '\n');
 return(dado);
}

void lerString(char questao[], char resposta[])
{int res;
 float dado;
 do
 {printf("%s",questao);
  res = scanf("%[^\n]",resposta);
 } while(res==0);
 while ((getchar()) != '\n');
}
