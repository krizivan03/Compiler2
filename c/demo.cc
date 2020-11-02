#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <unordered_map>
#include "compiler.h"
#include "lexer.h"
using namespace std;

LexicalAnalyzer lexer;
struct InstructionNode * parseProgram();
void parseVarSection();
void parseIDList();
struct InstructionNode * parseBody();
struct InstructionNode * parseStmt_list();
struct InstructionNode * parseStmt();
struct InstructionNode * parseAssignStmt();
struct expr;
expr *parseExpr();
Token parsePrimary();
ArithmeticOperatorType parseOp();
struct InstructionNode * parseOutputStmt();
struct InstructionNode * parseInputStmt();
struct InstructionNode * parseWhileStmt();
struct InstructionNode * parseIfStmt();
expr *parseCondition();
ConditionalOperatorType parseRelop();
struct InstructionNode * parseSwitchStmt();
struct InstructionNode * parseForStmt();
struct InstructionNode *parseCaseList(Token t, struct InstructionNode *switchNoop);
struct InstructionNode *parseCase(Token t, struct InstructionNode *switchNoop);
struct InstructionNode *parseDefaultCase(Token t,struct InstructionNode * switchNoop);
void parseInputs();
void parseNumList();
void initInst(struct InstructionNode *i);

unordered_map<string, int> m; // variable as a string, its location in mem as an int
typedef struct expr{
    Token LHS;
    ArithmeticOperatorType anOp;
    ConditionalOperatorType aC_OP;
    Token RHS;
} expr;

struct InstructionNode *parse_generate_intermediate_representation()
{
    next_available = 0;
    next_input = 0;
    struct InstructionNode *i = parseProgram();
    return i;
}
/*----------------------------PARSER----------------------------*/
void syntax_error(Token t)
{
    cout << "SYNTAX ERROR !&%!" << endl;
    cout << t.lexeme << endl;
    cout << "Line Number " << t.line_no << endl;
    exit(1);
}
Token expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error(t);
    return t;
}
struct InstructionNode *parseProgram(){
    struct InstructionNode *i;
    parseVarSection();
    i = parseBody();
    parseInputs();
    return i;
}
void parseVarSection(){
    parseIDList();
    expect(SEMICOLON);
}

void parseIDList(){
    Token t = expect(ID); m[t.lexeme] = next_available; mem[next_available++] = 0; // a, b, c, d;
    t = lexer.peek(1);
    if(t.token_type == COMMA){
        expect(COMMA);
        parseIDList();
    }
}
struct InstructionNode *parseBody(){
    struct InstructionNode *i;
    expect(LBRACE);
    i = parseStmt_list();
    expect(RBRACE);
    return i;
}
struct InstructionNode * parseStmt_list(){
    struct InstructionNode *i;
    struct InstructionNode *lastI;

    i = parseStmt();
    lastI = i; while (lastI->next!=NULL){lastI = lastI->next;}

    Token t = lexer.peek(1);
    if(t.token_type != RBRACE){
        lastI->next = parseStmt_list(); //might need noop to link to next also
    }
    else{lastI->next = NULL;}
    return i;
}
struct InstructionNode * parseStmt(){
    struct InstructionNode *i;
    struct InstructionNode * j;

    Token t = lexer.peek(1);
    switch (t.token_type)
    {
    case ID:
        i = parseAssignStmt();
    break;
    case IF:
        i = parseIfStmt(); 
        break;
    case WHILE:
        i = parseWhileStmt(); 
        break;
    case SWITCH:
        i = parseSwitchStmt(); //might need noop after this
        break;
    case FOR:
        i = parseForStmt(); //might need noop after this
        break;
    case INPUT:
        i = parseInputStmt();
    break;
    case OUTPUT:
        i = parseOutputStmt();
        break;
    
    default:
        syntax_error(t);
    }
    return i;
}
struct InstructionNode * parseAssignStmt(){
    struct InstructionNode * i = new InstructionNode; initInst(i);
    i->type = ASSIGN ;
    Token t;
    t = expect(ID); i->assign_inst.left_hand_side_index = m[t.lexeme];
    expect(EQUAL);
    t = lexer.peek(2);

    if(t.token_type==SEMICOLON){
        i->assign_inst.op = OPERATOR_NONE;
        t = parsePrimary(); i->assign_inst.operand1_index = m[t.lexeme];
    }else{
        expr * e = parseExpr();
        i->assign_inst.op = e->anOp;
        i->assign_inst.operand1_index = m[e->LHS.lexeme];
        i->assign_inst.operand2_index = m[e->RHS.lexeme];
    }
    expect(SEMICOLON);
    return i;
}
expr *parseExpr(){
    expr *e = new expr;
    e->LHS = parsePrimary();
    e->anOp = parseOp();
    e->RHS = parsePrimary();
    return e;
}
Token parsePrimary(){
    Token t = lexer.peek(1);
    if (t.token_type==ID){ t = expect(ID); } // might also need bottom if statement
    else    {   
        t = expect(NUM);
        if(m.find(t.lexeme) == m.end()){ // if its not there
            m[t.lexeme] = next_available; // this is adding constants to Table "5", index
             mem[next_available++] = stoi(t.lexeme);    //  adding the actual integer to the index of mem[]
        }
        }
        return t;
}
ArithmeticOperatorType parseOp(){
    Token t = lexer.peek(1);
    ArithmeticOperatorType theOp;
    switch (t.token_type)
    {
    case PLUS:
        t = lexer.GetToken();
        theOp = OPERATOR_PLUS;
        break;
    case MINUS:
        t = lexer.GetToken();
        theOp = OPERATOR_MINUS;
        break;
    case MULT:
        t = lexer.GetToken();
        theOp = OPERATOR_MULT;
        break;
    case DIV:
        t = lexer.GetToken();
        theOp = OPERATOR_DIV;
        break;
    default:
    syntax_error(t);
        break;
    }
    return theOp;
}
struct InstructionNode * parseOutputStmt(){
    struct InstructionNode * i = new InstructionNode; initInst(i);
    Token t;
    expect(OUTPUT); i->type = OUT;
    t = expect(ID); i->output_inst.var_index = m[t.lexeme];
    expect(SEMICOLON);
    return i;
}
struct InstructionNode * parseInputStmt(){
    struct InstructionNode * i = new InstructionNode; initInst(i);
    Token t;
    expect(INPUT); i->type = IN ;
    t = expect(ID); i->input_inst.var_index = m[t.lexeme];
    expect(SEMICOLON);
    return i;
}
struct InstructionNode * parseWhileStmt(){
    struct InstructionNode * i = new InstructionNode; initInst(i);
    struct InstructionNode * j = new InstructionNode; initInst(j); j->type = NOOP;
    struct InstructionNode * jmp = new InstructionNode; initInst(jmp); jmp->type = JMP; jmp->jmp_inst.target = i; jmp->next = j;
    struct InstructionNode *lastI;

    expect(WHILE); i->type = CJMP;
    expr *e = parseCondition();

    i->cjmp_inst.condition_op = e->aC_OP;
    i->cjmp_inst.operand1_index = m[e->LHS.lexeme];
    i->cjmp_inst.operand2_index = m[e->RHS.lexeme];
    i->next = parseBody();
    i->cjmp_inst.target = j;

    lastI = i; while (lastI->next!=NULL){ lastI = lastI->next; }
    lastI->next = jmp;
    
    return i;
}
struct InstructionNode * parseIfStmt(){
    struct InstructionNode * i = new InstructionNode; initInst(i);
    struct InstructionNode * j = new InstructionNode; initInst(j); j->type = NOOP;
    struct InstructionNode *lastI;

    expect(IF); i->type = CJMP;
    expr *e = parseCondition(); 
    
    i->cjmp_inst.condition_op = e->aC_OP;
    i->cjmp_inst.operand1_index = m[e->LHS.lexeme];
    i->cjmp_inst.operand2_index = m[e->RHS.lexeme];
    i->next = parseBody();
    i->cjmp_inst.target = j;
    
    lastI = i; while (lastI->next!=NULL){ lastI = lastI->next; }
    lastI->next = j;

    return i;
}
expr * parseCondition(){
    expr * e = new expr;
    e->LHS = parsePrimary();
    e->aC_OP = parseRelop();
    e->RHS =  parsePrimary();
    return e;
}
ConditionalOperatorType parseRelop(){
    Token t = lexer.peek(1);
    ConditionalOperatorType aC_Op;
    switch (t.token_type)
    {
    case GREATER:
        t = lexer.GetToken();
        aC_Op = CONDITION_GREATER;
        break;
    case LESS:
        t = lexer.GetToken();
        aC_Op = CONDITION_LESS;
        break;
    case NOTEQUAL:
        t = lexer.GetToken();
        aC_Op = CONDITION_NOTEQUAL;
        break;
    default:
        syntax_error(t);
        break;
    }
    return aC_Op;
}
struct InstructionNode * parseSwitchStmt(){
    struct InstructionNode * i;
    struct InstructionNode * switchNoop = new InstructionNode; initInst(switchNoop); switchNoop->type = NOOP;
    Token t;
    expect(SWITCH);
    t = expect(ID);
    expect(LBRACE);
    i = parseCaseList(t,switchNoop);
    struct InstructionNode *lastI = i; while (lastI->next!=NULL){ lastI = lastI->next; }

    t = lexer.peek(1);
    if(t.token_type== DEFAULT){
        lastI->next = parseDefaultCase(t,switchNoop);
        while (lastI->next!=NULL){ lastI = lastI->next; }
        lastI->next = switchNoop;
    }else{lastI->next = switchNoop;}
    
    expect(RBRACE);
    return i;
}
struct InstructionNode * parseForStmt(){
    struct InstructionNode * i;
    struct InstructionNode * c = new InstructionNode; initInst(c);
    struct InstructionNode * i2;
    struct InstructionNode * j = new InstructionNode; initInst(j); j->type = NOOP;
    struct InstructionNode * jmp = new InstructionNode; initInst(jmp); jmp->type = JMP; 
    struct InstructionNode *lastI;

    expect(FOR); 
    expect(LPAREN);
    i = parseAssignStmt(); 
    expr *e = parseCondition(); c->type = CJMP; i->next = c;
    c->cjmp_inst.condition_op = e->aC_OP;
    c->cjmp_inst.operand1_index = m[e->LHS.lexeme];
    c->cjmp_inst.operand2_index = m[e->RHS.lexeme];
    c->cjmp_inst.target = j;
    expect(SEMICOLON);
    i2 = parseAssignStmt(); i2->next = jmp; jmp->jmp_inst.target = c; jmp->next = j;
    expect(RPAREN);
    // i->next = parseBody();
    lastI = i; while (lastI->next!=NULL){ lastI = lastI->next; }
    lastI->next = parseBody();
    while (lastI->next!=NULL){ lastI = lastI->next; }
    lastI->next = i2;
    return i;

    
}
struct InstructionNode *parseCaseList(Token t, struct InstructionNode * switchNoop){ 
    struct InstructionNode * i = parseCase(t, switchNoop);
    struct InstructionNode *lastI = i; while (lastI->next!=NULL){ lastI = lastI->next; }

    Token t2 = lexer.peek(1);
    if(t2.token_type== CASE){
        lastI->next = parseCaseList(t, switchNoop);
    }else{lastI->next = NULL;}

    return i;
}
struct InstructionNode *parseCase(Token t,struct InstructionNode * switchNoop){
    struct InstructionNode * i = new InstructionNode; initInst(i); i->type = CJMP;
    struct InstructionNode * j = new InstructionNode; initInst(j); j->type = JMP; j->jmp_inst.target = switchNoop;
    struct InstructionNode * noop = new InstructionNode; initInst(noop); noop->type = NOOP; // i->cjmp_inst.target = noop;
    i->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
    i->cjmp_inst.operand1_index = m[t.lexeme];
    
    struct InstructionNode *lastI;
    expect(CASE);
    Token t2 = parsePrimary();  /*expect(NUM);*/ i->cjmp_inst.operand2_index = m[t2.lexeme];
    expect(COLON);
    i->cjmp_inst.target = parseBody();
    lastI = i->cjmp_inst.target; while (lastI->next!=NULL){ lastI = lastI->next; }
    lastI->next = j; j->next = noop;
    return i;
}
struct InstructionNode *parseDefaultCase(Token t,struct InstructionNode * switchNoop){
    struct InstructionNode * i;
    expect(DEFAULT);
    expect(COLON);
    i = parseBody();
    // return i;
}
void parseInputs(){
    parseNumList();
}
void parseNumList(){
    Token t = expect(NUM); inputs.push_back(stoi(t.lexeme));
    t = lexer.peek(1);
    if(t.token_type== NUM){
        parseNumList(); 
    }
}
void initInst(struct InstructionNode *i){
    i->next = NULL;
    
}
/*----------------------------PARSER----------------------------*/