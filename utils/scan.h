/**
 * @file scan.h
 * @author André Lucas Maegima
 * @brief Interface para o analisador léxico
 * @version 0.1
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#ifndef _SCAN_H_
#define _SCAN_H_

/**
 * @brief getToken retorna o próximo token
 * do arquivo de origem
 * 
 * @return TokenType token do arquivo
 */
TokenType getToken(void);

/**
 * @brief initScanner inicializa as 
 * váriaveis do analizador léxico
 * 
 */
void initScanner();

#endif
