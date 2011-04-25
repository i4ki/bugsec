#ifndef PARSER_AST_H
#define PARSER_AST_H

#include "types.h"
#include "parser_bison.h"

/* General Purpose Registers */

/* 16 bits */
enum GNPREGISTER16 {
  AX = 1,
  BX,
  CX,
  DX,
  SP,
  BP,
  SI,
  DI,
  IP
};

/* 32 bits */
enum GNPREGISTER32 {
  EAX = 10,
  EBX,
  ECX,
  EDX,
  ESP,
  EBP,
  ESI,
  EDI,
  EIP
};

/* Segment Registers */
enum SREGISTERS {
  CS = 20,
  DS,
  SS,
  ES,
  FS,
  GS
};

enum OPCODETYPE {
  PUSH_REG = 100,
  PUSH_NUMBER,

  POP
};

/* Symbol Table */
struct symbol {
  char* lbl_name;
};

struct opcode {
  _u8 optype;
  _u8 reg1;
  _u8 reg2;
  _u16 mem;
  _u32 value;
};

#define NMAXSYMS 9999
struct symbol symtab[NMAXSYMS];

struct ast {
  struct opcode *op;
  struct symbol *s;
  char* directive;
};

/**
 * The program itself
 * The assembly syntaxe doesn't have a tree node AST.
 * Then I guess that a list of AST's could define the whole program.
 */
struct astlist {
  struct ast** a; /* AST's */
  _u32 count; /* AST's counter */
};

void add_astlist(struct astlist* l, struct ast* a);
void free_astlist(struct astlist* l);
struct ast * init_ast(struct opcode* op, struct symbol* s, char* directive);
void free_ast(struct ast* a);
struct opcode* init_opcode(_u8 optype, _u8 reg1, _u8 reg2, _u16 mem, _u32 value);
void free_opcode(struct opcode* op);

#define DEBUG_AST(a) do {                            \
  if (a) { \
  if (a->op) printf("opcode = %d\n", a->op->optype); \
  if (a->s) printf("symbol = %s\n", a->s->lbl_name); \
  if (a->directive) printf("directive %s\n", a->directive); \
  } \
  } while(0)
  

#endif
