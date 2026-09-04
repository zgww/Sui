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

fail = Result()
def succRangeResult(parser:Parser, length: int):
    startPos = parser.pos
    parser.pos += length
    return Result(startPos, parser.pos, parser.code[startPos: parser.pos])

def succResult(parser:Parser, startPos, endPos: int, results: list[Result]=None):
    parser.pos = endPos
    return Result(startPos, endPos, parser.code[startPos: parser.pos], results)

class Rule:
    def __init__(self):
        pass


    def match(self, parser:Parser):
        pass


class CharOpt(Rule):
    def __init__(self, chars: str):
        self.chars = chars

    def match(self, parser:Parser):
        cnt = 0
        i = parser.pos
        while i < len(parser.code):
            c = parser.code[i]
            if c in self.chars:
                i+=1
                continue
            else:
                if i > parser.pos: # succ
                    return succRangeResult(i - parser.pos)
        return fail
                

class CharSeq(Rule):
    def __init__(self, chars: str):
        self.chars = chars

    def match(self, parser:Parser):
        sub = parser.code[parser.pos: parser.pos + len(self.chars)]
        if sub == self.chars:
            return succRangeResult(len(self.chars))
        return fail

class Chain(Rule):
    def __init__(self, *rules: list[Rule]):
        self.rules = rules

    def match(self, parser:Parser):
        startPos = parser.pos
        results = []
        for i, rule in self.rules:
            r = rule.match(parser)
            if r.succ:
                results.append(r)
                pass
            else:
                return fail
        return succResult(startPos, parser.pos, results)

class Opt(Rule):
    def __init__(self, *rules: list[Rule]):
        self.rules = rules

    def match(self, parser:Parser):
        startPos = parser.pos
        results = []
        for i, rule in self.rules:
            r = rule.match(parser)
            if r.succ:
                return succResult(startPos, parser.pos, [r])
        return fail


def test():
    p = Parser('abc')
    r = Chain(
        CharSeq('abc')
    )
    r.match(p)
    pass

if __name__ == '__main__':
    test()