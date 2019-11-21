#include "Parser.h"

static int start_n = 0;


//remember to change code so that we don't grab comments
Parser::Parser(vector<Token> tokens)
{
    parser_tokens = tokens;
    vect_pos = 0;
}

Parser::~Parser()
{
}

DatalogProgram Parser::getDatalogProgram() {
    return my_dp;
}

TokenType Parser::peekNextTokenType() {
    Token my_tok = parser_tokens.at(vect_pos);
    return my_tok.getTokenType();
}

void Parser::match(TokenType match_token_type) {
    Token my_token = parser_tokens.at(vect_pos); //token in vector to match with
    if (my_token.getTokenType() != match_token_type) {
        throw my_token; //throw the token that didn't match
    }
    //we matched!
    vect_pos++; //move on to the next token
}

void Parser::parseOperator() {
    if (peekNextTokenType() == ADD) {
        match(ADD);
    }
    else if (peekNextTokenType() == MULTIPLY) {
        match(MULTIPLY);
    }
    else { //failure of follow set
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
}

void Parser::parseExpression() {
    match(LEFT_PAREN);
    parseParameter();
    parseOperator();
    parseParameter();
    match(RIGHT_PAREN);
}

void Parser::parseParameter() {
    if (peekNextTokenType() == STRING) {
        match(STRING);
    }
    else if (peekNextTokenType() == ID) {
        match(ID);
    }
    else if (peekNextTokenType() == LEFT_PAREN) {
        parseExpression();
    }
    else { //failure throw failed token
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
}

void Parser::parseIdList() {
    if (peekNextTokenType() == COMMA) { //first set
        match(COMMA);
        match(ID);
        parseIdList();
    }
    else if (peekNextTokenType() != RIGHT_PAREN){ //doesn't match follow set
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
}

void Parser::parseStringList() {
    if (peekNextTokenType() == COMMA) { //first set
        match(COMMA);
        match(STRING);
        parseStringList();
    }
    else if (peekNextTokenType() != RIGHT_PAREN) { //follow set failed
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
}

void Parser::parseParameterList() {
    if (peekNextTokenType() == COMMA) {
        match(COMMA);
        parseParameter();
        parseParameterList();
    } 
    else if (peekNextTokenType() != RIGHT_PAREN) {
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }  
}

void Parser::parsePredicateList(Rule& my_rule) {
    if (peekNextTokenType() == COMMA) { //first set
        match(COMMA);
        parsePredicate(my_rule);
        parsePredicateList(my_rule);
    }
    else if (peekNextTokenType() != PERIOD) { //follow set failure
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
}


//used for rule
void Parser::parsePredicate(Rule& my_rule) {
    start_n = vect_pos;
    match(ID);
    match(LEFT_PAREN);
    parseParameter();
    parseParameterList();
    match(RIGHT_PAREN);
    Predicate body_predicate = new_pred(body); //creates a new predicate of type scheme
    my_rule.addPredicate(body_predicate);
}

//used for query
void Parser::parsePredicate() {
    start_n = vect_pos;
    match(ID);
    match(LEFT_PAREN);
    parseParameter();
    parseParameterList();
    match(RIGHT_PAREN);
}

void Parser::parseHeadPredicate(Rule& my_rule) {
    //check for matches with terminals
    start_n = vect_pos;
    match(ID);
    match(LEFT_PAREN);
    match(ID);
    parseIdList();
    match(RIGHT_PAREN);
    Predicate head_predicate = new_pred(head); //creates a new predicate of type scheme
    my_rule.addPredicate(head_predicate);
}

void Parser::parseQuery() {
    parsePredicate();
    match(Q_MARK);
    Predicate query_pred = new_pred(Query); //creates a new predicate of type scheme
    my_dp.addQuery(query_pred);//add to datalog vect of schemes here
}

void Parser::parseRule() {
    Rule my_rule;
    parseHeadPredicate(my_rule);
    match(COLON_DASH);
    parsePredicate(my_rule);
    parsePredicateList(my_rule);
    match(PERIOD);
    my_dp.addRule(my_rule);
}

void Parser::parseFact() {
    start_n = vect_pos;
    match(ID);
    match(LEFT_PAREN);
    match(STRING);
    parseStringList();
    match(RIGHT_PAREN);
    match(PERIOD);
    Predicate fact_pred = new_pred(Fact); //creates a new predicate of type scheme
    my_dp.addFact(fact_pred);//add to datalog vect of schemes here
}

void Parser::parseScheme() {
    start_n = vect_pos;
    match(ID);
    match(LEFT_PAREN);
    match(ID);
    parseIdList();
    match(RIGHT_PAREN);
    Predicate scheme_pred = new_pred(Scheme); //creates a new predicate of type scheme
    my_dp.addScheme(scheme_pred);//add to datalog vect of schemes here
    //string my_str = scheme_pred.toString(); //do this for now
    //cout << my_str << endl; //later do it all at end
}

void Parser::parseQueryList() {
    if (peekNextTokenType() == ID)  { //first set
        parseQuery();
        parseQueryList();
    } 
    //this is the last thing to run in the datalogProgram production.
    //there is no next token
    //so I guess instead check to see if the token thing is empty?
    else if (peekNextTokenType() != ENDFILE) {
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
} 

void Parser::parseRuleList() {
    if (peekNextTokenType() == ID) { //first set is headPredicate->ID
        parseRule();
        parseRuleList();
    }
    else if (peekNextTokenType() != QUERIES) { //doesn't match follow set
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
}

void Parser::parseFactList() {
    if (peekNextTokenType() == ID) {
        parseFact();
        parseFactList();
    }
    else if (peekNextTokenType() != RULES) { //doesn't match the follow set
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
}

void Parser::parseSchemeList() {
    if (peekNextTokenType() == ID) {//first set is ID for scheme
        parseScheme();
        parseSchemeList();
    }
    else if (peekNextTokenType() != FACTS) {//doesn't match the follow set
        Token my_token = parser_tokens.at(vect_pos);
        throw my_token;
    }
}


void Parser::parseDatalogProgram() {
    match(SCHEMES);
    match(COLON);
    parseScheme();
    parseSchemeList();
    match(FACTS);
    match(COLON);
    parseFactList();
    match(RULES);
    match(COLON);
    parseRuleList();
    match(QUERIES);
    match(COLON);
    parseQuery();
    parseQueryList();
}

void Parser::parse() {
    try{ //try statement for my parse function
        parseDatalogProgram(); //we are going to try to parse a DP
    }
        catch(Token error_token) {
            std::cout << "Failure!\n";
            return;
        }
    // std::cout << "Success!\n";
    // std::cout << my_dp.toString(); //print out my stuff!
    
}

void Parser::printTokenVector()
{
    int j = parser_tokens.size();
    for (int i = 0; i < j; i++)
    {
        std::cout << parser_tokens[i].toString(); //prints out tokens in token_vect
    }
    std::cout << "Total Tokens = " << j; //no newline at end of file

    while (!parser_tokens.empty())
        parser_tokens.pop_back(); //empties our token vector
}

Predicate Parser::new_pred(predType my_type) {
    std::vector<Token> tok_vec;
    for (int i = start_n; i < vect_pos; i++) {
        tok_vec.push_back(parser_tokens.at(i));
    }
    int length = vect_pos - start_n;
    Predicate my_p(tok_vec, length, my_type);//create a new predicate
    return my_p;
    // and add it to my schemes predicate vector
}