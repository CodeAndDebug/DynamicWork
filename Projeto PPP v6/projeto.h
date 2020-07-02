#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
typedef struct
{
    int dia, mes, ano;
} Data;
typedef struct
{
    int id;
    int prioridade;
    Data data_cria;
    char* descricao; /*Descricao textual da tarefa*/
    Data prazo_conc; /*Prazo maximo de conclusao*/
    Data data_conc; /*Data efetiva de conclusao*/
    int fase_p; /*1,2,3,*/
}Tarefa;
/*lista de apontadores genérica para tarefas */
typedef struct lnodeApontador *ListApontador;
typedef struct lnodeApontador
{
    struct lnodeTarefas *noTarefa;
    ListApontador next;
}List_apontador;

typedef struct
{
    char *nome;
    char *email;
    int id;
    int num_t; /*Numero de tarefas*/
}Pessoa;

/*Lista de Pessoas */
typedef struct lnodePessoas *ListaPessoas;
typedef struct lnodePessoas
{
    Pessoa p;
    List_apontador listaApontadoresTarefas;
    ListaPessoas next;
} List_nodePessoas;


/*Lista de Tarefas */
typedef struct lnodeTarefas *ListaTarefas;
typedef struct lnodeTarefas
{
    Tarefa t;
    ListaPessoas lista;/*Pessoa responsavel pela tarefa*/
    ListaTarefas next;
} List_nodeTarefas;


/*Cabeçalhos random*/
ListApontador cria_lista_apontadores(void);

/*Cabeçalhos das funções*/
void menu_inicial(ListaPessoas, ListaTarefas, ListApontador, ListApontador, ListApontador);
void menu_inicial_text(void);

/***********Pessoas***********/
ListaPessoas cria_lista_pessoas (void);
void le_dados_pessoa(Pessoa*);
void insere_pessoa(ListaPessoas, Pessoa*);
void elimina_pessoa(ListaPessoas, int);
void imprime_lista_pessoas(ListaPessoas);
void procura_lista_pessoas (ListaPessoas , int , ListaPessoas *, ListaPessoas *);
ListaPessoas destroi_lista_pessoas(ListaPessoas);

int max_tarefas(int);/*Melhorar e implementar*/

/***********Tarefas***********/
ListaTarefas cria_lista_tarefas (void);
void imprime_lista_tarefas(ListaTarefas ,ListaPessoas  , ListApontador ,ListApontador ,ListApontador );
void insere_tarefa (ListaTarefas,ListaTarefas);
void cria_tarefa2 (ListaTarefas,ListApontador);
void insere_tarefa2 (ListaTarefas,ListaTarefas);
void procura_lista_tarefas (ListaTarefas , int , ListaTarefas* , ListaTarefas* );
void le_dados_iniciais_tarefa2(Tarefa *,ListaTarefas );
void elimina_tarefa(ListaTarefas, int);
ListaTarefas destroi_lista_tarefas(ListaTarefas);
void insere_ToDo(ListApontador  , ListApontador );

void ordenaTarefas(ListaTarefas);
void insere_ord_tarefas(ListaTarefas  , ListaTarefas );
int comparaDatas(Data *d1 , Data *d2);
int comparaToDo(List_nodeTarefas n1,List_nodeTarefas n2);
void imprime_lista_todo(ListApontador lista);
ListApontador retira(ListApontador ,int );
void teste7(ListApontador lista);
void worker5(ListaPessoas ,ListaTarefas ,ListApontador ,ListApontador ,ListApontador );
void listarPessoascomID(ListaPessoas lista);
void imprimeToDoID_pessoa(ListApontador ,int);
void imprimeDoingID_pessoa(ListApontador,int);
void imprimeDoneID_pessoa(ListApontador,int);
void imprimeQuadroPessoa(ListaPessoas ,ListApontador  ,ListApontador  , int );
void ToDoparaDoing(ListaPessoas  ,ListaTarefas , ListApontador ,ListApontador ,ListApontador ,int );
void DoingparaToDo(ListaPessoas  ,ListApontador ,ListApontador );
ListaPessoas procuraPessoaID( ListaPessoas ,  int);
void alterar_responsavel(ListaPessoas  , ListApontador  , int ,int );
void DoingparaDone(ListaPessoas  , ListApontador ,ListApontador );
void imprimeDoing(ListApontador );
void imprimeDone(ListApontador );
void ReabreCartao(ListApontador , ListApontador );
int verifica_id(ListaPessoas , int );
int numTarefasDoing(ListApontador );
int verifica_id_todo(ListApontador lista_todo,int id_cartao);
void altera_prioridade(ListaPessoas ,ListaTarefas  , ListApontador  , ListApontador  , ListApontador );
ListApontador devolveApontador_ID(ListApontador ,int );
void imprime_lista_pessoas_vagas(ListaPessoas ,int );
ListApontador destroi_lista_apontadores(ListApontador );
int verifica_prazos(ListaPessoas ,ListApontador  ,int ,Data *);
void carregarTarefas(ListaPessoas ,ListaTarefas ,ListApontador ,ListApontador ,ListApontador );
void guardarTarefas(ListaPessoas ,ListaTarefas ,ListApontador ,ListApontador ,ListApontador );
void imprimeToDoFicheiros(FILE *, ListApontador );
void imprimeDoingFicheiros(FILE * , ListApontador );
void imprimeDoneFicheiros(FILE * , ListApontador );
void visualiza_tabela(ListaPessoas  ,ListaTarefas  ,ListApontador , ListApontador , ListApontador );
void guarda_quadro(ListApontador , ListApontador , ListApontador );
void guarda_quadro_pessoa(ListApontador , ListApontador , int );
void guardaDoing(ListApontador , FILE *);
void guardaDone(ListApontador , FILE *);
void guarda_lista_tarefas(ListaTarefas );
int verifica_id_cartao(ListaTarefas , int );
int numSemanas(Data * );
/***********Operacoes com Colunas************/



/*Ficheiros de texto*/

void carregarPessoas(ListaPessoas);
#endif
