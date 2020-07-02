#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "projeto.h"
int max_tarefas_doing=6;
int max_num_t=3;
int max_tarefas(int x){

    int n;
    do{
        printf("Numero maximo de tarefas pretendido: ");
        scanf("%d", &n);
        if (n >= x){
            break;
        }
    }
    while(1);
    return n;
}
int main()
{
    ListaPessoas lista_pessoas;
    ListaTarefas lista_tarefas;
    ListApontador lista_todo;
    ListApontador lista_doing;
    ListApontador lista_done;
    lista_pessoas = cria_lista_pessoas();
    lista_tarefas = cria_lista_tarefas();

    lista_todo = cria_lista_apontadores();
    lista_doing = cria_lista_apontadores();
    lista_done = cria_lista_apontadores();
    carregarPessoas(lista_pessoas);
    carregarTarefas( lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
    menu_inicial_text();
    menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
    return 0;
}

/**********************************PESSOAS*********************************/
ListaPessoas cria_lista_pessoas(){
    ListaPessoas node;
    node = (ListaPessoas) malloc (sizeof (List_nodePessoas));
    if (node != NULL){
        node -> p.nome = NULL;
        node -> p.email = NULL;
        node -> p.id = 0;
        node -> next = NULL;
    }

    return node;
}
void insere_pessoa2(ListaPessoas lista, ListaPessoas novo){
    /*Função para inserir uma pessoa no inicio da lista */
    ListaPessoas aux;
    aux=lista->next;
    if (novo != NULL){
        novo->next=aux;
        lista->next=novo;
    }
}
void imprime_lista_pessoas (ListaPessoas lista) {

    ListaPessoas l = lista->next;  /*Salta o header*/

    while (l) {
        printf("Nome: %s\nEmail: %s\nID: %d\n", l->p.nome, l->p.email, l->p.id);
        l=l->next;
    }
}


ListaPessoas destroi_lista_pessoas(ListaPessoas lista){

    ListaPessoas temp_ptr;
    while (lista -> next != NULL){
        temp_ptr = lista;
        lista = lista -> next;
        free(temp_ptr);
    }

    free(lista);
    return NULL;
}


/**********************************TAREFAS*********************************/
ListaTarefas cria_lista_tarefas(){

    ListaTarefas aux;
    aux = (ListaTarefas) malloc (sizeof(List_nodeTarefas));

    if (aux != NULL){
        aux -> t.id = 0;
        aux -> t.prioridade = 0;
        aux -> t.data_cria.dia = 0;
        aux -> t.data_cria.mes = 0;
        aux -> t.data_cria.ano = 0;
        aux -> t.descricao = NULL;
        aux -> t.prazo_conc.dia = 0;
        aux -> t.prazo_conc.mes = 0;
        aux -> t.prazo_conc.ano = 0;
        aux -> t.data_conc.dia = 0;
        aux -> t.data_conc.mes = 0;
        aux -> t.data_conc.ano = 0;
        aux -> next = NULL;
    }

    return aux;
}


void le_dados_iniciais_tarefa2(Tarefa *t,ListaTarefas lista_tarefas){
    /*Atribui este nome porque as tarefas podem ter mais dados,
     dependendo da fase do pipeline em que se encontram*/
    do{
        printf("ID do cartao: ");
        scanf("%d", &t->id);

        if (verifica_id_cartao(lista_tarefas, t->id) == -1){
            break;
        }
    }while(1);

    do{
        printf("Prioridade: ");
        scanf("%d", &t->prioridade);

        if (t->prioridade > 0 && t->prioridade < 11){
            break;
        }

    } while (1);

    printf("Data de criacao: ");
    scanf("%d/%d/%d", &t->data_cria.dia, &t->data_cria.mes, &t->data_cria.ano);

    printf("Descricao textual: ");
    t->descricao = (char*) malloc (sizeof(char));
    scanf ("%s", t->descricao);
}
void insere_tarefa2(ListaTarefas lista , ListaTarefas novo){
    /*Função para inserir uma tarefa no inicio da lista */
    ListaTarefas aux;
    aux=lista->next;
    if (novo != NULL){
        novo->next=aux;
        lista->next=novo;
    }
}
void cria_tarefa2(ListaTarefas lista, ListApontador ToDo)
{
    ListaTarefas novo;
    ListApontador novaT;
    novo = (ListaTarefas) malloc (sizeof(List_nodeTarefas));
    le_dados_iniciais_tarefa2(&novo->t,lista);
    /*insere_tarefa2(lista,novo);*/
    insere_ord_tarefas(lista,novo);
    /*Criar um nó de apontadores*/
    novaT = (ListApontador) malloc (sizeof(List_apontador));
    novaT->noTarefa=novo;/*Duvida*/
    novaT->next = NULL;
    insere_ToDo(ToDo,novaT);

}

void insere_ToDo(ListApontador lista , ListApontador novo){
    ListApontador ant=lista,act=lista->next;
    novo->noTarefa->t.fase_p=1;
    while(act!=NULL && comparaToDo(*(act->noTarefa),*(novo->noTarefa))>0){
        ant=act;
        act=act->next;
    }
    novo->next=act;
    ant->next=novo;

}
void insere_Doing(ListApontador lista , ListApontador novo){
    ListApontador ant=lista,act=lista->next;
    novo->noTarefa->t.fase_p=2;
    while(act!=NULL && strcmp(act->noTarefa->lista->p.nome,novo->noTarefa->lista->p.nome)<0){
        ant=act;
        act=act->next;
    }
    novo->next=act;
    ant->next=novo;
}
/*Por testar */
void insere_Done(ListApontador lista , ListApontador novo){
    ListApontador ant=lista,act=lista->next;
    Data d;
    novo->noTarefa->t.fase_p=3;
    d=novo->noTarefa->t.data_conc;
    while(act!=NULL && comparaDatas(&act->noTarefa->t.data_conc,&d)==1){
        ant=act;
        act=act->next;
    }
    novo->next=act;
    ant->next=novo;

}

int comparaToDo(List_nodeTarefas n1,List_nodeTarefas n2){
    if (n1.t.prioridade > n2.t.prioridade){
        return 1;/*Se o nó 1 tiver mais prioridade que o nó 2 */
    }
    else if (n1.t.prioridade < n2.t.prioridade)
        return -1;
    /*Se forem iguais , retorna isto */
    return comparaDatas(&(n1.t.data_cria), &(n2.t.data_cria));

}

ListApontador retira(ListApontador lista,int id_cartao){
    ListApontador ant=lista,act=lista->next;
    while(act!=NULL && act->noTarefa->t.id!=id_cartao){
        ant=act;
        act=act->next;
    }
    if(act->noTarefa->t.id==id_cartao){
        ant->next=act->next;
        return act;
    }
    else{
        printf("Elemento não presente na lista\n");
        return NULL;
    }
}
void imprime_lista_tarefas(ListaTarefas lista,ListaPessoas lista_pessoas , ListApontador lista_todo,ListApontador lista_doing,ListApontador lista_done){
    int opcao;
    ListaTarefas l = lista->next;  /*Salta o header*/
    printf("Conteúdo da lista de tarefas !\n");
    while (l) {
        printf("ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\n", l->t.id, l->t.prioridade, l->t.data_cria.dia, l->t.data_cria.mes, l->t.data_cria.ano, l->t.descricao);
        l=l->next;
    }
    printf("\n\n");
    printf("Pretende guardar a consulta efetuada num ficheiro de texto?\n");
    printf("1. Sim\n");
    printf("2. Nao\n");
    printf("\nOpcao pretendida: ");
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            /*Vai chamar a funcao que guarda no ficheiro*/
            guarda_lista_tarefas(lista);
            fflush(stdin);
            break;
        case 2:
            menu_inicial(lista_pessoas, lista, lista_todo, lista_doing, lista_done);
            break;
        default:
            printf("Opcao invalida, tente de novo: ");
            scanf("%d", &opcao);
            break;
    }
    fflush(stdin);
}


ListaTarefas destroi_lista_tarefas(ListaTarefas lista){

    ListaTarefas temp_ptr;
    while (lista -> next != NULL){
        temp_ptr = lista;
        lista = lista -> next;
        free(temp_ptr);
    }

    free(lista);
    return NULL;
}

/*******************************OPERACOES COM COLUNAS**************************************************/

void imprime_lista_todo(ListApontador lista){
    ListApontador l = lista->next;

    while (l) {
        printf("ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\n", l->noTarefa->t.id,l->noTarefa->t.prioridade,
               l->noTarefa->t.data_cria.dia,l->noTarefa->t.data_cria.mes,l->noTarefa->t.data_cria.ano,l->noTarefa->t.descricao);
        l=l->next;
    }
}
void imprime_lista_doing(ListApontador lista){
    ListApontador l = lista->next;

    while (l) {
        printf("ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\nResponsável: %s\nPrazo Conclusão: %d/%d/%d \n", l->noTarefa->t.id,l->noTarefa->t.prioridade,
               l->noTarefa->t.data_cria.dia,l->noTarefa->t.data_cria.mes,l->noTarefa->t.data_cria.ano,l->noTarefa->t.descricao,l->noTarefa->lista->p.nome,l->noTarefa->t.prazo_conc.dia,l->noTarefa->t.prazo_conc.mes,l->noTarefa->t.prazo_conc.ano);
        l=l->next;
    }
}
void imprime_lista_done(ListApontador lista){
    ListApontador l = lista->next;

    while (l) {
        printf("ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\nResponsável: %s\nPrazo Conclusão: %d/%d/%d\nData Conclusão: %d/%d/%d\n", l->noTarefa->t.id,l->noTarefa->t.prioridade,
               l->noTarefa->t.data_cria.dia,l->noTarefa->t.data_cria.mes,l->noTarefa->t.data_cria.ano,l->noTarefa->t.descricao,l->noTarefa->lista->p.nome,l->noTarefa->t.prazo_conc.dia,l->noTarefa->t.prazo_conc.mes,l->noTarefa->t.prazo_conc.ano,l->noTarefa->t.data_conc.dia,l->noTarefa->t.data_conc.mes,l->noTarefa->t.data_conc.ano);
        l=l->next;
    }
}
/*Fazer mais funções para imprimir*/

void visualiza_tabela(ListaPessoas lista_pessoas ,ListaTarefas lista_tarefas ,ListApontador lista_todo, ListApontador lista_doing, ListApontador lista_done){
    int opcao;
    printf("---------------------------To Do---------------------------\n");
    imprime_lista_todo( lista_todo);
    printf("---------------------------Doing---------------------------\n");
    imprime_lista_doing( lista_doing);
    printf("---------------------------Done----------------------------\n");
    imprime_lista_done( lista_done);


    printf("\n\n");
    printf("Pretende guardar a consulta efetuada num ficheiro de texto?\n");
    printf("1. Sim\n");
    printf("2. Nao\n");
    printf("\nOpcao pretendida: ");
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            /*Vai chamar a funcao que guarda no ficheiro*/
            guarda_quadro(lista_todo, lista_doing, lista_done);
            break;
        case 2:
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        default:
            printf("Opcao invalida, tente de novo: ");
            scanf("%d", &opcao);
            break;
    }
    fflush(stdin);
}



void menu_inicial_text(){

    printf("1. Listar pessoas\n");
    printf("2. Definir numero maximo de tarefas\n");
    printf("3. Inserir nova tarefa [Coluna To Do]\n");
    printf("4. Visualizar o quadro\n");
    printf("5. Visualizar o quadro de uma pessoa\n");
    printf("6. Visualizar todas as tarefas criadas [Por data de criacao]\n");
    printf("7. Mover cartoes [To Do para Doing e vice-versa]\n");
    printf("8. Alterar pessoa responsavel por um cartao [Coluna Doing]\n");
    printf("9. Terminar cartao [Envia para Done]\n");
    printf("10. Reabrir cartao [Envia de Done para To Do]\n");
    printf("11. Alterar a prioridade de uma tarefa em To Do\n");
    printf("12. Sair\n");
}

void menu_inicial(ListaPessoas lista_pessoas, ListaTarefas lista_tarefas,
                  ListApontador lista_todo, ListApontador lista_doing, ListApontador lista_done){

    int opcao,opcao7,id_responsavel1,id_responsavel2;

    ListaPessoas l;
    printf("\nOperacao pretendida: ");
    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            imprime_lista_pessoas(lista_pessoas);
            /*imprime_lista_tarefas(lista_tarefas);*/
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;

        case 2:
            max_num_t = 0;
            l = lista_pessoas->next;
            while (l) {
                if (l->p.num_t > max_num_t)
                    max_num_t = l->p.num_t;
                l=l->next;
            }
            max_num_t = max_tarefas(max_num_t);/* não deixar baixar para o menos do maximo presente em todas as pessoas */
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;

        case 3:
            cria_tarefa2(lista_tarefas,lista_todo);
            /*imprime_lista_tarefas(lista_tarefas);*//*Para teste*/
            /*insere_tarefa_todo(lista_todo, &t);*/
            /*Inserir na lista ToDo */
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 4:
            visualiza_tabela( lista_pessoas , lista_tarefas , lista_todo,  lista_doing,  lista_done);
            numTarefasDoing(lista_doing);
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 5:
            worker5( lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 6:/*Visualizar todas as tarefas criadas [Por data de criacao]*/
            imprime_lista_tarefas( lista_tarefas, lista_pessoas ,  lista_todo, lista_doing, lista_done);
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 7:/*é preciso indicar a data de conclusao */
            printf("\n\n");
            printf("1. ToDo----->Doing\n");
            printf("2. Doing----->ToDo\n");
            printf("3. Voltar\n");
            printf("\nOperacao pretendida: ");
            do{
                scanf("%d", &opcao7);
                if(opcao7 > 0 && opcao7 < 4){
                    break;
                }
            }while(1);
            if(opcao7 == 1){
                if(numTarefasDoing(lista_doing)<max_tarefas_doing){
                    ToDoparaDoing(lista_pessoas ,lista_tarefas,lista_todo,lista_doing,lista_done,max_num_t);
                }
                else{
                    printf("A coluna doing encontra-se cheia!\n");
                    menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
                }
            }
            else if(opcao7 == 2){
                DoingparaToDo(lista_pessoas ,lista_todo,lista_doing);
            }
            else if(opcao7 == 3){
                menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            }
            /*teste7(lista_todo);*/
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 8:
            printf("Lista de cartões na fase 'Doing' \n");
            imprime_lista_doing(lista_doing);
            printf("Qual é o id do cartão do qual quer alterar o responsavel?: ");
            scanf("%d",&id_responsavel1);
            imprime_lista_pessoas_vagas(lista_pessoas,max_num_t);/*Só imprimir aqueles que podem ser responsaveis*//*Só imprimir aqueles que têm vagas */
            printf("Qual é o id do novo responsável?: ");
            scanf("%d",&id_responsavel2);
            alterar_responsavel(lista_pessoas,lista_doing,id_responsavel1,id_responsavel2);
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 9:
            DoingparaDone( lista_pessoas , lista_doing,lista_done);
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 10:
            ReabreCartao( lista_done, lista_todo);
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 11:
            altera_prioridade( lista_pessoas, lista_tarefas ,  lista_todo ,  lista_doing ,lista_done);
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        case 12:
            printf("A guardar ficheiros de texto...\n");
            guardarTarefas( lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            lista_pessoas = destroi_lista_pessoas(lista_pessoas);
            lista_tarefas = destroi_lista_tarefas(lista_tarefas);
            lista_todo = destroi_lista_apontadores(lista_todo);
            lista_doing = destroi_lista_apontadores(lista_doing);
            lista_done = destroi_lista_apontadores(lista_done);
            printf("Listas destruídas!!!!!! \n");
            printf("Programa terminado com sucesso\n");
            exit(0);

        default:
            printf("Input invalida, tente de novo\n");
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
    }
}
void alterar_responsavel(ListaPessoas lista_pessoas , ListApontador lista_doing , int id_cartao,int id_responsavel2){
    /*Tenho de encontrar o responsavel pelo cartao*/
    ListaPessoas novo;
    ListApontador ant=lista_doing,act=lista_doing->next;
    while(act!=NULL && act->noTarefa->t.id!=id_cartao){
        ant=act;
        act=act->next;
    }
    if(act->noTarefa->t.id==id_cartao){/*Se encontrarmos a tarefa na lista de ponteiros*/
        printf("O responsável vai ser substituido pelo funcionário com o id  %d ",id_responsavel2);
        novo=procuraPessoaID(lista_pessoas ,id_responsavel2);
        act->noTarefa->lista=novo;
    }
    else{
        printf("Elemento não presente na lista\n");
    }
}
ListApontador cria_lista_apontadores(void){/*Pode estar mal a inicialização da tarefa , confirmar */
    ListApontador head;
    head = (ListApontador)malloc (sizeof (List_apontador));
    if (head != NULL) {
        head->noTarefa=NULL;
        head->next = NULL;
    }
    return head;
}

/* não é preciso funções de criar/apagar/alterar pessoas */
/*Função para ler pessoas do ficheiro de texto e carregá-las para a Lista */

/****** Funções para ordenar a lista de tarefas por data de criação */
int comparaDatas(Data *d1 , Data *d2){
    if ((d1->ano==d2->ano) && (d1->mes==d2->mes) && (d1->dia==d2->dia))
        return 0;
    else if (d1->ano<d2->ano)/*se a primeira for anterior à segunda */
        return -1;
    else if ((d1->ano==d2->ano)&&((d1->mes<d2->mes)))
        return -1;
    else if ((d1->ano==d2->ano)&&((d1->mes==d2->mes))&&(d1->dia<d2->dia))
        return -1;
    else
        return 1;
}

void escreveData(Data *data){
    printf("Ano: %d \n",data->ano);
    printf("Mes: %d \n",data->mes);
    printf("Dia: %d \n",data->dia);
}

void insere_ord_tarefas(ListaTarefas lista , ListaTarefas novo){
    ListaTarefas ant=lista,act=lista->next;
    Data d;
    d=novo->t.data_cria;
    while(act!=NULL && comparaDatas(&act->t.data_cria,&d)==1){
        ant=act;
        act=act->next;
    }
    novo->next=act;
    ant->next=novo;
}

void teste7(ListApontador lista){
    int id_cartao;
    printf("Conteúdo da lista ToDo\n");
    printf("Qual é o id do cartão que quer remover?\n");
    imprime_lista_todo(lista);
    scanf("Id pretendido : %d",&id_cartao);
    retira(lista,id_cartao);
}
void DoingparaToDo(ListaPessoas lista_pessoas ,ListApontador lista_todo,ListApontador lista_doing){
    /*Falta fazer verificações */
    ListApontador no;
    int id_cartao;
    printf("Conteúdo da lista Doing\n");
    imprime_lista_todo(lista_doing);
    printf("Qual é o id do cartão que quer colocar em 'To Do'?:");
    scanf("%d",&id_cartao);
    no=retira(lista_doing,id_cartao);
    no->noTarefa->lista=NULL;
    insere_ToDo(lista_todo,no);
}
void ToDoparaDoing(ListaPessoas lista_pessoas ,ListaTarefas lista_tarefas, ListApontador lista_todo,ListApontador lista_doing,ListApontador lista_done,int max_num_t){
    /*Falta fazer verificações */
    ListApontador no,aux;
    ListaPessoas responsavel;
    Data prazo;
    int id_cartao,id_pessoa;
    printf("Conteúdo da lista ToDo\n");
    imprime_lista_todo(lista_todo);
    printf("Qual é o id do cartão que quer colocar em 'Doing'?:");
    scanf("%d",&id_cartao);
    aux=devolveApontador_ID(lista_todo,id_cartao);
    do{
        printf("Qual é o prazo de conclusão?:");
        scanf("%d/%d/%d",&prazo.dia,&prazo.mes,&prazo.ano);
        if(comparaDatas(&prazo,&aux->noTarefa->t.data_cria)==1){
            break;
        }
    }while(1);
    imprime_lista_pessoas_vagas(lista_pessoas,max_num_t);
    do{
        printf("Qual é o id da pessoa responsável?:");
        scanf("%d",&id_pessoa);
        if (verifica_id(lista_pessoas, id_pessoa) == -1 && verifica_prazos(lista_pessoas,lista_doing , id_pessoa,&prazo)==0){
            break;
        }
    }while(1);
    no=retira(lista_todo,id_cartao);/*Retira da toDo*/
    no->noTarefa->t.prazo_conc=prazo;


    responsavel = procuraPessoaID(lista_pessoas , id_pessoa);
    if(responsavel->p.num_t>=max_num_t){
        printf("Esta pessoa não pode ter mais tarefas !\n");
        menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
    }
    responsavel->p.num_t++; /*Incremento o num de tarefas da pessoa*/
    printf("Elemento com o id %d vai ser retirado da lista ToDo!\n",id_pessoa);
    no->noTarefa->lista=responsavel;
    insere_Doing(lista_doing,no);
}
void DoingparaDone(ListaPessoas lista_pessoas , ListApontador lista_doing,ListApontador lista_done){
    int id_cartao;
    Data conclusao;
    ListApontador no,aux;
    /*Listar as tarefas em Doing */
    printf("Conteúdo da lista Doing\n");
    imprime_lista_doing(lista_doing);
    printf("Qual é o id do cartao que quer concluir?:");
    scanf("%d",&id_cartao);
    aux=devolveApontador_ID(lista_doing,id_cartao);
    do{
        printf("Qual é a data de conclusão?:");
        scanf("%d/%d/%d",&conclusao.dia,&conclusao.mes,&conclusao.ano);
        if(comparaDatas(&aux->noTarefa->t.prazo_conc,&conclusao )==1){
            printf("Tarefa concluída com sucesso dentro do tempo!\n");
            break;
        }
        else if(comparaDatas(&aux->noTarefa->t.prazo_conc,&conclusao )==-1){
            printf("Tarefa concluída fora do prazo!\n");
            break;
        }
    }while(1);
    no=retira(lista_doing,id_cartao);
    no->noTarefa->t.data_conc=conclusao;
    no->noTarefa->lista->p.num_t--; /*Decrementa o num de tarefas da pessoa*/
    insere_Done(lista_done, no);
}
ListaPessoas procuraPessoaID(ListaPessoas lista , int id_pessoa){
    ListaPessoas ant=lista,act=lista->next;
    while(act!=NULL && act->p.id!=id_pessoa){
        ant=act;
        act=act->next;
    }
    if(act->p.id==id_pessoa){
        return act;
    }
    else{
        printf("Elemento não presente na lista\n");
        return NULL;
    }

}

void worker5(ListaPessoas lista_pessoas,ListaTarefas lista_tarefas,ListApontador lista_todo,ListApontador lista_doing,ListApontador lista_done){
    int id_pessoa;
    int opcao;
    listarPessoascomID(lista_pessoas);
    printf("ID pretendido:");
    scanf("%d",&id_pessoa);
    imprimeQuadroPessoa(lista_pessoas,lista_doing,lista_done,id_pessoa);
    printf("\n\n");
    printf("Pretende guardar, num ficheiro de texto, a consulta efetuada?\n");
    printf("1. Sim\n");
    printf("2. Nao\n");
    printf("\nOpcao pretendida: ");
    scanf("%d", &opcao);

    switch(opcao){
        case 1:
            guarda_quadro_pessoa(lista_doing, lista_done, id_pessoa);
            break;
        case 2:
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
            break;
        default:
            printf("Opcao invalida, tente de novo: ");
            scanf("%d", &opcao);
            break;
    }

    fflush(stdin);
}
void listarPessoascomID(ListaPessoas lista){
    ListaPessoas l = lista->next;  /*Salta o header*/
    printf("Pessoas no sistema e respectivos IDs !\n");
    while (l) {
        printf("ID:%d\nNome:%s\n",l->p.id,l->p.nome);
        l=l->next;
    }
}

void imprimeQuadroPessoa(ListaPessoas lista_pessoas,ListApontador lista_doing ,ListApontador lista_done , int id_pessoas){
    /*Tem de imprimir o Doing e o Done */
    /*Doing*/
    ListApontador ant1=lista_doing,act1=lista_doing->next;
    ListApontador ant2=lista_done,act2=lista_done->next;
    printf("----------Tarefas na fase Doing do funcionário com o id %d ----------\n",id_pessoas);
    while(act1!=NULL){
        if(act1->noTarefa->lista->p.id==id_pessoas){
            /*Função para imprimir Doing */
            imprimeDoing(act1);
        }
        ant1=act1;
        act1=act1->next;
    }
    printf("----------Tarefas na fase Done do funcionário com o id %d ----------\n",id_pessoas);
    while(act2!=NULL){
        if(act2->noTarefa->lista->p.id==id_pessoas){
            imprimeDone(act2);
        }
        ant2=act2;
        act2=act2->next;
    }
}
void imprimeDoing(ListApontador no){
    printf("ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\nIDResponsável: %d\n Responsável: %s\nPrazo Conclusão: %d/%d/%d \n",
           no->noTarefa->t.id,no->noTarefa->t.prioridade,no->noTarefa->t.data_cria.dia,no->noTarefa->t.data_cria.mes,
           no->noTarefa->t.data_cria.ano,no->noTarefa->t.descricao,no->noTarefa->lista->p.id,no->noTarefa->lista->p.nome,no->noTarefa->t.prazo_conc.dia,no->noTarefa->t.prazo_conc.mes,no->noTarefa->t.prazo_conc.ano);
}
void imprimeDone(ListApontador no){
    printf("ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\nIDResponsável: %d\n Responsável: %s\nPrazo Conclusão: %d/%d/%d\nData Conclusão: %d/%d/%d\n", no->noTarefa->t.id
           ,no->noTarefa->t.prioridade,
           no->noTarefa->t.data_cria.dia,no->noTarefa->t.data_cria.mes,no->noTarefa->t.data_cria.ano
           ,no->noTarefa->t.descricao,no->noTarefa->lista->p.id
           ,no->noTarefa->lista->p.nome,
           no->noTarefa->t.prazo_conc.dia,no->noTarefa->t.prazo_conc.mes,no->noTarefa->t.prazo_conc.ano
           ,no->noTarefa->t.data_conc.dia,no->noTarefa->t.data_conc.mes,no->noTarefa->t.data_conc.ano);
}
void ReabreCartao(ListApontador lista_done, ListApontador lista_todo){

    ListApontador no;
    int id_cartao;
    Data prazo_reset, dataconc_reset;
    prazo_reset.dia = 0;
    prazo_reset.mes = 0;
    prazo_reset.ano = 0;
    dataconc_reset.dia = 0;
    dataconc_reset.mes = 0;
    dataconc_reset.ano = 0;



    printf("-------------Conteúdo da lista Done--------------\n");
    imprime_lista_done(lista_done);

    printf("Qual é o id do cartão que quer colocar em 'Done'?:");
    scanf("%d",&id_cartao);

    no=retira(lista_done,id_cartao);

    no->noTarefa->t.prazo_conc = prazo_reset;
    no->noTarefa->t.data_conc = dataconc_reset;
    no->noTarefa->lista = NULL; /*Retira o responsavel pelo cartao*/

    insere_ToDo(lista_todo, no);
}

int numTarefasDoing(ListApontador lista_doing){
    ListApontador ant=lista_doing,act=lista_doing->next;
    int contador=0;
    while(act!=NULL){
        ant=act;
        act=act->next;
        contador++;
    }
    return contador;
}

int verifica_id(ListaPessoas lista_pessoas, int id_pessoa){
    ListaPessoas l = lista_pessoas->next;
    while (l) {
        if (id_pessoa == l->p.id){
            printf("Id encontrado\n");
            return -1;
        }
        l=l->next;
    }
    printf("Id inexistente, tente de novo\n");
    return -2;
}

void altera_prioridade(ListaPessoas lista_pessoas,ListaTarefas lista_tarefas , ListApontador lista_todo , ListApontador lista_doing , ListApontador lista_done){
    ListApontador tarefa;
    int id_cartao,nova_prioridade;
    /*Imprimir lista To Do*/
    imprime_lista_todo(lista_todo);
    /*Escolher ID do cartão a alterar prioridade*/
    printf("Escolha o ID do cartão do qual quer alterar a prioridade: ");
    scanf("%d",&id_cartao);
    if(verifica_id_todo(lista_todo, id_cartao)==1){
        printf("Escolha a nova prioridade: ");
        scanf("%d",&nova_prioridade);
        if(nova_prioridade > 10 || nova_prioridade <1)
            menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
        tarefa =retira( lista_todo,id_cartao);
        tarefa->noTarefa->t.prioridade=nova_prioridade;
        /*Voltar a inserir na lista To Do*/
        insere_ToDo(lista_todo, tarefa);
    }
    else{
        printf("Este cartão não se encontra na Lista To Do!\n");
        menu_inicial(lista_pessoas, lista_tarefas, lista_todo, lista_doing, lista_done);
    }

}

int verifica_id_todo(ListApontador lista_todo,int id_cartao){
    ListApontador l = lista_todo->next;
    while (l) {
        if (id_cartao == l->noTarefa->t.id){
            return 1;
        }
        l=l->next;
    }
    return 0;
}

ListApontador devolveApontador_ID(ListApontador lista,int id_cartao){
    ListApontador ant=lista,act=lista->next;
    while(act!=NULL && act->noTarefa->t.id!=id_cartao){
        ant=act;
        act=act->next;
    }
    /*Ele vai encontrar portanto pode ser assim*/
    return act;
}
void imprime_lista_pessoas_vagas(ListaPessoas lista_pessoas,int num_max){
    ListaPessoas ant=lista_pessoas,act=lista_pessoas->next;
    printf("Pessoas disponiveis\n");
    while(act!=NULL){
        if(act->p.num_t<num_max){
            printf("ID: %d\nNome: %s\n",act->p.id,act->p.nome);
        }
        ant=act;
        act=act->next;
    }
}

ListApontador destroi_lista_apontadores(ListApontador lista){
    ListApontador temp_ptr;
    while (lista -> next != NULL){
        temp_ptr = lista;
        lista = lista -> next;
        free(temp_ptr);
    }
    free(lista);
    return NULL;
}
Data diferenca(Data *d1 , Data *d2){
    Data resultado;
    if (comparaDatas(d1,d2)==0){
        resultado.ano=0;resultado.mes=0;resultado.dia=0;
    }
    else if (comparaDatas(d1,d2)==-1){/*se a primeira for anterior à segunda */
        resultado.ano=d2->ano-d1->ano;
        resultado.mes=d2->mes-d1->mes;
        resultado.dia=d2->dia-d1->dia;
    }
    else{
        resultado.ano=d1->ano-d2->ano;
        resultado.mes=d1->mes-d2->mes;
        resultado.dia=d1->dia-d2->dia;
    }
    return resultado;
}

Data soma7dias(Data *d1){
    Data dfinal;
    if(d1->mes==12){/*Se for dezembro*/
        if(d1->dia>24){
            /*Passa para o próximo ano*/
            dfinal.ano=d1->ano++;
            dfinal.mes=1;
            dfinal.dia=d1->dia-24;
        }
        else{
            dfinal.ano=d1->ano;
            dfinal.mes=12;
            dfinal.dia=dfinal.dia+7;
        }
    }
    else if(d1->mes==2){/*Se for Fevereiro*/
        if(d1->dia>21){
            /*Passa para o próximo mês*/
            dfinal.ano=d1->ano;
            dfinal.mes=1;
            dfinal.dia=d1->dia-21;
        }
        else{
            dfinal.ano=d1->ano;
            dfinal.mes=2;
            dfinal.dia=dfinal.dia+7;
        }
    }
    else if(d1->mes==1 || d1->mes==3 || d1->mes==5 || d1->mes==7 || d1->mes==8|| d1->mes==10){/*Se tiverem 31 dias*/
        if(d1->dia>24){
            dfinal.ano=d1->ano;
            dfinal.mes=d1->mes++;
            dfinal.dia=d1->dia-24;
        }
        else{
            dfinal.ano=d1->ano;
            dfinal.mes=d1->mes;
            dfinal.dia=dfinal.dia+7;
        }
    }
    else {/*Se tiverem 30 dias*/
        if(d1->dia>23){
            dfinal.ano=d1->ano;
            dfinal.mes=d1->mes++;
            dfinal.dia=d1->dia-23;
        }
        else{
            dfinal.ano=d1->ano;
            dfinal.mes=d1->mes;
            dfinal.dia=dfinal.dia+7;
        }
    }
    return dfinal;
}
int semana(Data *d1 , Data *d2){
    /*Se pegarmos na data e somarmos 7 e for maior que o prazo então não pode ser */
    Data soma;
    soma=soma7dias(d1);
    if (comparaDatas(&soma,d2)==-1)
        return 1;
    else
        return 0;
}

int verifica_prazos(ListaPessoas lista,ListApontador lista_doing ,int id_pessoa,Data *nova){
    ListApontador ant=lista_doing,act=lista_doing->next;
    while(act!=NULL){
        if(act->noTarefa->lista->p.id==id_pessoa){
            if(numSemanas(nova)==numSemanas(&act->noTarefa->t.prazo_conc))
                return 1;
        }
        ant=act;
        act=act->next;
    }
    return 0;
}
void carregarPessoas(ListaPessoas lista_pessoas){
    FILE *f;
    int id;
    char *nome;
    char *email;
    /*Pessoa pessoa;*/
    ListaPessoas novo;
    f=fopen("Pessoas.txt","r");
    if(f==NULL){
        printf("Falha ao ler do ficheiro Pessoas.txt!\n");
    }
    else{
        printf("Ficheiro carregado com sucesso!\n");
    }
    nome=(char*)malloc(sizeof(char)*30);
    email=(char*)malloc(sizeof(char)*30);
    while (fscanf (f, "%d\t%s\t%[^\n]s",&id,email,nome) != EOF){
        /*Guardar diretamente na lista de pessoas*/
        novo=(ListaPessoas)malloc(sizeof(List_nodePessoas));
        novo->p.email=(char*)malloc(sizeof(char)*50);
        novo->p.nome=(char*)malloc(sizeof(char)*50);
        novo->next=NULL;
        novo->p.id=id;
        novo->p.num_t = 0;/*Talvez alterar*/
        strcpy(novo->p.email,email);
        strcpy(novo->p.nome,nome);
        insere_pessoa2(lista_pessoas,novo);
    }
    fclose(f);
    printf("Ficheiro fechado com sucesso!\n");
}
void carregarTarefas(ListaPessoas lista_pessoas,ListaTarefas lista_tarefas,ListApontador lista_todo,ListApontador lista_doing,ListApontador lista_done){
    FILE *f;
    int fase = 0;
    int id_cartao;
    int id_responsavel;
    int prioridade;
    char *descricao;
    Data data_cria;
    Data prazo;
    Data conclusao;
    ListApontador novo;
    ListaTarefas nova;
    ListaPessoas responsavel;
    descricao=(char*)malloc(sizeof(char)*50);
    f=fopen("Tarefas.txt","r");
    while(fase!=-1){/*por cena estranha*/
        fscanf(f,"%d\n",&fase);
        novo=(ListApontador)malloc(sizeof(List_apontador));
        nova=(ListaTarefas)malloc(sizeof(List_nodeTarefas));
        if(fase==1){
            fscanf(f,"%d\t%d/%d/%d\t%d\t%[^\n]s",&id_cartao,&data_cria.dia,&data_cria.mes,&data_cria.ano,&prioridade,descricao);
            /*Adicionar às listas*/
            /*printf("%d\t%d/%d/%d\t%d\t%s\n",id_cartao,data_cria.dia,data_cria.mes,data_cria.ano,prioridade,descricao);*/
            nova->t.id=id_cartao;
            nova->t.data_cria=data_cria;
            nova->t.prioridade=prioridade;
            nova->t.descricao=(char*)malloc(sizeof(char)*50);
            strcpy(nova->t.descricao,descricao);
            insere_ord_tarefas(lista_tarefas, nova);
            /*Inserir na ToDo*/
            novo->noTarefa=nova;
            insere_ToDo(lista_todo,novo);
        }
        if(fase==2){
            fscanf(f, "%d\t%d/%d/%d\t%d\t%d\t%d/%d/%d\t%[^\n]s",&id_cartao,&data_cria.dia,&data_cria.mes,&data_cria.ano,&prioridade,
                   &id_responsavel, &prazo.dia, &prazo.mes, &prazo.ano, descricao);
            nova->t.id=id_cartao;
            nova->t.data_cria=data_cria;
            /*Responsavel*/
            responsavel=(ListaPessoas)malloc(sizeof(List_nodePessoas));
            responsavel=procuraPessoaID(lista_pessoas , id_responsavel);
            nova->t.prioridade=prioridade;
            nova->t.prazo_conc=prazo;
            nova->t.descricao=(char*)malloc(sizeof(char)*50);
            strcpy(nova->t.descricao,descricao);
            insere_ord_tarefas(lista_tarefas, nova);
            /*Inserir na ToDo*/
            novo->noTarefa=nova;
            novo->noTarefa->lista=responsavel;
            insere_Doing(lista_doing,novo);
        }
        if(fase==3){
            fscanf(f, "%d\t%d/%d/%d\t%d\t%d\t%d/%d/%d\t%d/%d/%d\t%[^\n]s",&id_cartao,&data_cria.dia,&data_cria.mes,&data_cria.ano,&prioridade,
                   &id_responsavel, &prazo.dia, &prazo.mes, &prazo.ano, &conclusao.dia, &conclusao.mes, &conclusao.ano, descricao);
            nova->t.id=id_cartao;
            nova->t.data_cria=data_cria;
            nova->t.data_conc=conclusao;
            responsavel=(ListaPessoas)malloc(sizeof(List_nodePessoas));
            responsavel=procuraPessoaID(lista_pessoas , id_responsavel);
            nova->t.prioridade=prioridade;
            nova->t.prazo_conc=prazo;
            nova->t.descricao=(char*)malloc(sizeof(char)*50);
            strcpy(nova->t.descricao,descricao);
            insere_ord_tarefas(lista_tarefas, nova);
            /*Inserir na ToDo*/
            novo->noTarefa=nova;
            novo->noTarefa->lista=responsavel;
            insere_Done(lista_done,novo);
        }
    }
    fclose(f);
}
void guardarTarefas(ListaPessoas lista_pessoas,ListaTarefas lista_tarefas,ListApontador lista_todo,ListApontador lista_doing,ListApontador lista_done){
    FILE *f;
    f=fopen("Tarefas.txt","w");
    imprimeToDoFicheiros(f,  lista_todo);
    imprimeDoingFicheiros(f , lista_doing);
    imprimeDoneFicheiros(f ,  lista_done);
    fprintf(f,"-1\n");
    fclose(f);

}

void imprimeToDoFicheiros(FILE *f , ListApontador lista_todo){
    ListApontador ant=lista_todo,act=lista_todo->next;
    while(act!=NULL){
        fprintf(f,"1\n");
        fprintf(f,"%d\t%d/%d/%d\t%d\t%s\n",act->noTarefa->t.id,act->noTarefa->t.data_cria.dia,act->noTarefa->t.data_cria.mes,act->noTarefa->t.data_cria.ano,act->noTarefa->t.prioridade,act->noTarefa->t.descricao);
        ant=act;
        act=act->next;
    }
}
void imprimeDoingFicheiros(FILE *f , ListApontador lista_doing){
    ListApontador ant=lista_doing,act=lista_doing->next;
    while(act!=NULL){
        fprintf(f,"2\n");
        fprintf(f,"%d\t%d/%d/%d\t%d\t%d\t%d/%d/%d\t%s\n",act->noTarefa->t.id,act->noTarefa->t.data_cria.dia,act->noTarefa->t.data_cria.mes,act->noTarefa->t.data_cria.ano,act->noTarefa->t.prioridade,act->noTarefa->lista->p.id,act->noTarefa->t.prazo_conc.dia,act->noTarefa->t.prazo_conc.mes,act->noTarefa->t.prazo_conc.ano,act->noTarefa->t.descricao);
        ant=act;
        act=act->next;
    }
}
void imprimeDoneFicheiros(FILE *f , ListApontador lista_done){
    ListApontador ant=lista_done,act=lista_done->next;
    while(act!=NULL){
        fprintf(f,"3\n");
        fprintf(f,"%d\t%d/%d/%d\t%d\t%d\t%d/%d/%d\t%d/%d/%d\t%s\n",act->noTarefa->t.id,act->noTarefa->t.data_cria.dia,act->noTarefa->t.data_cria.mes,act->noTarefa->t.data_cria.ano,act->noTarefa->t.prioridade,act->noTarefa->lista->p.id,act->noTarefa->t.prazo_conc.dia,act->noTarefa->t.prazo_conc.mes,act->noTarefa->t.prazo_conc.ano,act->noTarefa->t.data_conc.dia,act->noTarefa->t.data_conc.mes,act->noTarefa->t.data_conc.ano,act->noTarefa->t.descricao);
        ant=act;
        act=act->next;
    }
}
int verifica_id_cartao(ListaTarefas lista_tarefas, int id_cartao){
    ListaTarefas l = lista_tarefas->next;
    while(l) {
        if(id_cartao == l->t.id){
            printf("Id ja existente, tente de novo\n");
            return -2;
        }
        l = l->next;
    }

    printf("Id disponivel\n");
    return -1;
}


void guarda_quadro(ListApontador lista_todo, ListApontador lista_doing, ListApontador lista_done){

    FILE *fp;
    char nomef[30];
    ListApontador l1, l2, l3;
    printf("Nome do ficheiro[sem espacos]: "); /*Alterar se necessario*/
    scanf("%s", nomef);
    fp = fopen(nomef, "a");

    fprintf(fp, "---------------------------To Do---------------------------\n");
    l1 = lista_todo->next;
    while (l1) {
        fprintf(fp, "ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\n", l1->noTarefa->t.id,l1->noTarefa->t.prioridade,
                l1->noTarefa->t.data_cria.dia,l1->noTarefa->t.data_cria.mes,l1->noTarefa->t.data_cria.ano,l1->noTarefa->t.descricao);
        l1=l1->next;
    }

    fprintf(fp, "---------------------------Doing---------------------------\n");
    l2 = lista_doing->next;
    while (l2) {
        fprintf(fp, "ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\nResponsável: %s\nPrazo Conclusão: %d/%d/%d \n", l2->noTarefa->t.id,l2->noTarefa->t.prioridade,
                l2->noTarefa->t.data_cria.dia,l2->noTarefa->t.data_cria.mes,l2->noTarefa->t.data_cria.ano,l2->noTarefa->t.descricao,l2->noTarefa->lista->p.nome,
                l2->noTarefa->t.prazo_conc.dia,l2->noTarefa->t.prazo_conc.mes,l2->noTarefa->t.prazo_conc.ano);
        l2=l2->next;
    }

    fprintf(fp, "---------------------------Done----------------------------\n");
    l3 = lista_done->next;
    while (l3) {
        fprintf(fp, "ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\nResponsável: %s\nPrazo Conclusão: %d/%d/%d\nData Conclusão: %d/%d/%d\n", l3->noTarefa->t.id,
                l3->noTarefa->t.prioridade,l3->noTarefa->t.data_cria.dia,l3->noTarefa->t.data_cria.mes,l3->noTarefa->t.data_cria.ano,l3->noTarefa->t.descricao,l3->noTarefa->lista->p.nome,
                l3->noTarefa->t.prazo_conc.dia,l3->noTarefa->t.prazo_conc.mes,l3->noTarefa->t.prazo_conc.ano,l3->noTarefa->t.data_conc.dia,l3->noTarefa->t.data_conc.mes,l3->noTarefa->t.data_conc.ano);
        l3=l3->next;
    }

    fclose(fp);
}


void guarda_quadro_pessoa(ListApontador lista_doing, ListApontador lista_done, int id_pessoas){

    FILE *fp;
    char nomef[30];
    ListApontador ant1, act1, ant2, act2;
    printf("Nome do ficheiro[sem espacos]: "); /*Alterar se necessario*/
    scanf("%s", nomef);
    fp = fopen(nomef, "a");

    /*Tem de imprimir o Doing e o Done */
    /*Doing*/
    ant1=lista_doing;
    act1=lista_doing->next;
    ant2=lista_done;
    act2=lista_done->next;
    while(act1!=NULL){
        if(act1->noTarefa->lista->p.id==id_pessoas){
            fprintf(fp, "------------------DOING da pessoa com id %d------------------\n", id_pessoas);
            guardaDoing(act1, fp);    /*Função para imprimir Doing */
        }
        ant1=act1;
        act1=act1->next;
    }
    while(act2!=NULL){
        if(act2->noTarefa->lista->p.id==id_pessoas){
            fprintf(fp, "------------------DONE da pessoa com id %d------------------\n", id_pessoas);
            guardaDone(act2, fp);
        }
        ant2=act2;
        act2=act2->next;
    }
    fclose(fp);
}



void guardaDoing(ListApontador no, FILE *fp){
    fprintf(fp, "ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\nID Responsável: %d\n Responsável: %s\nPrazo Conclusão: %d/%d/%d \n",
            no->noTarefa->t.id,no->noTarefa->t.prioridade,no->noTarefa->t.data_cria.dia,no->noTarefa->t.data_cria.mes,
            no->noTarefa->t.data_cria.ano,no->noTarefa->t.descricao,no->noTarefa->lista->p.id,no->noTarefa->lista->p.nome,no->noTarefa->t.prazo_conc.dia,no->noTarefa->t.prazo_conc.mes,no->noTarefa->t.prazo_conc.ano);
}
void guardaDone(ListApontador no, FILE *fp){
    fprintf(fp, "ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\nID Responsável: %d\n Responsável: %s\nPrazo Conclusão: %d/%d/%d\nData Conclusão: %d/%d/%d\n", no->noTarefa->t.id
            ,no->noTarefa->t.prioridade,
            no->noTarefa->t.data_cria.dia,no->noTarefa->t.data_cria.mes,no->noTarefa->t.data_cria.ano
            ,no->noTarefa->t.descricao,no->noTarefa->lista->p.id
            ,no->noTarefa->lista->p.nome,
            no->noTarefa->t.prazo_conc.dia,no->noTarefa->t.prazo_conc.mes,no->noTarefa->t.prazo_conc.ano
            ,no->noTarefa->t.data_conc.dia,no->noTarefa->t.data_conc.mes,no->noTarefa->t.data_conc.ano);
}


void guarda_lista_tarefas(ListaTarefas lista){

    FILE *fp;
    ListaTarefas l;
    char nomef[30];
    printf("Nome do ficheiro[sem espacos]: "); /*Alterar se necessario*/
    scanf("%s", nomef);
    fp = fopen(nomef, "a");

    l = lista->next;  /*Salta o header*/
    while (l) {
        fprintf(fp, "ID: %d\nPrioridade: %d\nData de criacao: %d/%d/%d\nDescricao: %s\n", l->t.id, l->t.prioridade, l->t.data_cria.dia, l->t.data_cria.mes, l->t.data_cria.ano, l->t.descricao);
        l=l->next;
    }
    fclose(fp);
}
int numSemanas(Data * d){
    int i;/*número do mês*/
    int sum_dias=0;
    for (i=1;i<d->mes;i++){
        if(d->mes==1 || d->mes==3 || d->mes==5 || d->mes==7 || d->mes==8|| d->mes==10 || d->mes==12){/*meses com 31 dias*/
            sum_dias+=31;
        }
        else if(d->mes==2){
            sum_dias+=28;
        }
        else{/*Se tiverem 30 dias*/
            sum_dias+=30;
        }
    }
    sum_dias+=d->dia;
    if (sum_dias%7!=0){
        return sum_dias/7 + 1;
    }
    else
        return sum_dias/7;
}
