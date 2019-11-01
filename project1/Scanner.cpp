#include "Scanner.h"
#include "Token.h"

//bool get_next_char = false; //gets next char w/o going to new_char_st
Token my_token;                     //scanner token dummy var
scan_st my_scan_st = new_char_st;   //state var starts w/new_char_st
static int line_number = 1;                //current line number
int str_ln;                         //holds str_ln
int cmt_ln;                         //holds comment line
std::ifstream my_file;              //global so other functions can peek at next val
std::vector<Token> token_vect(0); //declare a large vector to hold my tokens
std::string id_string = "";         //keep track of id string
std::string string_string = "";     //keep track of string's string
std::string comment_str = "";       //keep track of comment string
char rc;
/*Scanner::Scanner(std::string fn) {
    filename = fn;
}*/

void Scanner::readFile()
{
    my_file.open(filename);
    if (my_file.is_open())
    {
        //proceed
        while (my_file.peek() != EOF)
        {          
            //figure out a way to output EOF
            rc = my_file.get(); //receive next char
            do
            {
                tokenize();
            } while (my_scan_st != new_char_st);
        }
        rc = my_file.get(); //rc is EOF
        setTokenVals(ENDFILE, "", line_number); //push it onto vec and set data members
    }
    else
    {
        //something went wrong
    }
}

void Scanner::printTokenVector()
{
    int j = token_vect.size();
    for (int i = 0; i < j; i++)
    {
        std::cout << token_vect[i].toString(); //prints out tokens in token_vect
    }
    std::cout << "Total Tokens = " << j; //no newline at end of file

    while (!token_vect.empty())
        token_vect.pop_back(); //empties our token vector
}

void Scanner::setTokenVals(TokenType tok_type, std::string tok_str, int lin_num)
{
    my_token.setTokenType(tok_type);  //sets the token type to tok_type
    my_token.setTokenString(tok_str); //sets the token string to tok_str
    my_token.setLineNum(lin_num);     //sets the line_number to lin_num
    token_vect.push_back(my_token);   //pushes this new token onto the token vector
    //may have a problem with this last line. If so then maybe need to
    // a new token each time this function is called
}

/*
this function allows us to compare the string we have just received
and check to see if it is a keyword or an id
*/
void Scanner::keywordComp()
{
    if (id_string == "Schemes")
    {
        //schemes
        setTokenVals(SCHEMES, id_string, line_number);
    }
    else if (id_string == "Facts")
    {
        //facts
        setTokenVals(FACTS, id_string, line_number);
    }
    else if (id_string == "Rules")
    {
        //rules
        setTokenVals(RULES, id_string, line_number);
    }
    else if (id_string == "Queries")
    {
        //queries
        setTokenVals(QUERIES, id_string, line_number);
    }
    else
    {
        //id
        setTokenVals(ID, id_string, line_number);
    }
    id_string = ""; //reset id_string
    my_scan_st = new_char_st;
}

void Scanner::receivedChar()
{
    //sm #2
    //std::cout << "value of rc in receivedChar: " << rc << std::endl;
    switch (rc)
    {
    case ',':
        my_scan_st = new_char_st; //move to symbol_st
        setTokenVals(COMMA, ",", line_number);
        break;
    case '.':
        my_scan_st = new_char_st; //move to symbol_st
        setTokenVals(PERIOD, ".", line_number);
        break;
    case '?':
        my_scan_st = new_char_st; //move to symbol_st
        setTokenVals(Q_MARK, "?", line_number);
        break;
    case '(':
        my_scan_st = new_char_st; //move to symbol_st
        setTokenVals(LEFT_PAREN, "(", line_number);
        break;
    case ')':
        my_scan_st = new_char_st; //move to symbol_st
        setTokenVals(RIGHT_PAREN, ")", line_number);
        break;
    case '*':
        my_scan_st = new_char_st; //move to symbol_st
        setTokenVals(MULTIPLY, "*", line_number);
        break;
    case '+':
        my_scan_st = new_char_st; //move to symbol_st
        setTokenVals(ADD, "+", line_number);
        break;
    case ':':
        my_scan_st = colon_st; //move to colon_st
        break;
    case '\'':
        //std::cout << "we made it in the string_st" << std::endl;
        //std::cout << "lineNumber: " << line_number << std::endl;
        string_string += rc;
        //std::cout << "current string" << string_string << std::endl;
        str_ln = line_number; //string line should be the line string started on
        my_scan_st = string_st;
        break;
    case '#':
        my_scan_st = comment_st;
        cmt_ln = line_number;
        comment_str += rc;
        break;
    default:
        if (isspace(rc))
        { //whitespace
        //std::cout << "dealing with whitespace\n"; 
        my_scan_st = new_char_st;
        if (rc == '\n')
        {                  //if we get a newline
            line_number++; //inc our line_number
        }                  //thus keeping track of which line we are on
        }
        else if (isalpha(rc))
        {
            my_scan_st = id_st;
            //get_next_char = true; //nvm Idk if I need this
            //treat like an ID
        }
        else
        {
            //undefined
            std::string undef_str = "";
            undef_str += rc;                                 //char to string
            setTokenVals(UNDEFINED, undef_str, line_number); //push the undef char onto our token vect
            //and set it's data members
            my_scan_st = new_char_st;
        }
        break;
    }
}
//pick out the incoming chars and decide what to do with them
void Scanner::tokenize()
{
    char pc;
    //sm #1
    switch (my_scan_st)
    {
    case new_char_st:
        receivedChar(); //function call
        break;
    case id_st:
        //An identifier is a letter followed by zero or more letters or digits, and is not a keyword
        id_string += rc;          //add old rc to string
        pc = my_file.peek(); //look at new incoming char
        if (isalnum(pc))
        {                       //check if it is within id rules
            rc = my_file.get(); //get new char
        }
        else
        { //we have the whole string now comp to our keywords
            //write keyword comparison here
            keywordComp(); //determines what the string really is and pushes the token to the vector
        }
        break;
    case colon_st:
        pc = my_file.peek();
        if (pc == '-')
        {
            my_file.get(); //grabs this token
            setTokenVals(COLON_DASH, ":-", line_number);
        }
        else
        {
            setTokenVals(COLON, ":", line_number);
        }
        my_scan_st = new_char_st; //move onto next_char_st
        break;
    case string_st:
        pc = my_file.peek();
        //std::cout << "in the string_st..." << std::endl;
        if (pc == EOF)
        {
            //undetermined
            setTokenVals(UNDEFINED, string_string, str_ln);
            string_string = ""; //reset string_string
            my_scan_st = new_char_st;
            break;
        }
        //else
        rc = my_file.get(); //get the next char
        if (rc == '\n') {
            line_number++; //inc line number if new line char
            } 
        pc = my_file.peek(); //check the char after rc
        string_string += rc;
        //std::cout << "Our current string: " << string_string << std::endl;
        if ((rc == '\'') & (pc != '\''))
        {
            //std::cout << "we set a string!" << std::endl;
            setTokenVals(STRING, string_string, str_ln);
            string_string = ""; //reset string_string
            my_scan_st = new_char_st;
        }
        else if ((rc == '\'') & (pc == '\'')) {
            rc = my_file.get(); //get the next char
            string_string += rc;
        }
        break;
    case comment_st:
        pc = my_file.peek();
        if ((pc == EOF) | (pc == '\n'))
        { //if next char is eof or \n is encountered
            setTokenVals(COMMENT, comment_str, cmt_ln);
            comment_str = "";         //reset comment_str
            my_scan_st = new_char_st; //go to new_char_st
            break;
        }
        rc = my_file.get();
        comment_str += rc;
        if ((rc == '|') & (comment_str == "#|"))
        { //block comment
            //go to block comment state
            my_scan_st = block_comment_st;
        }
        //else normal comment
        break;
    case block_comment_st:
    //std::cout << "we made it to block_comment!" << std::endl;
        if (my_file.peek() == EOF)
        {
            //undefined
            setTokenVals(UNDEFINED, comment_str, cmt_ln); //set token vals and push to vector
            comment_str = "";                                  //reset comment_str
            my_scan_st = new_char_st;
            break;
        }
        rc = my_file.get();
        comment_str += rc;
        if (rc == '\n') line_number++; //increment line_number
        if ((rc == '|') & (my_file.peek() == '#')) //check to see if the end of a block comment is here
        {
            rc = my_file.get();                     //get the next char
            comment_str += rc;                      //concat with string
            setTokenVals(COMMENT, comment_str, cmt_ln); //push onto token vector
            comment_str = ""; //reset comment_str 
            my_scan_st = new_char_st; //go to new_char_st
        }
        break;
    }
}