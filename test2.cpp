#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char lookahead;

void error() {
    printf("Error\n");
    exit(1);
}

void match(char c) {
    if (lookahead == c) {
        lookahead = getchar();
    } else {
        error();
    }
}

int is_digit(char c) {
    return isdigit(c);
}

int is_plus(char c) {
    return c == '+';
}

int is_minus(char c) {
    return c == '-';
}

int is_times(char c) {
    return c == '*';
}

int is_divide(char c) {
    return c == '/';
}

int is_expr(char c) {
    return is_digit(c);
}

int is_term(char c) {
    return is_expr(c);
}

int is_factor(char c) {
    return is_expr(c);
}

int expr() {
    int value = term();
    while (is_plus(lookahead) || is_minus(lookahead)) {
        if (is_plus(lookahead)) {
            match('+');
            value += term();
        } else if (is_minus(lookahead)) {
            match('-');
            value -= term();
        }
    }
    return value;
}

int term() {
    int value = factor();
    while (is_times(lookahead) || is_divide(lookahead)) {
        if (is_times(lookahead)) {
            match('*');
            value *= factor();
        } else if (is_divide(lookahead)) {
            match('/');
            value /= factor();
        }
    }
    return value;
}

int factor() {
    int value;
    if (is_expr(lookahead)) {
        value = lookahead - '0';
        match(lookahead);
    } else if (lookahead == '(') {
        match('(');
        value = expr();
        match(')');
    } else {
        error();
    }
    return value;
}

int main() {
    lookahead = getchar();
    int result = expr();
    if (lookahead != '\n') {
        error();
    }
    printf("%d\n", result);
    return 0;
}
