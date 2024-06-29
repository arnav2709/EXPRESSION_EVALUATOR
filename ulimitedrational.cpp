#include "ulimitedrational.h"
bool compareStrings1(const string& num_str1,const string& num_str2) {
    if (num_str1.size() < num_str2.size()) {
        return false; 
    } else if (num_str1.size() > num_str2.size()) {
        return true;  
    } else {
        int z=num_str1.size();
        for (int i = 0; i < z; ++i) {
            if (num_str1[i] < num_str2[i]) {
                return false;
            } else if (num_str1[i] > num_str2[i]) {
                return true;
            }
        }
        return true;
    }
}
UnlimitedInt* gcd(UnlimitedInt* a,UnlimitedInt* b){
    UnlimitedInt* t1=new UnlimitedInt(a->to_string());
    UnlimitedInt* t2=new UnlimitedInt(b->to_string());
    if(a->to_string()=="0" or a->to_string()=="-0" ){
        return b;
    }
    else if(b->to_string()=="0" or b->to_string()=="-0"){
        return a;
    }
    else{
        if(compareStrings1(a->to_string(),b->to_string())){
            UnlimitedInt* t=UnlimitedInt::mod(t1,t2);
            delete t1;delete t2;
            return gcd(t,b); 
        }
        else{
            UnlimitedInt* t=UnlimitedInt::mod(t2,t1);
            delete t1;delete t2;
            return gcd(t,a);
        }

    }
}
UnlimitedRational* simplify(UnlimitedRational* x){
    UnlimitedInt* p=x->get_p();
    UnlimitedInt* q=x->get_q();
    UnlimitedInt* g=gcd(p,q);
    if(g->get_sign()==-1){
        string r=g->to_string().substr(1);
        g=new UnlimitedInt(r);
    }
    return new UnlimitedRational(UnlimitedInt::div(p,g),UnlimitedInt::div(q,g));
}
UnlimitedRational::UnlimitedRational()
{
     p = new UnlimitedInt(0);
    q = new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{   
    UnlimitedInt* g=gcd(num,den);
    if(g->get_sign()==-1){
        string r=g->to_string().substr(1);
        g=new UnlimitedInt(r);
    }
     p=UnlimitedInt::div(num,g);
    q=UnlimitedInt::div(den,g);
}

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{
    return p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return q->to_string();
}

string UnlimitedRational::get_frac_str()
{
    return p->to_string() + "/" + q->to_string();
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt* nume1=UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt* nume2=UnlimitedInt::mul(i2->get_p(),i1->get_q());
    UnlimitedInt* denominator=UnlimitedInt::mul(i1->get_q(),i2->get_q());
    return simplify(new UnlimitedRational(UnlimitedInt::add(nume1,nume2),denominator));
        
}

UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt* nume1=UnlimitedInt::mul(i1->get_p(),i2->get_q());
    UnlimitedInt* nume2=UnlimitedInt::mul(i2->get_p(),i1->get_q());
    UnlimitedInt* denominator=UnlimitedInt::mul(i1->get_q(),i2->get_q());
    return simplify(new UnlimitedRational(UnlimitedInt::sub(nume1,nume2),denominator));

    
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt* numerator=UnlimitedInt::mul(i1->get_p(),i2->get_p());
    UnlimitedInt* denominator=UnlimitedInt::mul(i1->get_q(),i2->get_q());
    return simplify(new UnlimitedRational(numerator,denominator));
}

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if(i2->get_p_str()=="0" or i2->get_p_str()=="-0"){
        return new UnlimitedRational(new UnlimitedInt(0),new UnlimitedInt(0));
    }
    else{
        UnlimitedInt* numerator=UnlimitedInt::mul(i1->get_p(),i2->get_q());
        UnlimitedInt* denominator=UnlimitedInt::mul(i1->get_q(),i2->get_p());
        return simplify(new UnlimitedRational(numerator,denominator));
    }
    
    
}