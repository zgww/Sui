// RecuPeg.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <format>
#include <string>
#include <memory>

namespace RecuPeg {


class Result {
public:
    bool succ = false;
    //左闭右开
    int startPos = -1;
    int endPos = -1;
    std::string str;

    
};

using PtrResult = std::shared_ptr<Result>;

class Parser {
public:
    std::string str;
    int pos = 0;
    std::unordered_map<std::string, PtrResult> memo;

    std::shared_ptr<Result> mkFail() {
        auto r = std::make_shared<Result>();
        return r;
    }
    std::shared_ptr<Result> mkSucc(int startPos, int endPos) {
        auto r = std::make_shared<Result>();
        r->startPos = startPos;
        r->endPos = endPos;
        r->str = str.substr(startPos, endPos - startPos);
        return r;
    }
    bool isEnd() {
        return pos >= str.size();
    }

    //所有的many，any, chain, option都需要配合for使用
    /*
    for (auto c = many(0, 10); c.cond(); c.next()){
        auto r = charOpt("0123456789");

        for (auto d = options(); c.cond(); c.next()){
            key("function");  if (d.feed()) continue;
            blanks(); if (d.feed()) continue;
            number(); if (d.feed()) continue;
            blanks if (d.feed()) continue;
            id(); if (d.feed()) continue;
            blanks(); if (d.feed()) continue;
            argsDecl(); if (d.feed()) continue;
        }

        for (auto d = chain(); c.cond(); c.next()){
            key("function");
            blanks();
            number();
            blanks();
            id();
            blanks();
            argsDecl();
        }
    }

    many(
        0, 10, 
        charOpt("0123456789"),
        options(
            key("function"),
            blanks(),
            number(),
            blanks(),
            id()
            blanks(),
            argsDecl(),
        ),
    )
    "Expr": LeftRecu(
        rule("Expr"),
        blanks(),
        many(1, infinity,
            char("+"),
            blanks(),
            rule("Expr")
        )
    )
    
    */
    PtrResult many() {
        return nullptr;
    }

    PtrResult charOpt(const char* seq) {
        int startPos = pos;
        int len = strlen(seq);

        for (int i = pos; i < str.size(); i++) {
            auto matched = false;
            for (int j = 0; j < len; j++) {
                if (str[i] == seq[i]) { 
                    matched = true;
                }
            }
            if (!matched) { 
                if (i > pos) { //说明有匹配一些
                    pos = i;
                    return mkSucc(pos, i);
                }
                break;
            }
            else {
                if (i == str.size()) {
                    pos = i;
                    return mkSucc(pos, i);
                }
            }
        }

        pos = startPos;
        return mkFail();
    }
    PtrResult charSeq(const char *seq) {
        int startPos = pos;
        int len = strlen(seq);

        for (int i = 0, strSize = str.size(); i < len && pos + i < strSize; i++) {
            if (str[i + pos] != seq[i]) { //直到失败
                break;
            }
            if (i == len - 1) { //匹配成功
                pos = pos + len;
                return mkSucc(startPos, pos);
            }
        }
        pos = startPos;
        return mkFail();
    }

    PtrResult leftRecu(std::string ruleName, std::function<std::shared_ptr<Result> ()> ruleFn) {
        int startPos = pos;
        auto key = std::format("{}_{}", ruleName, pos);
        //说明在递归
        if (memo.contains(key)) {
            auto result = memo[key];
            return result;
        }
        //种子
        //std::vector<std::shared_ptr<Result>> results;
        auto seed = std::make_shared<Result>();
        memo[key] = seed;
        std::shared_ptr<Result> prevResult = seed;

        //results.push_back(seed);

        //迭代，直到失败
        while (!isEnd()) {
            int itStartPos = pos;
            auto result = ruleFn();
            pos = itStartPos;
            if (result->succ){
                prevResult = memo[key];
                memo[key] = result;
                //results.push_back(result);
            }
            else {
                //因为外面还有一次的expr, 所以最后一次的成功，也要pop掉
                //这样的话，外面会多执行一次expr
                //results.pop_back();
                break;
            }
        }
        //倒2的result
        //auto size = results.size();
        //auto result2 = size > 0 ? results[size - 1] : seed;
        //memo[key] = result2;
        //return result2;
        //memo[key] = prevResult;
        //return prevResult;
        auto ret = memo[key];
        if (ret->succ) {
            pos = ret->endPos;
        }
        else {
            pos = startPos;
        }
        return ret;
    }
};

}

using namespace RecuPeg;
int main()
{
    std::cout << "Hello World!\n";
    Parser p;
    p.str = "aabd";
    auto result = p.charSeq("aab");
    printf("result:%d\n", result->succ);
}
