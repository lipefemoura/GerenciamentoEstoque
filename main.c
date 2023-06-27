
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Permitir caracteres da língua portuguesa (ç,ã,é...)
#include <string.h> // Biblioteca para algumas funções com strings

//As variáveis "produtos", "tamdesc", "descricao" e "contprod" são variáveis globais. Podem ser lidas e modificadas em qualquer parte do código.

float produtos[3][500]; //Matriz que armazena o código, a quantidade e o preço de cada produto. Máximo de 500 produtos.
/*
O número da coluna está associado ao número do produto. Produto 1 = coluna 0, Produto 2 = coluna 1 e assim por diante.
O número da linha representa o tipo de informação armazenado naquela posição.
Linha 0: código do produto (vem da contagem de produtos, variável global "contprod")
Linha 1: quantidade disponível em estoque do produto em questão
Linha 2: preço do produto em questão
Exemplo: Produto 1
         produtos[0][0] = 0
         produtos[1][0] = quantidade do Produto 1
         produtos[2][0] = preço do Produto 1
*/

int tamdesc[500]; //Armazena a quantidade de letras da descrição de cada produto.
/*
Se a descrição do produto 1 for "blusa vermelha", tamdesc[0] = 14.
*/
char descricao[500][25]; // Matriz que armazena a descrição dos produtos.
/*
Ao adicionar um produto, é lida uma string de no máximo 20 caracteres. Esta string é passada, caractere a caractere, para a matriz "descricao".
A linha da matriz "descricao" diz respeito ao produto em questão, enquanto cada coluna, de 0 a 24, recebe uma letra.
*/
int contprod=0; /* Variável que conta quantos produtos já foram inseridos no estoque. É incrementada em 1 sempre que um produto é adicionado e decrementada
                    em 1 sempre que um produto é excluído.  */

int main(void) {
    setlocale(LC_ALL,"Portuguese"); // Permitir caracteres do português (é, ç, ã...)
    int flag=0, opcao=0, item=0;
    char add='s';
    void adicionar(); //Chamada das funções que estão fora da main
    void consulta();
    void atualizar();
    void excluir();
    void exibir();

  do{ // Imprime o menu de opções e executa o switch case que está dentro deste loop enquanto flag!=6. Caso flag=6 o loop é encerrado.

  printf("========== Controle de estoque ==========\n"); //Menu
  printf("Bem-vindo! Escolha uma das seguintes opcoes:\n1) Buscar produto\n2) " //Menu
         "Adicionar produto\n3) Editar produto\n4) Exibir todos os "
         "produtos disponiveis\n5) Excluir produto\n6) Sair\n");
  printf("=========================================\n"); //Menu
  fflush(stdin);
  scanf("%d", &opcao); //Lê a opção do menu escolhida pelo usuário
  system("cls"); // Função que limpa a tela

  switch (opcao) { //Switch case com as opções informadas no menu
  case 1: //Buscar prduto
    consulta(); // Chama a função consulta
    printf("Pressione qualquer tecla para voltar ao menu.\n");
    fflush(stdin); ////Limpa o buffer do teclado para que o comando getch() não receba algo indesejado antes que o usuário pressione alguma tecla
    getch(); //Pausa o programa até que uma tecla seja digitada
    system("cls"); //Limpa a tela
    break;

  case 2: //Adicionar produto
    add='s'; //Define add como s para que o programa entre no laço
    while(add=='s'||add=='S'){ //Executa o laço enquanto add for igual a s
        printf("==========Adicionar produto==========\n");
        adicionar();
        printf("Deseja adicionar outro item?\nS - sim\nN - nao\n");
        fflush(stdin);
        scanf("%c",&add);   //Espera o usuário digitar a letra correspondente a "sim" ou "não"
                            //Caso o usuário digite 's', o programa continua no laço
        system("cls"); //Limpa a tela
    }
    system("cls"); //Caso o usuário digite "n", o laço é encerrado, em seguida o programa limpa a tela e imprime o menu novamente
    break;

  case 3: //Editar produto
    system("cls"); //Limpa a tela para apagar o menu antes de exibir as instruções da opção editar produto
    printf("==========Editar produto==========\n\n");
    atualizar(); //Chama a função atualizar
    printf("\nPressione qualquer tecla para retornar ao menu.");
    fflush(stdin); //Limpa o buffer do teclado para que o comando getch() não receba lixo
    getch(); // Aguarda o usuário pressionar alguma tecla para continuar o programa
    system("cls"); //Limpa a tela
    break;

  case 4: // Exibir todos os produtos
    exibir(); // Chama a função exibir
    printf("\nPressione qualquer tecla para retornar ao menu.");
    fflush(stdin);
    getch();
    system("cls");
    break;

  case 5: //Excluir produto
    printf("==========Excluir produto==========\n");
    printf("Qual produto deseja excluir? ");
    scanf("%d",&item); //Lê o número do produto que o usuário deseja excluir
    if(produtos[0][item-1]!=0 && produtos[0][item-1]==item && contprod>0){ //Verifica se o número do produto informado existe e não permite que 0 seja passado como parâmetro
        excluir(item); //Chama a função excluir, que recebe como parâmetro o número do produto a ser excluído
        printf("Produto excluido com sucesso.\n");
        printf("\nPressione qualquer tecla para retornar ao menu.");
        fflush(stdin);
        getch();
        system("cls");
    }
    else{ //Caso o produto não exista, é informada uma mensagem alertando o usuário
        printf("Produto nao cadastrado.");
        printf("\nPressione qualquer tecla para retornar ao menu.");
        fflush(stdin);
        getch();
        system("cls");
    }
    break;

  case 6: //Sair
      flag=6; //Quando flag=6, o programa sai do laço "do while" inicial, e após o laço nada é executado, terminando o programa.
    break;
  }

  } while(flag!=6); //Condição de parada do laço.

  return 0;
}

void adicionar(){ //Função que cria um novo produto
    int qtde=0, i=0; //Variáveis locais da função adicionar
    float preco=0; //Variáveis locais da função adicionar
    char nome[20]; //Variáveis locais da função adicionar

    printf("Codigo do item: %d",contprod+1); //O número do produto é sempre contprod+1, pois o número do produto deve pertir de 1.
                                             //Também é necessário saber quando contprod é 0, pois indica estoque vazio em outras funções.
    printf("\nDescricao (max. 20 caracteres): ");
    fflush(stdin);
    gets(nome);
    while(strlen(nome)>20){ //Loop para garantir que a descrição do produto tenha no máximo 20 caracteres.
        printf("Limite de 20 caracteres extrapolado.\n");
        printf("Descricao (máx. 20 caracteres): ");
        fflush(stdin);
        gets(nome);
    }
    tamdesc[contprod]=strlen(nome); //Conta quantos caracteres a string "nome" possui e armazena a quantidade no vetor tamdesc, na posição relativa ao número do produto
                                    //Exemplo: a descrição do produto 1 é "blusa azul", logo a posição 0 do vetor "tamdesc" recebe o valor 10.
    for(i=0;i<strlen(nome);i++){
        descricao[contprod][i]=nome[i]; //Armazena cada caractere da string "nome" em uma posição específica da matriz "descricao".
                                        //Exemplo: se a descrição do produto 1 for "ab", descricao[0][0]=nome[0]='a' e descricao[0][1]=nome[1]='b'.
    }
    printf("Quantidade: ");
    fflush(stdin);
    scanf("%d", &qtde); //Lê a quantidade a ser adicionada do produto em questão
    printf("Preco unitario: ");
    fflush(stdin);
    scanf("%f", &preco); //Lê o preço do produto em questão. O programa reconhece APENAS A VÍRGULA como indicativo de casas decimais.
    produtos[0][contprod]=contprod+1; //Armazena o número do produto na posição específica para código (linha 0), correspondente ao produto n (coluna n).
                                      //É adicionado 1 ao valor para que o número do produto armazenado na posição 0 seja 1.
    produtos[1][contprod]=qtde; //Armazena a quantidade do produto na posição específica para quantidade (linha 1), correspondente ao produto n (coluna n).
    produtos[2][contprod]=preco; //Armazena o preço do produto na posição específica para preço (linha 2), correspondente ao produto n (coluna n).
    contprod++; //Incrementa a contagem de produtos em 1.
    printf("Produto adicionado com sucesso! ");
}

void consulta(){ //Função que consulta os dados de um produto escolhido pelo usuário
    int item=0, i=0, j=0, k=0, flag=0; //Variáveis locais da função
    printf("==========Consulta produto==========\n");
    printf("Inserir numero do produto: ");
    fflush(stdin);
    scanf("%d", &item); //Lê o número do produto a ser consultado

    for(i=0;i<500;i++){ //Este laço pode ser repetido até 500 vezes

        if(item==produtos[0][i]&&item!=0){ /* A cada iteração é feita a comparação do número informado pelo usuário com o código do produto
                                              armazenado na primeira linha da matriz "produtos". Por exemplo, se o usuário deseja consultar
                                              o Produto 5, i será incrementado até 4. O valor 4 indicará a coluna da matriz "produtos" que
                                              o programa irá buscar os dados. */
            printf("Descricao: ");
            for(j=i;j<i+1;j++){ /*  Impressão da descrição: j recebe o valor relativo ao número do produto, que por sua vez está relacionado
                                    ao número da linha da matriz "descricao". Então, se o usuário está consultando o Produto 5, j = i = 4. A
                                    condição de parada é feita para o laço ser executado apenas uma vez.  */

                for(k=0;k<tamdesc[i];k++){ /* A variável k indica até qual coluna da matriz "descricao", na linha correspondente ao produto
                                              desejado, o programa irá imprimir o caractere armazenado na respectiva posição. k cresce de 0
                                              até o valor armazenado em "tamdesc" na posição referente ao produto consultado, ou seja, se a
                                              palavra tiver 5 caracteres, k vai de 0 a 4 */

                    printf("%c", descricao[j][k]); //Imprime o caractere armazenado na posição definida por j e k da matriz "descricao"
                }
            }
            printf("\nQuantidade em estoque: %.f",produtos[1][i]); // Exibe o valor da quantidade relativo ao número do produto desejado
            printf("\nPreco unitario: R$%.2f\n\n",produtos[2][i]); // Exibe o valor do preço relativo ao número do produto desejado
            flag=0; //Atribui o valor 0 para flag. Isso faz o programa entender que o produto existe.
            break;
        }
        else{
            flag=1; //Caso o usuário digite um número de produto não cadastrado, a variável flag recebe valor 1.
        }
    }
    if(flag==1){ //Caso flag seja igual a 1, significa que o número de produto informado não está cadastrado, portanto não existe.
        printf("Produto nao cadastrado.\n");
    }
}

void atualizar(){ /*    Função que edita a quantidade e o preço de um produto já criado. Caso a quantidade seja alterada para 0, é perguntado ao
                        usuário se ele deseja excluir aquele produto.  */

    int coditem=0, qtde=0, i=0, flag=0; //Declaração de variáveis locais da função "atualizar"
    float preco=0;
    char exc;
    void excluir(); //Declaração da função excluir, que será utilizada dentro da função "atualizar"

    if(contprod==0){ //Quando contprod=0, não existe nenhum produto cadastrado. Logo, o programa informa isso ao usuário e não executa o que está no "else"
        printf("Nenhum produto cadastrado.\n");
    }
    else{ //Caso contprod seja maior que 0, as instruções do "else" são executadas
        printf("Digite o numero produto a ser atualizado: ");
        scanf("%d",&coditem); //Leitura do número do produto a ser atualizado
        for(i=0;i<contprod;i++){ //Laço que inicia com i = 0 até o número de produtos já adicionados
            if(produtos[0][i]==coditem){ /* Caso o número do produto coincida com um dos códigos armazenados na linha de códigos de produtos da matriz
                                            "produtos", a variável flag tem seu valor alterado para 1 e o laço é interrompido  */
                flag=1;
                break;
            }
        }
        if(flag==1){ //Se flag = 1, o número de produto que o usuário digitou existe, logo, pode ser atualizado na matriz "produtos".
            printf("Nova quantidade: ");
            scanf("%d", &qtde); // O programa lê a nova quantidade do produto
            printf("Novo preco: ");
            scanf("%f",&preco); //O programa lê o novo preço do produto
            if(qtde==0){ //Caso o usuário digite 0 na quantidade, é oferecida a opção de excluir o produto do estoque.
                printf("Deseja excluir este item do estoque?\nS - sim\nN - não\n");
                fflush(stdin);
                scanf("%c",&exc); //O programa lê a opção que o usuário escolheu, 's' para sim e 'n' para não
                if(exc=='s'||exc=='S'){ //Caso a opção seja sim, o programa chama a função excluir e passa como parâmetro o número do item a ser excluído
                    excluir(coditem);
                    printf("Produto excluido com sucesso.\n");
                }
                else if(exc=='n'||exc=='N'){ //Caso a opção seja não, o produto não é excluído e os valores de quantidade e preço são atualizados normalmente
                    produtos[1][coditem-1]=qtde; //Atualiza a quantidade na matriz "produtos"
                    produtos[2][coditem-1]=preco; //Atualiza o preço na matriz "produtos"
                    printf("Produto atualizado com sucesso!");
                }
            }
            else{ //Se a nova quantidade não for 0, o programa não oferece a opção de excluir o produto
                produtos[1][coditem-1]=qtde; //Atualiza a quantidade na matriz "produtos"
                produtos[2][coditem-1]=preco; //Atualiza o preço na matriz "produtos"
                printf("Produto atualizado com sucesso!");
            }
        }
        else{ //Se flag = 0, o número de produto informado não existe. O programa informa ao usuário que este produto ainda não foi cadastrado.
            printf("Produto nao cadastrado.\n");
        }
    }
}

void exibir(){ //Função que exibe todos os produtos já cadastrados no estoque
    int i=0, j=0, k=0; //Declaração das variáveis locais da função exibir
    printf("==========Estoque da loja==========\n");
    for(i=0;i<contprod;i++){ //Inicia um laço que se repete n vezes, no qual n corresponde ao número de podutos diferentes existentes em estoque.
            if(produtos[0][i]!=0){ //Os produtos são mostrados apenas se "contprod" for maior que 0, ou seja, se existirem produtos no estoque.
                printf("\n----- Produto %d -----",i+1);
                printf("\nDescricao: ");
                for(j=i;j<i+1;j++){ //Laço para exibir cada caractere da descrição. A variável j recebe o número relacionado à linha do produto exibido
                for(k=0;k<tamdesc[i];k++){ //A variável k aumenta a partir de 0 até a quantidade de caracteres da descrição do produto
                    printf("%c",descricao[j][k]); //O programa mostra o que está armazenado na matriz "descricao", na linha j e coluna k
                }
            }
            printf("\nQuantidade: %.f",produtos[1][i]); //O programa mostra a quantidade de itens do produto "i"
            printf("\nPreco: %.2f\n",produtos[2][i]); //O programa mostra o preço do produto "i"
            }
    }
}

void excluir(int prod){ //Função que exclui um produto. Esta função recebe como parâmetro uma variável do tipo inteiro, que correponde ao número do produto.
    int i=0, j=0; //Declaração de variáveis locais da função excluir

/* Quando um produto é excluído do estoque, os valores de código, quantidade e preço dos produtos que se encontram nas posições seguintes são deslocados
   para a posição imediatamente anterior à que ocupam atualmente. Além disso, os valores do último produto são zerados e os caracteres da sua descrição
   são substituídos por espaços. A variável contprod é decrementada em 1, para que  o programa entenda que a quantidade de produtos diminuiu em 1. */

    for(i=prod-1;i<contprod;i++){ //Este laço substitui os valores de um produto na posição i pelos valores da posição seguinte, i+1.
        produtos[0][i]=produtos[0][i+1]-1; //Atualiza número do produto em cada posição
        produtos[1][i]=produtos[1][i+1]; //Atualiza a quantidade de produtos de cada posição
        produtos[2][i]=produtos[2][i+1]; //Atualiza o preço dos produtos de cada posição
    }
    produtos[0][contprod]=0; //Os valores do último produto são zerados
    produtos[1][contprod]=0; //Os valores do último produto são zerados
    produtos[2][contprod]=0; //Os valores do último produto são zerados

    for(i=0;i<25;i++){
        for(j=prod-1;j<contprod;j++){ //Este laço substitui os caracteres do produto i pelos caracteres do produto i+1.
            descricao[j][i]=descricao[j+1][i];
        }
    }
    for(i=prod-1;i<=contprod;i++){ /* Este laço atualiza o tamanho da descrição de cada item, deslocando o valor da posição atual para a posição
                                      imediatamente anterior. Isto garante que na hora de exibir a descrição dos produtos, o programa exiba os
                                      caracteres certos, uma vez que podem existir outros caracteres além da posição máxima especificada.  */
        tamdesc[i]=tamdesc[i+1];
    }
    contprod--; //A variável global que conta a quantidade de produtos existentes é decrementada em 1, já que um produto foi excluído do estoque
}
