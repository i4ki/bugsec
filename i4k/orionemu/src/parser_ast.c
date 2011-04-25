#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_ast.h"

void copy_ast(struct ast* dest, struct ast* src)
{
        dest->op = malloc(sizeof(struct ast));
        if (!dest->op)
        {
                fprintf(stderr, "memory limit ...\n");
                exit(1);
        }
        
        dest->op->optype = src->op->optype;
        dest->op->reg1 = src->op->reg1;
        dest->op->reg2 = src->op->reg2;
        dest->op->mem = src->op->mem;
        dest->op->value = src->op->value;

        if (src->s && strlen(src->s->lbl_name))
        {
                dest->s = malloc(sizeof(struct symbol));
                dest->s->lbl_name = strdup(src->s->lbl_name);
        }

        if (src->directive != NULL && strlen(src->directive) > 0)
                        dest->directive = strdup(src->directive);
}

void init_astlist(struct astlist* l)
{
        if (l->count > 0)
                free_astlist(l);

        l->count = 0;
        l->a = NULL;
}

void add_astlist(struct astlist* l, struct ast* a)
{
        if (!l->a)
                l->a = (struct ast**) malloc(sizeof(struct ast));
        else
                l->a = (struct ast**) realloc(l->a, sizeof(struct ast) * (l->count+1));

        if (!l->a)
        {
                fprintf(stderr, "insuficient memory ...\n");
                exit(1);
        }

        struct ast* ast_tmp = (struct ast*) malloc(sizeof(struct ast));
        if (!ast_tmp)
        {
                fprintf(stderr, "insuficient memory ...\n");
                exit(1);
        }

        copy_ast(ast_tmp, a);

        l->a[l->count] = ast_tmp;
        
        l->count += 1;
}

void free_astlist(struct astlist* l)
{
        _u32 i;
        if (l->count > 0 && l->a != NULL)
        {
                for (i = 0; i < l->count; i++)
                {
                        free_ast(l->a[i]);
                }
                free(l->a);
        }
}

struct opcode* init_opcode(
        _u8 optype,
        _u8 reg1,
        _u8 reg2,
        _u16 mem,
        _u32 value)
{
        struct opcode* op = (struct opcode*) malloc(sizeof(struct opcode));
        if (!op)
        {
                fprintf(stderr, "memory insufficient...\n");
                exit(1);
        }

        op->optype = optype;
        op->reg1 = reg1;
        op->reg2 = reg2;
        op->mem = mem;
        op->value = value;

        return op;
}

void free_opcode(struct opcode* op)
{
        if (op)
                free(op);
}

struct ast* init_ast(
        struct opcode* op,
        struct symbol* s,
        char* directive)
{
        struct ast* a = (struct ast*) malloc(sizeof(struct ast));
        if (!a)

        {
                fprintf(stderr, "memory insufficient ...\n");
                exit(1);
        }

        a->op = op != NULL ? op : NULL;
        a->s = s != NULL ? s : NULL;
        a->directive = directive != NULL ? directive : NULL;

        return a;
}

void free_ast(struct ast* a)
{
        if (a)
        {
                if (a->op)
                        free(a->op);
                if (a->s)
                {
                        if (a->s->lbl_name)
                                free(a->s->lbl_name);
                        free(a->s);
                }
                if (a->directive) free(a->directive);

                free(a);
        }
}

