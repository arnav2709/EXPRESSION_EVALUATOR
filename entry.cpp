/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry()
{
}

SymEntry::SymEntry(string k, UnlimitedRational *v)
{   
    key=k;
    val=v;
    left=nullptr;
    right=nullptr;

}

SymEntry::~SymEntry()
{
    if(left != nullptr){
        delete left;
        left=nullptr;
    }
    if(right != nullptr){
        delete right ;
        right=nullptr;
    }

   
}
