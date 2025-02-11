/*
  EP: Árvore Binária de Busca (BST)
  Professor Anderson Ávila - UEL
  Descrição: Completar as funções solicitadas, sem alterar suas assinaturas.
  
  A main() contém testes que exibem resultados esperados como comentário.
  Quando as funções estiverem corretamente implementadas, esses testes
  devem produzir a saída indicada.
*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct no {
    int chave;
    int contador;           // número de cópias (frequência) dessa chave
    struct no* esq;         // ponteiro para subárvore esquerda
    struct no* dir;         // ponteiro para subárvore direita
} NO, *PONT;

// Protótipos das funções
void inicializar(PONT* raiz);
PONT criarNo(int valor);
PONT inserir(PONT raiz, int valor);
PONT buscarNo(PONT raiz, int valor, PONT *pai);
PONT removerUmaOcorrencia(PONT raiz, int valor);
PONT removerTodasOcorrencias(PONT raiz, int valor);
PONT buscar(PONT raiz, int valor);
void exibirInOrder(PONT raiz);
void exibirPreOrder(PONT raiz);
void exibirPosOrder(PONT raiz);
int contarNos(PONT raiz);
int contarTotalElementos(PONT raiz);
int InOrderKEsimoMenor(PONT raiz, int k, int* contador);
int kEsimoMenor(PONT raiz, int k);
void imprimirIntervalo(PONT raiz, int min, int max);
PONT lowestCommonAncestor(PONT raiz, int val1, int val2);

//------------------------------------------------------------------------------
// 1) Inicializar ✔
void inicializar(PONT* raiz) {
    *raiz = NULL;
}

//------------------------------------------------------------------------------
// 2) Criar nó ✔
PONT criarNo(int valor) {
    PONT novo = (PONT) malloc(sizeof(NO));
    if(novo) {
        novo->chave = valor;
        novo->contador = 1;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

//------------------------------------------------------------------------------
// 3) Buscar ✔
PONT buscar(PONT raiz, int valor) {
    if (!raiz) return NULL;
    if (valor == raiz->chave) return raiz;
    if (valor < raiz->chave) return buscar(raiz->esq, valor);
    if (valor > raiz->chave) return buscar(raiz->dir, valor);
    return NULL;
}

//------------------------------------------------------------------------------
// 4) Inserir ✔
PONT inserir(PONT raiz, int valor) {
    if(!raiz) return criarNo(valor);
    if(valor < raiz->chave) raiz->esq = inserir(raiz->esq, valor);
    else if(valor > raiz->chave) raiz->dir = inserir(raiz->dir, valor);
    else raiz->contador++;
    return raiz;
}

//------------------------------------------------------------------------------
// 5.1) Método de Busca Auxiliar ✔
PONT buscarNo(PONT raiz, int valor, PONT *pai) {
    PONT atual = raiz;
    *pai = NULL;
    while (atual) {
        if (atual->chave == valor) return atual;
        *pai = atual;
        if (valor < atual->chave) atual = atual->esq;
        else atual = atual->dir;
    }
    return NULL;
}

// 5.2) Remover UMA ocorrência ✔
PONT removerUmaOcorrencia(PONT raiz, int valor){
    PONT pai, no, p, q;
    no = buscarNo(raiz, valor, &pai);
    if(no == NULL) return raiz;
    if (no->contador > 1){
        no->contador--;
        return raiz;
    }
    if(!no->esq || !no->dir){
        if(!no->esq) q = no->dir;
        else q = no->esq;
    }
    else {
        p = no;
        q = no->esq;
        while(q->dir){
            p = q;
            q = q->dir;
        }
        if(p != no){
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }
    if(!pai){
        free(no);
        return (q);
    }
    if (valor < pai->chave) pai->esq = q;
    else pai->dir = q;
    free(no);
    return raiz;
}

//------------------------------------------------------------------------------
// 6) Remover TODAS ocorrências ✔
PONT removerTodasOcorrencias(PONT raiz, int valor) {
    PONT pai, no, p, q;
    no = buscarNo(raiz, valor, &pai);
    if(no == NULL) return raiz;
    if(!no->esq || !no->dir){
        if(!no->esq) q = no->dir;
        else q = no->esq;
    }
    else {
        p = no;
        q = no->esq;
        while(q->dir){
            p = q;
            q = q->dir;
        }
        if(p != no){
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }
    if(!pai){
        free(no);
        return (q);
    }
    if (valor < pai->chave) pai->esq = q;
    else pai->dir = q;
    free(no);
    return raiz;
}

//------------------------------------------------------------------------------
// 7) Exibir InOrder ✔
void exibirInOrder(PONT raiz) {
    if (raiz == NULL) return;
    exibirInOrder(raiz->esq);
    for(int i = raiz->contador; i > 0; i--){
        printf("%d ", raiz->chave);
    }
    exibirInOrder(raiz->dir);
}

//------------------------------------------------------------------------------
// 8.1) Exibir PreOrder ✔
void exibirPreOrder(PONT raiz){
    if (raiz == NULL) return;
    for(int i = raiz->contador; i > 0; i--){
        printf("%d ", raiz->chave);
    }
    exibirPreOrder(raiz->esq);
    exibirPreOrder(raiz->dir);
}

// 8.2) Exibir PosOrder ✔
void exibirPosOrder(PONT raiz){
    if (raiz == NULL) return;
    exibirPosOrder(raiz->esq);
    exibirPosOrder(raiz->dir);
    for(int i = raiz->contador; i > 0; i--){
        printf("%d ", raiz->chave);
    }
}

//------------------------------------------------------------------------------
// 9) Contar nós distintos ✔
int contarNos(PONT raiz) {
    if(!raiz) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

//------------------------------------------------------------------------------
// 10) Contar total de elementos (somando contadores) ✔
int contarTotalElementos(PONT raiz) {
    if(!raiz) return 0;
    return raiz->contador + contarTotalElementos(raiz->esq) + contarTotalElementos(raiz->dir);
}

//------------------------------------------------------------------------------
// 11.1) Função auxiliar k-ésimo menor ✔
int InOrderKEsimoMenor(PONT raiz, int k, int* contador){
    if (!raiz) return -1;

    int valor = InOrderKEsimoMenor(raiz->esq, k, contador);
    if (valor != -1) return valor;

    for(int i = raiz->contador; i > 0; i--){
        (*contador)++;
        if(*contador == k){
            return raiz->chave;
        }
    }

    valor = InOrderKEsimoMenor(raiz->dir, k, contador);
    
}

// 11.2) k-ésimo menor ✔
int kEsimoMenor(PONT raiz, int k) {
    if(k > contarTotalElementos(raiz)) return -1;
    int contador = 0;
    return InOrderKEsimoMenor(raiz, k, &contador);
}

//------------------------------------------------------------------------------
// 12) Imprimir Intervalo [min, max] ✔
void imprimirIntervalo(PONT raiz, int min, int max) {
    if(!raiz) return;
    if(raiz->chave > min) imprimirIntervalo(raiz->esq, min, max);
    if (raiz->chave >= min && raiz->chave <= max) {
        for(int i = raiz->contador; i > 0; i--){
            printf("%d ", raiz->chave);
        }
    }
    if(raiz->chave < max) imprimirIntervalo(raiz->dir, min, max);
}

//------------------------------------------------------------------------------
// 13) Lowest Common Ancestor - Ancestral comum mais prox das chaves val1 e val2 ✔
PONT lowestCommonAncestor(PONT raiz, int val1, int val2) {
    if (!buscar(raiz, val1)) return NULL;
    if (!buscar(raiz, val2)) return NULL;
    if (!raiz) return NULL;
    if (val1 < raiz->chave && val2 < raiz->chave) return lowestCommonAncestor(raiz->esq, val1, val2);
    if (val1 > raiz-> chave && val2 > raiz->chave) return lowestCommonAncestor(raiz->dir, val1, val2);
    return raiz; 
}

//------------------------------------------------------------------------------
// main() para testes com expectativas de resultado
int main() {
    // PONT raiz;                    // ponteiro para a raiz da BST
    // inicializar(&raiz);           // deixa a árvore vazia
    // 
    // As funções a serem implementadas:
    //   - criarNo
    //   - inserir
    //   - removerUmaOcorrencia
    //   - removerTodasOcorrencias
    //   - buscar
    //   - exibirInOrder
    //   - contarNos
    //   - contarTotalElementos
    //   - kEsimoMenor
    //   - imprimirIntervalo
    //   - lowestCommonAncestor

    PONT raiz;
    inicializar(&raiz);

    // -------------------------------------------------------
    // 1) Inserção com valores repetidos
    //    Esperado que:
    //      - nó 10 tenha contador=2
    //      - nó 5  tenha contador=3
    //      - nó 15 tenha contador=1
    //      - nó 18 tenha contador=1
    //
    // InOrder final esperado (antes de quaisquer remoções):
    //     "5 5 5 10 10 15 18"
    //
    raiz = inserir(raiz, 10); 
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 10); // repetido => contador(10)++
    raiz = inserir(raiz, 5);  // repetido => contador(5)++
    raiz = inserir(raiz, 5);  // repetido => contador(5)++
    raiz = inserir(raiz, 18);

    printf("\n--- APÓS INSERIR (10,5,15,10,5,5,18) ---\n");
    printf("InOrder esperado: 5 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz); 
    printf("\n");

    //EXTRAS inseridos pelo aluno (Alexandre Marchioli)
    printf("\n--- EXTRA - PreOrder e PosOrder -> inserido pelo aluno (Alexandre Marchioli) ---\n");
    printf("PreOrder esperado: 10 10 5 5 5 15 18\n");
    printf("PreOrder obtido:   ");
    exibirPreOrder(raiz); 
    printf("\n\n");
    printf("PosOrder esperado: 5 5 5 18 15 10 10\n");
    printf("PosOrder obtido:   ");
    exibirPosOrder(raiz); 
    printf("\n");
    
    // -------------------------------------------------------
    // 2) Busca por valores
    PONT node5 = buscar(raiz, 5);
    if(node5) {
        printf("\nBuscar(5): encontrado com contador=%d (esperado=3)\n", node5->contador);
    } else {
        printf("\nBuscar(5): não encontrado (inesperado)\n");
    }

    PONT nodeX = buscar(raiz, 999); // valor não existente
    if(!nodeX) {
        printf("Buscar(999): não encontrado (esperado)\n");
    } else {
        printf("Buscar(999): encontrado??? (inesperado)\n");
    }

    // -------------------------------------------------------
    // 3) Remover UMA ocorrência 
    //    removerUmaOcorrencia(5) => contador(5) deve passar de 3 para 2
    raiz = removerUmaOcorrencia(raiz, 5);

    printf("\n--- APÓS removerUmaOcorrencia(5) ---\n");
    printf("Esperado InOrder: 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    node5 = buscar(raiz, 5);
    if(node5) {
        printf("Agora contador(5)=%d (esperado=2)\n", node5->contador);
    }

    // -------------------------------------------------------
    // 4) Remover TODAS ocorrências
    //    removerTodasOcorrencias(10) => remove nó com chave=10 por completo
    raiz = removerTodasOcorrencias(raiz, 10);

    printf("\n--- APÓS removerTodasOcorrencias(10) ---\n");
    printf("Esperado InOrder: 5 5 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    // -------------------------------------------------------
    // 5) Contagem de nós e total de elementos
    //    Árvores resultante: {5(cont=2), 15(cont=1), 18(cont=1)}
    //      => contarNos=3   (chaves distintas: 5,15,18)
    //      => contarTotalElementos=4   (5,5,15,18)
    int qtdNos = contarNos(raiz);
    int totalElem = contarTotalElementos(raiz);
    printf("\ncontarNos => %d (esperado=3)\n", qtdNos);
    printf("contarTotalElementos => %d (esperado=4)\n", totalElem);

    // -------------------------------------------------------
    // 6) k-ésimo menor (considerando contadores)
    //    InOrder real: [5,5,15,18]
    //       k=1 => 5
    //       k=2 => 5
    //       k=3 => 15
    //       k=4 => 18
    //       k=5 => -1 (não existe)
    printf("\n--- Teste k-ésimo menor ---\n");
    printf("k=1 => %d (esperado=5)\n", kEsimoMenor(raiz,1));
    printf("k=2 => %d (esperado=5)\n", kEsimoMenor(raiz,2));
    printf("k=3 => %d (esperado=15)\n", kEsimoMenor(raiz,3));
    printf("k=4 => %d (esperado=18)\n", kEsimoMenor(raiz,4));
    printf("k=5 => %d (esperado=-1)\n", kEsimoMenor(raiz,5));

    // -------------------------------------------------------
    // 7) imprimirIntervalo [6..18]
    //    InOrder da árvore: 5,5,15,18
    //    Filtrando [6..18], esperamos: 15 18
    printf("\n--- Teste imprimirIntervalo [6..18] ---\n");
    printf("Esperado: 15 18\nObtido:   ");
    imprimirIntervalo(raiz, 6, 18);
    printf("\n");

    // -------------------------------------------------------
    // 8) Testar LCA (lowestCommonAncestor) - não é opcional
    //    Vamos inserir mais alguns valores para teste de LCA
    //    Situação final da árvore atual: 5(cont=2),15(cont=1),18(cont=1)
    //    Inserir(12), Inserir(16), Inserir(3)
    //    Nova BST (com contadores):
    //       5 (cont=2)
    //           /    \
    //         3(1)   15(1)
    //                /  \
    //              12(1) 18(1)
    //                    /       <-- CORREÇÃO, 16 é filho de 18, e não de 12.
    //                  16(1)
    inserir(raiz, 12);
    inserir(raiz, 16);
    inserir(raiz, 3);

    printf("\n--- Árvore após inserir(12,16,3) ---\n");
    printf("InOrder esperado: 3 5 5 12 15 16 18\n");
    printf("Obtido:           ");
    exibirInOrder(raiz);
    printf("\n");

    // LCA tests:
    //  LCA(3,5) -> 5 ou 3? 
    //     - 3 e 5 estão ambos na subárvore da raiz=5? 
    //     - Se a raiz é 5, e 3<5 => esq 
    //       => LCA(3,5) deve ser 5, mas depende da estrutura exata
    //  LCA(3,12) -> 5
    //  LCA(16,18) -> 16 ou 15? 
    //     => Analisando: 16 < 18 => 16 deve estar na subárvore direita(15)
    //        -> 15 < 16 => goes right => 18
    //        => 16 < 18 => subárvore esquerda de 18
    //        => LCA deve ser 15 ou 18? Precisamos verificar a implementação.
    //  LCA(5,18) -> 5 (pois 5 é raiz, e 18 está à direita)

    PONT nLCA;

    nLCA = lowestCommonAncestor(raiz, 3, 5);
    if(nLCA) {
        printf("\nLCA(3,5) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 3, 12);
    if(nLCA) {
        printf("LCA(3,12) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    ////////////////////  NOTA DO ALUNO : ALEXANDRE MARCHIOLI   ///////////////////////////
    //ATENÇÃO: Resultado esperado 15 é incorreto, portanto, modifiquei o resultado esperado para 18! Segue abaixo a explicação, printada direto no código. Colocarei-a também no arquivo "readme.md".
    nLCA = lowestCommonAncestor(raiz, 16, 18);
    if(nLCA) {
        printf("LCA(16,18) => chave=%d (esperado=18)\n", nLCA->chave);
    }
    printf(">>>>> Nota do Aluno: O resultado esperado é 18. Anteriormente no código, estava como 15, mas isso é incorreto. Uma explicação sobre esse erro foi deixada no arquivo README.md.\n\n");


    nLCA = lowestCommonAncestor(raiz, 5, 18);
    if(nLCA) {
        printf("LCA(5,18) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    // Por fim, buscar um LCA com valor inexistente
    nLCA = lowestCommonAncestor(raiz, 100, 3);
    if(!nLCA) {
        printf("LCA(100,3) => NULL (esperado=chave nao existe)\n");
    }

    printf("\n--- FIM DOS TESTES ---\n");

    return 0;
}
