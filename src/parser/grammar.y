/*
BSD 3-Clause License

Copyright (c) 2017, expertcompsci
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
%scanner                ../scanner/Scanner.h
%scanner-token-function d_scanner.lex()

%token ALL
%token UNION
%token MATCH
%token CREATE
%token RETURN
%token AS
%token DISTINCT
%token WHERE
%token ORDER
%token BY
%token ASC
%token DESC
%token LIMIT
%token AND
%token OR
%token TRUE
%token FALSE
%token IDENTIFIER
%token FLOAT
%token INTEGER
%token STRING
%token COMMA
%token LEFT_PAREN
%token RIGHT_PAREN
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_CURLY_BRACKET
%token RIGHT_CURLY_BRACKET
%token GE
%token LE
%token EDGE
%token LEFT_EDGE
%token RIGHT_EDGE
%token SHAFT
%token LEFT_ARROW
%token RIGHT_ARROW
%token GT
%token LT
%token NE
%token EQ
%token COLON
%token SEMICOLON
%token DOT
%token ASTERISK
%token OPTIONAL
%token DOLLAR
%token BAR

%print-tokens

%start start_rule

%%

start_rule: cypher;

cypher:
    statement
{ std::cout << " cypher: statement \n"; }
|
    statement SEMICOLON
;

statement: query ;

query:
    regular_query
    { std::cout << "regular_query\n"; }
//|
//    standalone_call
;

regular_query: single_query
// TODO: union
;

single_query:
    single_part_query
//|
//    multi_part_query
;

single_part_query:
    read_only_end
|
    read_update_end
|
    updating_end
;

read_only_end: read_part return;

read_part:
    // empty
|
    reading_clause
;

reading_clause:
    match
|
    reading_clause match
// TODO: Unwind and InQueryCall
;

updating_clause:
    create
|
    updating_clause create
// TODO: merge, delete, set, remove
;

read_update_end:
    reading_clause updating_clause
|
    reading_clause updating_clause return
;

updating_end:
    create
|
// TODO:    merge
|
    create updating_clause opt_return
;

opt_return:
    // empty
|
    return
;

return:
    RETURN return_body
|
    RETURN DISTINCT return_body
;

return_body:
    ASTERISK
|
    expression_list
;

variable: IDENTIFIER;

// TODO: order_by, skip, limit, starts with, contains, not etc.
expression_list:
    expression
|
    expression AS variable
|
    expression_list COMMA expression
|
    expression_list COMMA expression AS variable
;

node_name:
    IDENTIFIER
;

opt_node_name:
    // empty
|
    node_name
;

relationship_name:
    IDENTIFIER
;

opt_relationship_name:
    // empty
|
    relationship_name
;

opt_variable_eq:
    // empty
|
    IDENTIFIER EQ
;

opt_where:
    // empty
|
    WHERE expression
;

match:
    MATCH pattern opt_where
|
    OPTIONAL MATCH pattern opt_where
;

create: CREATE pattern;

pattern:
    opt_variable_eq pattern_element
|
    pattern COMMA opt_variable_eq pattern_element
;

pattern_element:
    node_pattern
|
    node_pattern EDGE pattern_element
|
    node_pattern RIGHT_EDGE pattern_element
|
    node_pattern LEFT_EDGE pattern_element
|
    node_pattern SHAFT relationship_pattern SHAFT pattern_element
|
    node_pattern SHAFT relationship_pattern RIGHT_ARROW pattern_element
|
    node_pattern LEFT_ARROW relationship_pattern SHAFT pattern_element
;

node_pattern:
    LEFT_PAREN opt_node_detail RIGHT_PAREN
;

opt_node_detail:
    // empty
|
    node_detail
;

node_detail:
        opt_node_name opt_map_literal
|
        opt_node_name node_labels opt_map_literal
;

node_labels:
    COLON IDENTIFIER
|
    node_labels COLON IDENTIFIER
;

relationship_pattern:
    relationship_detail
;

relationship_label_pair:
    COLON IDENTIFIER
|
    IDENTIFIER
;

relationship_label: 
    relationship_label_pair
|
    relationship_label BAR relationship_label_pair
;

opt_relationship_label:
    // empty
|
    relationship_label
;

relationship_detail: 
    LEFT_BRACKET 
        opt_relationship_name
        opt_relationship_label 
    RIGHT_BRACKET
;


opt_map_literal:
    // empty
|
    map_literal
;

property_key_name: IDENTIFIER;

property_key_value_pair: property_key_name COLON expression;

property_key_value_pairs:
    property_key_value_pair
|
    property_key_value_pairs COMMA property_key_value_pair
;

map_literal: LEFT_CURLY_BRACKET property_key_value_pairs RIGHT_CURLY_BRACKET;

expression: IDENTIFIER;

//parameter:
//    DOLLAR IDENTIFIER
//|
//    DOLLAR INTEGER
//;
