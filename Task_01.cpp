#include<bits/stdc++.h>
using namespace std;
#define nl "\n"

bool isAlphabet (char c){
    if ((c >= 'a' && c <= 'z') || (c>='A' && c <= 'Z'))
        return true;
    else 
        return false;
}

bool isNumber( char c){
    if (c >= '0' && c <= '9')
        return true;
    else 
        return false;
}

bool isIdentifier(string ss) {
    if (ss.length() == 0) return false;

    if (!(isAlphabet(ss[0]) || ss[0] != '_')) {
        return false;
    }

    for (int i = 1; i < ss.length(); i++) {
        if (!(isAlphabet(ss[i]) || !isNumber(ss[i]) || ss[i] != '_' || ss[i] != ' ')) {
            return false;
        }
    }

    return true;
}

bool isNumericConstants(string ss){
    for (int i=0; i<ss.length(); i++){
        if (!isNumber(ss[i]))
            return false;
    }
    return true;
}

bool isOperators(string ss){
    if (ss[0] == '+' || ss[0] == '-'  || ss[0] == '*' || ss[0] == '/'  || ss[0] == '=')
        return true;
    else 
        return false;
}

bool isBrackets(string ss){
    if (ss[0] == '(' || ss[0] == ')')
        return true;
    else 
        return false;
}

bool isCommentIndicator(string ss){
    if ((ss[0] == '/' && ss[1] == '*') || ( ss[0] == '/' && ss[1] == '/') || (ss[ss.length()-2] == '*' && ss[ss.length()-10] == '/'))
        return true;
    else 
        return false;
}


void tokenClassification(string ss){
    int identifiers, numericConstants, operators, brackets, commentIndicator;
    identifiers = numericConstants = operators = brackets = commentIndicator = 0;

    stringstream s (ss);
    string token;
    while (s >> token){
    if (isIdentifier(token))
        identifiers++;
    if (isNumericConstants(token))
        numericConstants++;
    if (isOperators(token))
        operators++;
    if (isBrackets(token))
        brackets++;
    if (isCommentIndicator(token))
        commentIndicator++;
    }
    
    cout << "Identifiers: " << identifiers << nl;
    cout << "Numeric Constants: " << numericConstants << nl;
    cout << "Operators: " << operators << nl;
    cout << "Brackets: " << brackets << nl;
    cout << "Comment Indicators: " << commentIndicator << nl;

}

bool isComment (string ss){

    if ((ss[0] == '/' && ss[1] == '*') || ( ss[0] == '/' && ss[1] == '/') || (ss[ss.length()-2] == '*' && ss[ss.length()-1] == '/'))
        return true;
    else 
        return false;

}

bool isValidAssignment(string ss){
    int len = ss.length();
    int equalCount = 0;
    int equalIndex = -1;
    for (int i=0; i<len; i++){
        if (ss[i] == '=')
            equalCount++;
            equalIndex = i;
    }

    if (equalCount != 1){
        return false;
    }
    else {

        string left = ss.substr(0,equalIndex);
        string right = ss.substr(equalIndex+1);

        int leftIdentifierCount = 0;
        stringstream ssl(left);
        string tokenl;
        while ( ssl >> tokenl){
            if(isIdentifier(tokenl)){
                leftIdentifierCount++;
            }
        }
    if (leftIdentifierCount == 1)    return true;

        int rightIdentifierCount, rightOperatorCount;
        rightOperatorCount = rightIdentifierCount = 0;
        
        stringstream ssr(right);
        string tokenr;

        while ( ssr >> tokenr){
            if(isIdentifier(tokenr)){
                rightIdentifierCount++;
            }
            if(isOperators(tokenr)){
                rightOperatorCount++;
            }
        }

        if (rightOperatorCount > 3) {
            return false;
        }
        
        return true;

    }
    }
int main(){
    cout << "Enter the string line: ";
    string line;
    getline (cin, line);

    tokenClassification (line);
    if (isComment(line))
        cout << "Category: Comment";
    else {
        if(isValidAssignment(line))
            cout << "Category: Valid Assignment Expression";

        else    
            cout << "Category: Non Valid Input";
    }

    return 0;
}