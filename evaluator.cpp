/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <iostream>
bool containsNonDigits(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return true; 
        }
    }
    return false; 
}
bool isOperator(const string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == ":=");
}
int precedence(const string& op) {
    if (op == ":=") {
        return 3; 
    } else if (op == "*" || op == "/") {
        return 2;
    } else if (op == "+" || op == "-") {
        return 1;
    }
    return 0;
}

vector<string> infixToPostfix(const vector<string>& infix) {
    vector<string> operatorStack;
    vector<string> postfix;
    for (const string& token : infix) {
        if (isOperator(token)) {
            while (!operatorStack.empty() && precedence(token) <= precedence(operatorStack.back())) {
                postfix.push_back(operatorStack.back());
                operatorStack.pop_back();
            }
            operatorStack.push_back(token);
        } else if (token == "(") {
            operatorStack.push_back(token);
        } else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.back() != "(" ) {
                postfix.push_back(operatorStack.back());
                operatorStack.pop_back();
            }
            if (!operatorStack.empty() && operatorStack.back() == "("  ) {
                operatorStack.pop_back();
            }
        } else {
            postfix.push_back(token); 
        }
    }

    while (!operatorStack.empty()) {
        postfix.push_back(operatorStack.back());
        operatorStack.pop_back();
    }

    return postfix;
}

Evaluator::Evaluator()
{
     symtable = new SymbolTable();
}

Evaluator::~Evaluator()
{   
     for(auto i:expr_trees){
        if(i != nullptr){
            delete i;
        }
   } 
     delete symtable;
   
}
void Evaluator::parse(vector<string> code) {
        vector<string> postfix = infixToPostfix(code);
        vector<ExprTreeNode*> nodeVector;
        for (const string& token : postfix) {
            if (token == "+" || token == "-" || token == "*" || token == "/" || token == ":=") {
                ExprTreeNode* operatorNode = new ExprTreeNode();
                if(token==":="){
                    operatorNode->type="UN";
                }
                else if(token=="+"){
                     operatorNode->type="ADD";}
                else if(token=="*"){
                     operatorNode->type="MUL";}
                else if(token=="-"){
                     operatorNode->type="SUB";}
                else if(token=="/"){
                     operatorNode->type="DIV";
                     }
                operatorNode->right = nodeVector.back();
                nodeVector.pop_back();
                operatorNode->left = nodeVector.back();
                nodeVector.pop_back();
                nodeVector.push_back(operatorNode);
            } else {
                ExprTreeNode* operandNode = new ExprTreeNode();
                 if(containsNonDigits(token)){
                    operandNode->type="VAR";
                    operandNode->id=token;
                }
                else{
                    operandNode->type="VAL";
                    operandNode->val=new UnlimitedRational(new UnlimitedInt(token),new UnlimitedInt("1"));
                }
                
                nodeVector.push_back(operandNode);
            }
        }
        if (!nodeVector.empty()) {
            expr_trees.push_back(nodeVector.back());
        }
        
    
}

UnlimitedRational* evaluate(ExprTreeNode* root,SymbolTable*& symtable){
        if(root->type=="UN"){
            root->evaluated_value=evaluate(root->right,symtable);
            symtable->insert(root->left->id, root->evaluated_value);
            return root->evaluated_value;
        }
        else if(root->type == "VAL"){
            root->evaluated_value=root->val;
            return root->val;
        }
        else if(root->type=="VAR"){
            root->evaluated_value=symtable->search(root->id);
            return root->evaluated_value;
            }
        else{
            if(root->type=="ADD"){
                root->evaluated_value=UnlimitedRational::add(evaluate(root->left,symtable),evaluate(root->right,symtable));
            }
            else if(root->type=="SUB"){
                root->evaluated_value=UnlimitedRational::sub(evaluate(root->left,symtable),evaluate(root->right,symtable));
            }
            else if(root->type=="MUL"){
                root->evaluated_value=UnlimitedRational::mul(evaluate(root->left,symtable),evaluate(root->right,symtable));
            }
            if(root->type=="DIV"){
                root->evaluated_value=UnlimitedRational::div(evaluate(root->left,symtable),evaluate(root->right,symtable));
            }
            return root->evaluated_value;

        }
        
    
    }
void Evaluator::eval()
{
    ExprTreeNode* root=expr_trees.back();
    evaluate(root,symtable);
    return ;


}
