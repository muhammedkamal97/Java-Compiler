//
// Created by mario_hunter on 4/20/19.
//
#include "util.h"

Token *
create_token(string token_type_name) {
    TokenType *type = new TokenType{
            token_type_name,
            false
    };

    Token *tkn = new Token{
            type,
            string("")
    };
    return tkn;
}