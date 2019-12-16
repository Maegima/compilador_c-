/**
 * @file SymbolTable.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe SymbolTable.
 * @version 1.0
 * @date 2019-12-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _SYMBOLTABLE_HPP_
#define _SYMBOLTABLE_HPP_

#include "TreeNode.hpp"
#include "BucketList.hpp"

/** SIZE é o tamanho da tabela hash. (Isso ira para o CPP) */
#define SIZE 211

/**
 * @brief Classe responsável por armazenar as variáveis
 * utilizadas na análise semântica.
 * 
 */
class SymbolTable{
private:
    /// A tabela hash.
    BucketList **table;
    /**
     * @brief A função hash.
     * 
     * @param key Chave para fazer o hash.
     * @return int Hash da chave.
     */
    int hash(const char *key);
    
    /**
     * @brief O método traverse percorre a árvore em 
     * pré-ordem.
     * 
     * @param t Nó da árvore.
     */
    void traverse(TreeNode *t);

    /**
     * @brief O método insertNode insere identificadores 
     * armazenados na árvore sintática na tabela de simbolos.
     * 
     * @param t Nó da árvore.
     */
    void insertNode(TreeNode *t);
public:
    /**
     * @brief Construct a new Symbol Table object.
     * 
     */
    SymbolTable();
    /**
     * @brief O método insert insere ou 
     * atualiza um dado na tabela de simbolos.
     * 
     * @param name Nome.
     * @param idName Escopo.
     * @param lineno Linha.
     * @param decl_line Linha de declaração.
     * @param type Tipo.
     * @param func Se é função.
     * @param atrib Se é atribuição.
     * @param loc Localização na memória.
     */
    void insert(std::string *name, std::string *idName, int lineno, int decl_line, int type, int func, int atrib, int loc);

    /**
     * @brief O método lookup procura na tabela
     * de símbolos por um dado.
     * 
     * @param name Id do dado a ser procurado.
     * @return int Localização do dado.
     */
    int lookup(std::string *name);

    /**
     * @brief O método print imprime em um
     * arquivo a tabela de simbolos.
     * 
     * @param listing Arquivo de escrita.
     */
    void print(FILE *listing);

    /**
     * @brief Get the Hash Table object.
     * 
     * @return BucketList** A tabela hash.
     */
    BucketList **getHashTable();

    /**
     * @brief O método que constroi a tabela de simbolos
     * percorrendo a árvore sintática em pré ordem.
     * 
     * @param syntaxTree Raiz da árvore sintática.
     */
    void build(TreeNode *symtaxTree);
};

#endif

