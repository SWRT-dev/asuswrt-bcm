/*****************************************************************************\
*  _  _       _          _              ___                                   *
* | || | ___ | |_  _ __ | | _  _  __ _ |_  )                                  *
* | __ |/ _ \|  _|| '_ \| || || |/ _` | / /                                   *
* |_||_|\___/ \__|| .__/|_| \_,_|\__, |/___|                                  *
*                 |_|            |___/                                        *
\*****************************************************************************/

#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H 1

#ifdef HND_ROUTER
#define inline  
#endif

char *dup_line(char *, char **);
inline int iscolon(int);
char *dup_token(char *, char **, int (*)(int));
char *dup_token_r(char *, char *, char **, int (*)(int));
#endif
