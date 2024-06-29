/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode()
{
        val=nullptr;
        evaluated_value=nullptr;
        left=nullptr;
        right=nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v)
{
   type=t;
    if(type=="VAL"){
        val=new UnlimitedRational(v,new UnlimitedInt(1));
    }
    left=nullptr;
    right=nullptr;
    evaluated_value=nullptr;

}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v)
{
    type=t;
    if(type=="VAL"){
        val=v;
    }
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::~ExprTreeNode()
{   
    if(type != "VAL" && type != "VAR" && type != "UN"){
        if(evaluated_value != nullptr){
            delete evaluated_value;
            evaluated_value=nullptr;
        }
    }
    if(type=="VAL"){
        delete val;
        val=nullptr;
    }
    if(left != nullptr){
        delete left;
        left=nullptr;
    } 
    if(right!=nullptr){
        delete right;
        right=nullptr;
    }
    


}
