#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#include "lexer.h"
using namespace std;

LexicalAnalyzer lexer;
void parseProgram();
void parseVarSection();
void parseIDList();
void parseBody();
void parseStmt_list();
void parseStmt();
void parseAssignStmt();
void parseExpr();
void parsePrimary();
void parseOp();
void parseOutputStmt();
void parseInputStmt();
void parseWhileStmt();
void parseIfStmt();
void parseCondition();
void parseRelop();
void parseSwitchStmt();
void parseForStmt();
void parseCaseList();
void parseCase();
void parseDefaultCase();
void parseInputs();
void parseNumList();

struct InstructionNode * parse_generate_intermediate_representation()
{
    parseProgram();
    // Sample program for demonstration purpose only
    // Replace the following with a parser that reads the program from stdin &
    // creates appropriate data structures to be executed by execute_program()
    // This is the imaginary input for the following construction:
    
    // a, b, c, d;
    // {
    //     input a;
    //     input b;
    //     c = 10;
    // 
    //     IF c <> a
    //     {
    //         output b;
    //     }
    // 
    //     IF c > 1
    //     {
    //         a = b + 900;
    //         input d;
    //         IF a > 10
    //         {
    //             output d;
    //         }
    //     }
    // 
    //     d = 0;
    //     WHILE d < 4
    //     {
    //         c = a + d;
    //         IF d > 1
    //         {
    //             output d;
    //         }
    //         d = d + 1;
    //     }
    // }
    // 1 2 3 4 5 6
    
    // // Assigning location for variable "a"
    // int address_a = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for variable "b"
    // int address_b = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for variable "c"
    // int address_c = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for variable "d"
    // int address_d = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for constant 10
    // int address_ten = next_available;
    // mem[next_available] = 10;
    // next_available++;

    // // Assigning location for constant 1
    // int address_one = next_available;
    // mem[next_available] = 1;
    // next_available++;

    // // Assigning location for constant 900
    // int address_ninehundred = next_available;
    // mem[next_available] = 900;
    // next_available++;

    // // Assigning location for constant 3
    // int address_three = next_available;
    // mem[next_available] = 3;
    // next_available++;

    // // Assigning location for constant 0
    // int address_zero = next_available;
    // mem[next_available] = 0;
    // next_available++;

    // // Assigning location for constant 4
    // int address_four = next_available;
    // mem[next_available] = 4;
    // next_available++;

     struct InstructionNode * i1 = new InstructionNode;
    // struct InstructionNode * i2 = new InstructionNode;
    // struct InstructionNode * i3 = new InstructionNode;
    // struct InstructionNode * i4 = new InstructionNode;
    // struct InstructionNode * i5 = new InstructionNode;
    // struct InstructionNode * i6 = new InstructionNode;
    // struct InstructionNode * i7 = new InstructionNode;
    // struct InstructionNode * i8 = new InstructionNode;
    // struct InstructionNode * i9 = new InstructionNode;
    // struct InstructionNode * i10 = new InstructionNode;
    // struct InstructionNode * i11 = new InstructionNode;
    // struct InstructionNode * i12 = new InstructionNode;
    // struct InstructionNode * i13 = new InstructionNode;
    // struct InstructionNode * i14 = new InstructionNode;
    // struct InstructionNode * i15 = new InstructionNode;
    // struct InstructionNode * i16 = new InstructionNode;
    // struct InstructionNode * i17 = new InstructionNode;
    // struct InstructionNode * i18 = new InstructionNode;
    // struct InstructionNode * i19 = new InstructionNode;
    // struct InstructionNode * i20 = new InstructionNode;
    // struct InstructionNode * i21 = new InstructionNode;
    // struct InstructionNode * i22 = new InstructionNode;

    // i1->type = IN;                                      // input a
    // i1->input_inst.var_index = address_a;
    // i1->next = i2;

    // i2->type = IN;                                      // input b
    // i2->input_inst.var_index = address_b;
    // i2->next = i3;

    // i3->type = ASSIGN;                                  // c = 10
    // i3->assign_inst.left_hand_side_index = address_c;
    // i3->assign_inst.op = OPERATOR_NONE;
    // i3->assign_inst.operand1_index = address_ten;
    // i3->next = i4;

    // i4->type = CJMP;                                    // if c <> a
    // i4->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
    // i4->cjmp_inst.operand1_index = address_c;
    // i4->cjmp_inst.operand2_index = address_a;
    // i4->cjmp_inst.target = i6;                          // if not (c <> a) skip forward to NOOP
    // i4->next = i5;

    // i5->type = OUT;                                     // output b
    // i5->output_inst.var_index = address_b;
    // i5->next = i6;

    // i6->type = NOOP;                                    // NOOP after IF
    // i6->next = i7;

    // i7->type = CJMP;                                    // if c > 1
    // i7->cjmp_inst.condition_op = CONDITION_GREATER;
    // i7->cjmp_inst.operand1_index = address_c;
    // i7->cjmp_inst.operand2_index = address_one;
    // i7->cjmp_inst.target = i13;                         // if not (c > 1) skip forward to NOOP (way down)
    // i7->next = i8;

    // i8->type = ASSIGN;                                  // a = b + 900
    // i8->assign_inst.left_hand_side_index = address_a;
    // i8->assign_inst.op = OPERATOR_PLUS;
    // i8->assign_inst.operand1_index = address_b;
    // i8->assign_inst.operand2_index = address_ninehundred;
    // i8->next = i9;

    // i9->type = IN;                                      // input d
    // i9->input_inst.var_index = address_d;
    // i9->next = i10;

    // i10->type = CJMP;                                   // if a > 10
    // i10->cjmp_inst.condition_op = CONDITION_GREATER;
    // i10->cjmp_inst.operand1_index = address_a;
    // i10->cjmp_inst.operand2_index = address_ten;
    // i10->cjmp_inst.target = i12;                        // if not (a > 10) skipp forward to NOOP
    // i10->next = i11;

    // i11->type = OUT;                                    // output d
    // i11->output_inst.var_index = address_d;
    // i11->next = i12;

    // i12->type = NOOP;                                   // NOOP after inner IF
    // i12->next = i13;

    // i13->type = NOOP;                                   // NOOP after outer IF
    // i13->next = i14;

    // i14->type = ASSIGN;                                 // d = 0
    // i14->assign_inst.left_hand_side_index = address_d;
    // i14->assign_inst.op = OPERATOR_NONE;
    // i14->assign_inst.operand1_index = address_zero;
    // i14->next = i15;

    // i15->type = CJMP;                                   // if d < 4
    // i15->cjmp_inst.condition_op = CONDITION_LESS;
    // i15->cjmp_inst.operand1_index = address_d;
    // i15->cjmp_inst.operand2_index = address_four;
    // i15->cjmp_inst.target = i22;                        // if not (d < 4) skip whole WHILE body
    // i15->next = i16;

    // i16->type = ASSIGN;                                 // c = a + d
    // i16->assign_inst.left_hand_side_index = address_c;
    // i16->assign_inst.op = OPERATOR_PLUS;
    // i16->assign_inst.operand1_index = address_a;
    // i16->assign_inst.operand2_index = address_d;
    // i16->next = i17;

    // i17->type = CJMP;                                   // if d > 1
    // i17->cjmp_inst.condition_op = CONDITION_GREATER;
    // i17->cjmp_inst.operand1_index = address_d;
    // i17->cjmp_inst.operand2_index = address_one;
    // i17->cjmp_inst.target = i19;                        // if not (d > 1) skip body of IF
    // i17->next = i18;

    // i18->type = OUT;                                    // output d
    // i18->output_inst.var_index = address_d;
    // i18->next = i19;

    // i19->type = NOOP;                                   // NOOP after body of IF
    // i19->next = i20;

    // i20->type = ASSIGN;                                 // d = d + 1
    // i20->assign_inst.left_hand_side_index = address_d;
    // i20->assign_inst.op = OPERATOR_PLUS;
    // i20->assign_inst.operand1_index = address_d;
    // i20->assign_inst.operand2_index = address_one;
    // i20->next = i21;

    // i21->type = JMP;
    // i21->jmp_inst.target = i15;
    // i21->next = i22;

    // i22->type = NOOP;                                   // NOOP after body of WHILE
    // i22->next = NULL;

    // // Inputs
    // inputs.push_back(1);
    // inputs.push_back(2);
    // inputs.push_back(3);
    // inputs.push_back(4);
    // inputs.push_back(5);
    // inputs.push_back(6);
    // cout << "PASS"<< endl;
    return i1;
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
void parseProgram(){
    parseVarSection();
    parseBody();
    parseInputs();
}
void parseVarSection(){
    parseIDList();
    expect(SEMICOLON);
}
void parseIDList(){
    expect(ID);
    Token t = lexer.peek(1);
    if(t.token_type == COMMA){
        expect(COMMA);
        parseIDList();
    }
}
void parseBody(){
    expect(LBRACE);
    parseStmt_list();
    expect(RBRACE);
}
void parseStmt_list(){
    parseStmt();
    Token t = lexer.peek(1);
    if(t.token_type != RBRACE){
      parseStmt_list();
    }
}
void parseStmt(){
    Token t = lexer.peek(1);
    switch (t.token_type)
    {
    case ID:
        parseAssignStmt();
    break;
    case IF:
        parseIfStmt();
        break;
    case WHILE:
        parseWhileStmt();
        break;
    case SWITCH:
        parseSwitchStmt();
        break;
    case FOR:
        parseForStmt();
        break;
    case INPUT:
        parseInputStmt();
    break;
    case OUTPUT:
        parseOutputStmt();
        break;
    
    default:
        syntax_error(t);
    }
}
void parseAssignStmt(){
    expect(ID);
    expect(EQUAL);
    Token t = lexer.peek(2);
    if(t.token_type==SEMICOLON){
        parsePrimary();
    }else{
        parseExpr();
    }
    expect(SEMICOLON);

}
void parseExpr(){
    parsePrimary();
    parseOp();
    parsePrimary();
}
void parsePrimary(){
    Token t = lexer.peek(1);
    if (t.token_type==ID){  expect(ID); }
    else    {   expect(NUM);    }
}
void parseOp(){
    Token t = lexer.peek(1);
    if(t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT || t.token_type == DIV){
        t = lexer.GetToken();
    }
}
void parseOutputStmt(){
    expect(OUTPUT);
    expect(ID);
    expect(SEMICOLON);
}
void parseInputStmt(){
    expect(INPUT);
    expect(ID);
    expect(SEMICOLON);
}
void parseWhileStmt(){
    expect(WHILE);
    parseCondition();
    parseBody();
}
void parseIfStmt(){
    expect(IF);
    parseCondition();
    parseBody();
}
void parseCondition(){
    parsePrimary();
    parseRelop();
    parsePrimary();
}
void parseRelop(){
    Token t = lexer.peek(1);
    if(t.token_type == GREATER || t.token_type == LESS || t.token_type == NOTEQUAL){
        t = lexer.GetToken();
    }

}
void parseSwitchStmt(){
    expect(SWITCH);
    expect(ID);
    expect(LBRACE);
    parseCaseList();
    Token t = lexer.peek(1);
    if(t.token_type== DEFAULT){
        parseDefaultCase();
    }
    expect(RBRACE);

}
void parseForStmt(){
    expect(FOR);
    expect(LPAREN);
    parseAssignStmt();
    parseCondition();
    expect(SEMICOLON);
    parseAssignStmt();
    expect(RPAREN);
    parseBody();
}
void parseCaseList(){
    parseCase();
    Token t = lexer.peek(1);
    if(t.token_type== CASE){
        parseCaseList();
    }

}
void parseCase(){
    expect(CASE);
    expect(NUM);
    expect(COLON);
    parseBody();
}
void parseDefaultCase(){
    expect(DEFAULT);
    expect(COLON);
    parseBody();
}
void parseInputs(){
    parseNumList();
}
void parseNumList(){
    expect(NUM);
    Token t = lexer.peek(1);
    if(t.token_type== NUM){
        parseNumList(); 
    }
}


/*----------------------------PARSER----------------------------*/