#include "Lab_2.h"
#include "Fabric.h"


void pop_cmd::execute(Param& p) {
    if (!p.stk.empty()) {
        p.stk.pop();
    }
    else {
        throw EmptyStack();
    }
};

void push_cmd::execute(Param& p) {
    if (integer_check(p) && p.vst.size() >= 2) {
        SafeInt<int64_t> number = SafeInt<int64_t>::SafeAtoI(p.vst[1].c_str());
        p.stk.push(int64_t(number));
    }
    else {
        if (p.var.count(p.vst[1])) {
            p.stk.push(p.var[p.vst[1]]);
        }
        else {
            throw VarNotFound();
        }

    }
};

void peek_cmd::execute(Param& p) {
    if (!p.stk.empty() && p.vst.size() >= 2) {
        p.var[p.vst[1]] = p.stk.top();
    }
    else if (p.stk.empty()) {
        throw EmptyStack();
    }
    else {
        throw ArgNotEntered();
    }
};

void abs_cmd::execute(Param& p) {
    if (!p.stk.empty()) {
        SafeInt<int64_t, IntOverflow> val1(p.stk.top());
        p.stk.pop();
        if (val >= 0) {
            p.stk.push(val1);
        }
        else {
            SafeInt<int64_t, IntOverflow> res = -val1;
            p.stk.push(res);
            
        }
    }
    else {
        throw EmptyStack();
    }
};

void plus_cmd::execute(Param& p)
{

    if (!p.stk.empty()) {
        SafeInt<int64_t, IntOverflow> val1(p.stk.top());
        p.stk.pop();
        if (!p.stk.empty()) {
            SafeInt<int64_t, IntOverflow> val2(p.stk.top());
            p.stk.pop();
            p.stk.push(val1 + val2);
        }
        else {
            p.stk.push(val1);
            throw OneArgumentStack();
        }
    }
    else {
        throw EmptyStack();
    }
};

void mul_cmd::execute(Param& p)
{

    if (!p.stk.empty()) {

        SafeInt<int64_t, IntOverflow> val1(p.stk.top());
        p.stk.pop();
        if (!p.stk.empty()) {
            SafeInt<int64_t, IntOverflow> val2(p.stk.top());
            p.stk.pop();
            p.stk.push(val1 * val2);
        }
        else {
            p.stk.push(val1);
            throw OneArgumentStack();
        }
    }
    else {
        throw EmptyStack();
    }
};
void minus_cmd::execute(Param& p) {

    if (!p.stk.empty()) {
        SafeInt<int64_t, IntOverflow> val1(p.stk.top());
        p.stk.pop();
        if (!p.stk.empty()) {
            SafeInt<int64_t, IntOverflow> val2(p.stk.top());
            p.stk.pop();
            p.stk.push(val2 - val1);
        }
        else {
            p.stk.push(val1);
            throw OneArgumentStack();
        }
    }
    else {
        throw EmptyStack();
    }
};

void div_cmd::execute(Param& p) {

    if (!p.stk.empty()) {
        SafeInt<int64_t, IntOverflow> val1(p.stk.top());
        p.stk.pop();
        int64_t result = 0;
        if (!p.stk.empty() && val1 != 0) {
            SafeInt<int64_t, IntOverflow> val2(p.stk.top());
            p.stk.pop();
            SafeDivide(val2, val1, result);
            p.stk.push(result);
        }
        else if (p.stk.top() == 0) {
            throw divByZero();
        }
        else {
            p.stk.push(val1);
            throw OneArgumentStack();
        }
    }
    else {
        throw EmptyStack();
    }

};


void print_cmd::execute(Param& p) {
    if (!p.stk.empty()) {
        std::cout << int64_t(p.stk.top()) << endl;
    }
    else {
        throw EmptyStack();
    }
};

void read_cmd::execute(Param& p) {
    int64_t i = 0;
    SafeInt<int64_t, IntOverflow> enterval(i);
    cin >> i;
    p.stk.push(i);
};
