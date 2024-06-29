/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
bool compareStrings(const string& num_str1,const string& num_str2) {
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
bool compareStrings2(const string& num_str1,const string& num_str2) {
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
        return false;
    }
}
UnlimitedInt::UnlimitedInt()
{
    size=0;
    sign=1;
    capacity=1;
    unlimited_int=new int[capacity]();
}

UnlimitedInt::UnlimitedInt(string s)
{
    size=0;
    sign=1;
    capacity = s.length();
    unlimited_int=new int[capacity]();
    int start_index = 0;
    if (s[0] == '-') {
        sign = -1;
        start_index = 1;
    }
    size = s.length() - start_index;
    for (int i = size - 1; i>=0 ; i--) {
        unlimited_int[size-i-1] = s[start_index + i] - '0';
    }
    if(s[0]=='0'){
        sign=-1;
    }


}


UnlimitedInt::UnlimitedInt(int i)
{
    UnlimitedInt(std::to_string(i));
}

UnlimitedInt::~UnlimitedInt()
{
    delete []unlimited_int;
        
}

int UnlimitedInt::get_size()
{
    return size;
}

int *UnlimitedInt::get_array()
{
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->get_sign() == 1 && i2->get_sign() == -1) {
        UnlimitedInt* i2_=new UnlimitedInt(i2->to_string());
        i2_->sign = 1; 
        return sub(i1, i2_);
    } else if (i1->get_sign() == -1 && i2->get_sign() == 1) {
        UnlimitedInt* i1_=new UnlimitedInt(i1->to_string());
        i1_->sign = 1;
        return sub(i2, i1_);
    }
    else{
    UnlimitedInt* result = new UnlimitedInt();
    int carry = 0;
    int max_size = std::max(i1->get_size(), i2->get_size());
    result->sign = i1->get_sign();
    int new_capacity = max_size + 1;
    if (new_capacity > result->capacity) {
        int* new_int = new int[new_capacity]();
        copy(result->unlimited_int, result->unlimited_int + result->size, new_int);
        delete[] result->unlimited_int;
        result->unlimited_int = new_int;
        result->capacity = new_capacity;
    }

    for (int i = 0; i < max_size || carry; i++) {
        int sum = carry;
        if (i < i1->get_size()) {
            sum += i1->get_array()[i];
        }
        if (i < i2->get_size()) {
            sum += i2->get_array()[i];
        }

        result->get_array()[i] = sum % 10;
        carry = sum / 10;
        result->size++;
    }
    while (result->size > 1 && result->get_array()[result->size - 1] == 0) {
        result->size--;
    }

    return result;}
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if(i1->to_string()==i2->to_string()){
        return new UnlimitedInt("0");
    }
    else if(i1->get_sign()==1 && i2->get_sign()==-1){
        UnlimitedInt* i2_=new UnlimitedInt(i2->to_string());
        i2_->sign=1;
        return add(i1,i2_);
    }
    else if(i1->get_sign()==-1 && i2->get_sign()==1){
        UnlimitedInt* i1_=new UnlimitedInt(i1->to_string());
        i1_->sign=1;
        UnlimitedInt* t=add(i1_,i2);
        t->sign=-1;
        return t;    }
    else if(i1->get_sign() == -1 && i2->get_sign() == -1){
        UnlimitedInt* i1_=new UnlimitedInt(i1->to_string());
        UnlimitedInt* i2_=new UnlimitedInt(i2->to_string());
        i1_->sign = 1; 
        i2_->sign = 1;
        return sub(i2_, i1_);
    }
    else if(compareStrings(i2->to_string(),i1->to_string())){
        UnlimitedInt* t=sub(i2,i1);
        t->sign=-1;
        return t;
    }
    else{
    UnlimitedInt* result = new UnlimitedInt();
    int borrow = 0;
    int max_size =max(i1->get_size(), i2->get_size());
    result->sign = i1->get_sign();
    int new_capacity = max_size;
    if (new_capacity > result->capacity) {
        new_capacity = new_capacity;
        int* new_int = new int[new_capacity]();
        copy(result->unlimited_int, result->unlimited_int + result->size, new_int);
        delete [] result->unlimited_int;
        result->unlimited_int = new_int;
        result->capacity = new_capacity;
    }

    for (int i = 0; i < max_size; i++) {
        int diff = borrow + i1->get_array()[i];
        if (i < i2->get_size()) {
            diff -= i2->get_array()[i];
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        result->get_array()[i] = diff;
        result->size++;
    }
    while (result->size > 1 && result->get_array()[result->size - 1] == 0) {
        result->size--;
    }

    return result;
    }

    
}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* result = new UnlimitedInt();
    result->sign = i1->get_sign() * i2->get_sign();
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    int maxSize = size1 + size2 + 1; 
    int new_capacity = maxSize;
    if (new_capacity > result->capacity) {
        new_capacity = new_capacity;
        int* new_int = new int[new_capacity]();
        copy(result->unlimited_int, result->unlimited_int + result->size, new_int);
        delete [] result->unlimited_int;
        result->unlimited_int = new_int;
        result->capacity = new_capacity;
    }
    int intermediate[maxSize] = {0};
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            int product = i1->get_array()[i] * i2->get_array()[j];
            intermediate[i + j] += product;
        }
    }

    int carry = 0;
    for (int i = 0; i < maxSize; i++) {
        int sum = intermediate[i] + carry;
        result->get_array()[i] = sum % 10;
        carry = sum / 10;
    }

    result->size = maxSize;
    while (result->size > 1 && result->get_array()[result->size - 1] == 0) {
        result->size--;
    }
    return result;
}
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
        UnlimitedInt* i10 = new UnlimitedInt(i1->to_string());
        UnlimitedInt* i20 = new UnlimitedInt(i2->to_string());
        i10->sign=1;i20->sign=1;
        int i=i10->get_size()-1;
        int* arr=i10->get_array();
        UnlimitedInt* remainder=new UnlimitedInt("0");
        string ans="";
        int j=0;
        string z=i20->to_string();
        while(i>=0){
            string s1="";
            string s="";
            if(remainder->to_string() != "0"){
             s=""+remainder->to_string();
             }
            while(compareStrings2(z,s) && i>=0){
                if(arr[i]==0){
                    if(s==""){ans+="0";i--;}
                    else{s+=std::to_string(arr[i]);i--;
                        }
                }
                else{s+=std::to_string(arr[i]);i--;
                }
                if(compareStrings2(z,s) && j>0 && i != -1 && s != ""){ans+="0" ;}
                }
            UnlimitedInt* t;
            j++;
            if(s==""){
                 t=new UnlimitedInt("-1");}
            else{
                t=new UnlimitedInt(s);
            }
            int c=-1;
            while(t->sign==1 || t->to_string()=="0"){
                t=sub(t,i20);c++;
            }
            t=add(t,i20);
            remainder=t;
            if(c==-1){
                ans+="";
            }
            else{ans+=std::to_string(c);}
                    }
    delete i10;delete i20;
    if(i1->to_string()=="0"){
        return new UnlimitedInt("0");    }
    else if(i1->to_string()==i2->to_string()){
        return new UnlimitedInt("1");    }
    else if(i1->sign*i2->sign==-1){
            if(remainder->to_string()=="0"){
                UnlimitedInt* t=new UnlimitedInt(ans);t->sign=-1;
                return t;            }
            else{
                UnlimitedInt* t=new UnlimitedInt(ans);t->sign=-1;
                t=sub(t,new UnlimitedInt("1"));
                return t;            }  
        }
    else{
        return new UnlimitedInt(ans);
        }
}
UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt* t=div(i1,i2);
    UnlimitedInt* z=new UnlimitedInt(sub(i1,mul(t,i2))->to_string());
    delete t;
    return z;
}

string UnlimitedInt::to_string()
{
    string result;
    if (size == 1 && unlimited_int[0] == 0) {
        result = "0";
    } else {
        if (sign == -1) {
            result += "-";
        }

        for (int i = size - 1; i >= 0; i--) {
            result += std::to_string(unlimited_int[i]);
        }
    }

    return result;
}
UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
    unlimited_int=ulimited_int;
    sign=sgn;
    size=sz;
    capacity=cap;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}
