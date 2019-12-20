/**
 * @file Scanner.hpp
 * @author André Lucas Maegima
 * @brief Definição da classe utilizada para a analise léxica.
 * @version 1.0
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _SCANNER_HPP_
#define _SCANNER_HPP_

#include "TokenType.hpp"

/**
 * @brief Classe responsárvel por fazer a análise léxica. 
 */ 
class Scanner{
private:
    int line_number; /**< Linha atual do arquivo de origem. */
    bool trace; /**< Caso tenha valor true imprime no arquivo 
    de saída do scanner os tokens lidos. */
    FILE *listing; /**< Arquivo de saída do scanner. */
public:
    /**
     * @brief O método Scanner inicializa as 
     * váriaveis do analisador léxico.
     * 
     * @param source Arquivo de entrada do scanner.
     * @param listing Arquivo de saída do scanner.
     * @param trace Rastrear ou não.
     */
    Scanner(FILE *source, FILE *listing, bool trace);

    /**
     * @brief O método getToken retorna o próximo token
     * do arquivo de origem.
     * 
     * @return TokenType Token do arquivo.
     */
    TokenType getToken();
    /**
     * @brief O método lexicalError imprime uma mensagem
     * na tela caso ocorra algum erro léxico.
     * 
     * @return TokenType Retorna o token de erro.
     */
    TokenType lexicalError();
    /**
     * @brief O método getLineNumber retorna a linha atual
     * do código de entrada.
     * 
     * @return int Número da linha.
     */
    int getLineNumber();
    /**
     * @brief O método incrementLine incrementa a váriavel
     * que indica a linha atual do arquivo de entrada.
     * 
     */
    void incrementLine();
    /**
     * @brief O método printToken imprime um token 
     * e seu lexema no arquivo de listagem.
     * 
     * @param lisiting Arquivo de saída.
     * @param token Identificador do token.
     * @param tokenString Descrição textual do token.
     */
    void printToken(FILE *listing, TokenType token, const char* tokenString);
};

#endif




