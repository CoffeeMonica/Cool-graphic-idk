#ifndef POLAND_H
#define POLAND_H

#endif // POLAND_H

#include <string>
#include <cmath>
#include <QString>
//#include <iostream>

using namespace std;

typedef long double ld;

struct Stack {
    char sim;
    ld num;
    Stack* pointer;
};

QString rez = "";

Stack* pointer = nullptr;

void Push(Stack*& t, ld n, char s) {
    Stack* p = new Stack;
    (*p).sim = s;
    (*p).num = n;
    (*p).pointer = t;
    t = p;
}

void Pop(Stack*& t) {
    t = (*t).pointer;
}

void Clear(Stack*& t) {
    while (t != nullptr) {
        Pop(t);
    }
}

Stack Top(Stack*& t) {
    Stack st;
    st.num = (*t).num;
    st.sim = (*t).sim;
    return st;
}

void goStack(Stack*& tl, Stack*& tr, char op) {
    ld a = Top(tl).num;
    Pop(tl);
    if (op == 'S') {
        Push(tl, sin(a), '@');
        return;
    }
    if (op == 'C') {
        Push(tl, cos(a), '@');
        return;
    }
    if (op == 'T') {
        if (cos(a) == 0) {
            rez = "Error";
            return;
        }
        Push(tl, tan(a), '@');
        return;
    }
    if (op == 'Q') {
        if (a < 0) {
            rez = "Error";
            return;
        }
        Push(tl, sqrt(a), '@');
        return;
    }
    if (op == 'L') {
        if (a < 0) {
            rez = "Error";
            return;
        }
        Push(tl, log(a), '@');
        return;
    }
    ld b = Top(tl).num;
    //cout << a << ' ' << op << ' ' << b << '\n';
    Pop(tl);
    if (op == '+')
        Push(tl, a + b, '@');
    if (op == '-')
        Push(tl, b - a, '@');
    if (op == '*')
        Push(tl, a * b, '@');
    if (op == '/') {
        if (a == 0) {
            rez = "Error";
            return;
        } else {
            Push(tl, b / a, '@');
        }
    }
    if (op == '^') {
        Push(tl, pow(b, a), '@');
    }
}

int priority(char s) {
    if (s == '(')
        return 0;
    if (s == '+' || s == '-')
        return 1;
    if (s == '*' || s == '/')
        return 2;
    if (s == '^')
        return 3;
    if (s == 'L' || s == 'S' || s == 'C' || s == 'T' || s == 'Q')
        return 4;
    return -1;
}

bool isOpper(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return true;
    if (ch == 'L' || ch == 'S' || ch == 'C' || ch == 'T' || ch == 'Q')
        return true;
    return false;
}

bool Check(string s) {
    if (isOpper(s[0]) == true && priority(s[0]) < 4)
        return false;
    int len = s.size() - 1;
    if (isOpper(s[len]) == true)
        return false;
    for (int i = 0; i < len; i++) {
        if (s[i] == ')' && s[i + 1] == '(')
            return false;
        if (s[i] == '(' && s[i + 1] == ')')
            return false;
        if (s[i] == '(' && isOpper(s[i + 1]) == true && priority(s[i + 1]) < 4)
            return false;
        if (s[i + 1] == '(' && (isOpper(s[i]) == false && s[i] != '('))
            return false;
        if (s[i + 1] == ')' && (isOpper(s[i]) == true && s[i] != ')'))
            return false;
        if (s[i] == ')' && s[i + 1] >= '0' && s[i + 1] <= '9')
            return false;
        if (isOpper(s[i]) == true && isOpper(s[i + 1]) == true && priority(s[i + 1]) < 4)
            return false;
        if (s[i] >= '0' && s[i] <= '9' && priority(s[i + 1]) == 4)
            return false;
    }
    return true;
}

bool psp(string s) {
    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ')')
            cnt--;
        if (s[i] == '(')
            cnt++;
        if (cnt < 0)
            return false;
    }
    if (cnt != 0)
        return false;
    else
        return true;
}

Stack* sl = nullptr;
Stack* sr = nullptr;

QString culc(string ss, string x) {
    Clear(pointer);
    Clear(sl);
    Clear(sr);
    pointer = nullptr;
    rez = "";
    string s = "";
    for (int i = 0; i < ss.size(); i++) {
        if (ss[i] == ' ')
            continue;
        if (ss[i] == 'x') {
            s += '(';
            if (x[0] == '-') {
                s += '0';
            }
            s += x;
            s += ')';
            continue;
        }
        if (ss[i] == '-') {
            if (i == 0 || ss[i - 1] == '(') {
                s += "0-";
                continue;
            }
        }
        if (ss[i] == 's' && i + 1 < ss.size() && ss[i + 1] == 'i' && i + 2 < ss.size() && ss[i + 2] == 'n') {
            s += 'S';
            i += 2;
            continue;
        }
        if (ss[i] == 'c' && i + 1 && ss[i + 1] == 'o' && i + 2 < ss.size() && ss[i + 2] == 's') {
            s += 'C';
            i += 2;
            continue;
        }
        if (ss[i] == 's' && i + 1 && ss[i + 1] == 'q'  && i + 2 < ss.size() && ss[i + 2] == 'r'  && i + 3 < ss.size() && ss[i + 3] == 't') {
            s += 'Q';
            i += 3;
            continue;
        }
        if (ss[i] == 'l' && i + 1 && ss[i + 1] == 'n' ) {
            s += 'L';
            i += 1;
            continue;
        }
        if (ss[i] == 't' && i + 1 && ss[i + 1] == 'g') {
            s += 'T';
            i += 1;
            continue;
        }
        s += ss[i];
    }
    if (psp(s) == false) {
        rez = "Error";
        return rez;
    }
    if (Check(s) == false) {
        rez = "Error";
        return rez;
    }
    for (int i = 0; i < s.size(); i++) {
        if (s[i] > '9' || s[i] < '0') {
            if (s[i] == '(') {
                Push(sr, 0.0, s[i]);
                continue;
            }
            if (s[i] == ')') {
                while (Top(sr).sim != '(') {
                    goStack(sl, sr, Top(sr).sim);
                    Pop(sr);
                }
                Pop(sr);
                continue;
            }
            if (priority(s[i]) == -1) {
                rez = "Error";
                return rez;
            }
            if (sr == nullptr) {
                Push(sr, 0.0, s[i]);
                continue;
            }
            int a = priority(s[i]);
            int b = priority(Top(sr).sim);
            if (a <= b) {
                while (a <= b && sr != nullptr) {
                    goStack(sl, sr, Top(sr).sim);
                    if (rez == "Error") {
                        return rez;
                    }
                    Pop(sr);
                    if (sr == nullptr)
                        break;
                    b = priority(Top(sr).sim);
                }
                Push(sr, 0.0, s[i]);
            } else {
                Push(sr, 0.0, s[i]);
            }
        } else {
            //ld ans = s[i] - '0';
            string ans;
            ans += s[i];
            int l = 0;
            bool isDouble = false;
            int k = 1;
            for (int j = i + 1; j < s.size(); j++) {
                if (s[j] > '9' || s[j] < '0' && s[j] != '.')
                    break;
                l++;
                if (s[j] == '.') {
                    if (isDouble == true) {
                        rez = "Error";
                        return "Error";
                    }
                    isDouble = true;
                    //continue;
                }
                ans += s[j];
                /*
                if (isld == true) {
                    ld asdf = s[j] - '0';
                    ans += asdf / (10 * k);
                    k++;
                } else {
                    ld asdf = s[j] - '0';
                    ans *= 10;
                    ans += asdf;
                }
                */
            }
            i += l;
            if(ans[ans.size() - 1] == '.') {
                rez = "Error";
                return rez;
            }
            Push(sl, stold(ans), '@');
        }
    }
    while (sr != nullptr) {
        goStack(sl, sr, Top(sr).sim);
        if (rez == "Error") {
            return rez;
        }
        Pop(sr);
    }
    if (rez != "Error") {
        rez = QString::number(Top(sl).num, 'f', 6);
    }
    return rez;
}
