#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/*
    This file is a code to make an 'To do List' aplication, thats is a small project in C Language to make better someones of my skills.
    Stay free to use the code on your own and make changes.
*/

/*
    Esse arquivo é um codigo para uma aplicação do tipo 'To do List', é um pequeno projeto em Linguagem C para melhorar algumas habilidades.
    Fique a vontade para utilizar o codigo e realizar alterações.
*/

/*
    Explicando o contexto geral do codigo:
    - Ele consulta a data e hora com o ponteiro de tempo.
    - Salva a data de hoje em um arquivo de bloco de notas (data de registro.txt).
    - Chama uma função que consulta a data, salva no bloco de notas e compara com
      algum possivel registro no arquivo de bloco de notas de registro de atividades
      (registro.txt),.
    - Caso exista registros ela os imprime.
    - Ao final do relatório é dado a opção de gerar um novo registro no arquivo de
      registro de atividades (registro.txt). Ao final do registro ele repete a opção 
      de gerar um novo registro.
*/

int checaData(){

    //Abre o arquivo de registros de atividades.

        FILE* arquivo;

        arquivo = fopen("registro.txt", "r");

    //Abre o aquivo de registro de data atual.

        FILE* arquivo_datado;

        arquivo_datado = fopen("data de registro.txt", "r");

    //String que recebe a data que vai procurar no arquivo de texto.
    char data_procurada[10];

    //String que receberá strings do aquivo de procura de texto.
    char linha[300];

    //Entrega a string data_procurada a data atual.
    fgets(data_procurada, sizeof(data_procurada), arquivo_datado);

    //Verifica se o arquivo de registro de atividade realmente pode ser aberto.
    if (!arquivo) {
        printf("Desculpe, ouve uma falha ao acessar o arquivo de registro de atividades.");
        return 0;
    } else { 
        
        //Contador do numero de atividades.
        int cont = 0;
        
        //Lê linha a linha do arquivo
        while (fgets(linha,sizeof(linha),arquivo) != NULL)
            //Verifica se uma string existe dentro de outra
            if (strstr(linha,data_procurada) != NULL){
                cont++;
                printf("\nAtividade Prevista %d\n%s", cont, linha);                
            }

        if(cont > 0){
            return 1;
        } else{
            return 0;
        }
    }
    
        
    fclose(arquivo);
    fclose(arquivo_datado);
}

void criaRegistro(){

    //Encapsulamento do arquivo de texto.

        //Ponteiro que acessa o arquivo .txt
        FILE *registro;

        //Abre o arquivo .txt, permitindo escrever texto ao final do que já foi escrito.
        registro = fopen("registro.txt","a");
    
        //Recebe a atividade a ser registrada.
        char frase[300];
        //Recebe o dia do registro.
        int dia_programado;
        //Recebe o mes do registro.
        int mes_programado;
        //Recebe o ano atual.
        int ano_programado;

        printf("Digite em numeros o dia, o mes e ano, da tarefa agendada:\n");

        //Identificador para auxiliar nas respostas de data inseridas pelo usuário;
        int respt = 0;

        //Pede a dia e repete o pedido caso o numero digitado seja maior que 31 ou menor que 1.
        do
        {
            respt = 0;            
            
            printf("Dia: ");
            scanf("%d", &dia_programado);

            if((dia_programado > 31) || (dia_programado < 1))
                respt = 1;

        } while (respt);

        //Pede a mês e repete o pedido caso o numero digitado seja maior que 12 ou menor que 1.
        do
        {
            respt = 0;

            printf("Mes: ");
            scanf("%d", &mes_programado);

            if((mes_programado > 12) || (mes_programado < 1))
                respt = 1;

        } while(respt);
        
        //Pede a dia e repete o pedido caso o numero digitado seja maior que 2022.
        do
        {
            respt = 0;

            printf("Ano: ");
            scanf("%d", &ano_programado);

            if(ano_programado < 2022)
                respt = 1;

        } while(respt);

        printf("Digite a tarefa agendada: ");
        getchar();
        gets(frase);

    //Criando registro no arquivo .txt

        fprintf(registro, "%d/%d/%d - ", dia_programado, mes_programado, ano_programado);
        fprintf(registro, "%s. \n", frase);
    
        fclose(registro);

}

int main(){
    
    //Recebe o nome do usuário.
    char nome[15];

    strcpy(nome, "Igor");

    //Encapsulamento de tempo.

        //Cria um ponteiro para acessar o struct de tempo.
        struct tm *data; 

        //Cria uma variavel que guarda o tempo em segundos.
        time_t segundos; 

        //Obtem o tempo em segundos.
        time(&segundos); 

        //Transforma o que está salvo na variavel time_t em legivel.
        data = localtime(&segundos);
    
    
    //Imprime  a tela de saudação

        printf("----------------------------------------------------------------------------------------\n");

        printf("Ola %s, data de hoje: %d/%d, segue abaixo as atividades registradas para o dia de hoje:\n", nome, data->tm_mday, data->tm_mon+1);

        printf("----------------------------------------------------------------------------------------\n");

    //Verifica a data no sistema e se existe atividade para o dia atual.

        FILE* arquivo_datado;

        arquivo_datado = fopen("data de registro.txt", "w");

        int dia_atual = data->tm_mday;
        int mes_atual = data->tm_mon + 1;
        int ano_atual = data->tm_year + 1900;

        fprintf(arquivo_datado, "%d/%d/%d", dia_atual, mes_atual, ano_atual);
        fclose(arquivo_datado);

    //Se tiver atividade registrada na data em questão, informar.

        if(checaData()){
            
        printf("----------------------------------------------------------------------------------------\n");
            printf("Essas foram todas as atividades programadas.\n");
            printf("----------------------------------------------------------------------------------------\n");
        } else {
            printf("Nao existem atividades programadas para hoje!\n");
            printf("----------------------------------------------------------------------------------------\n");
        }

    //Tela de comandos.

        for(int i=0; i<2 ;i++){

            int resposta_atividade = NULL;
            printf("Se deseja adicionar alguma atividade, tecle 1 + Enter\n");
            printf("----------------------------------------------------------------------------------------\n");
            scanf("%d", &resposta_atividade);

            if(resposta_atividade == 1){
                i = 0;
                printf("----------------------------------------------------------------------------------------\n");
                criaRegistro();
                printf("----------------------------------------------------------------------------------------\n");
            } else{
                i = 2;
            }
        }

    system("pause");
}

/*  
    As atividades devem ser registradas em um arquivo .txt
    O formato de anotação das atividades deve ser:
    
    - Começar com a data da atividade.
    
    - Terminar com quebra de texto. (\n)
*/