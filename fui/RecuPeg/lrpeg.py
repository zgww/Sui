import os

class Parser:
    def __init__(self, code):
        self.code = code
        self.pos = 0

    def isEnd(self):
        return self.pos >= len(self.code)


class Result:
    def __init__(self, startPos=-1, endPos =-1, value='', results: list['Result']=None):
        self.succ = False
        self.startPos = startPos
        self.endPos = endPos
        self.value = value
        self.results: list['Result'] = results or []

    def __repr__(self):
        return f'Result({self.succ}, {self.startPos}, {self.endPos}, {self.value}, \n{self.results})'

fail = Result()
def succRangeResult(parser:Parser, length: int):
    startPos = parser.pos
    parser.pos += length
    r = Result(startPos, parser.pos, parser.code[startPos: parser.pos])
    r.succ = True
    return r

def succResult(parser:Parser, startPos, endPos: int, results: list[Result]=None):
    parser.pos = endPos
    r = Result(startPos, endPos, parser.code[startPos: parser.pos], results)
    r.succ = True
    return r

class Rule:
    def __init__(self):
        pass


    def match(self, parser:Parser):
        pass


class Empty(Rule):
    def match(self, parser:Parser):
        return succRangeResult(parser, 0)

class Many(Rule):
    def __init__(self, minTimes: int=0, *rules: list[Rule]):
        self.minTimes = minTimes
        self.rules = rules

    def match(self, parser:Parser):
        startPos = parser.pos
        times = 0
        results = []
        while not parser.isEnd():
            passSucc = True
            passStartPos = parser.pos
            passResults = []
            for i, rule in enumerate(self.rules):
                r = rule.match(parser)
                if r.succ:
                    passResults.append(r)
                else:
                    passSucc = False
                    break
            if passSucc:
                results.append(*passResults)
                times += 1
                pass
            else:
                parser.pos = passStartPos
                break
        if times >= self.minTimes:
            return succResult(parser, startPos, parser.pos, results)
        return fail
            



class CharOpt(Rule):
    def __init__(self, chars: str, minTimes=0):
        self.chars = chars
        self.minTimes = minTimes

    def match(self, parser:Parser):
        startPos = parser.pos
        cnt = 0
        i = parser.pos
        while i < len(parser.code):
            c = parser.code[i]
            if c in self.chars:
                cnt+=1
                i+=1
                if i == len(parser.code):
                    if cnt < self.minTimes:
                        break
                    return succRangeResult(parser, i - parser.pos)
            else:
                if i > parser.pos: # succ
                    if cnt < self.minTimes:
                        break
                    return succRangeResult(parser, i - parser.pos)
                else:
                    break

        parser.pos = startPos
        return fail
                

class CharSeq(Rule):
    def __init__(self, chars: str):
        self.chars = chars

    def match(self, parser:Parser):
        startPos = parser.pos
        sub = parser.code[parser.pos: parser.pos + len(self.chars)]
        if sub == self.chars:
            return succRangeResult(parser, len(self.chars))
        parser.pos = startPos
        return fail

class Chain(Rule):
    def __init__(self, *rules: list[Rule]):
        print('Chain rule', rules)
        self.rules = rules

    def match(self, parser:Parser):
        startPos = parser.pos
        results = []
        print('rules', self.rules, type(self.rules))
        for i, rule in enumerate(self.rules):
            r = rule.match(parser)
            if r.succ:
                results.append(r)
            else:
                return fail
        return succResult(parser, startPos, parser.pos, results)

class Opt(Rule):
    def __init__(self, *rules: list[Rule]):
        self.rules = rules

    def match(self, parser:Parser):
        startPos = parser.pos
        results = []
        for i, rule in enumerate(self.rules):
            r = rule.match(parser)
            if r.succ:
                return succResult(parser, startPos, parser.pos, [r])
        return fail

def blanks(min=0):
    return Many(
        min,
        CharOpt(' \t\f\r\n'),
    )

def may(*rules:list[Rule]):
    return Opt(
        Chain(*rules),
        Empty(),
    )

def ruleNumber():
    return Chain(
        Opt(
            CharOpt('-'),
            Empty(),
        ),
        blanks(),
        CharOpt('0123456789', 1),
        may(
            CharSeq('.'),
            CharOpt('0123456789', 1)
        )
    )

def test():
    p = Parser('123.45')
    # r = Chain(
    #     CharSeq('abc')
    # )
    # result = r.match(p)
    result = ruleNumber().match(p)
    print('result', result)
    pass

if __name__ == '__main__':
    test()