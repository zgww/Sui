from lark import Lark

# 使用类似 EBNF 的语法，直接写左递归
grammar = """
    ?expr: expr "+" term -> add
         | expr "-" term -> sub
         | term

    ?term: NUMBER

    %import common.NUMBER
    %import common.WS
    %ignore WS
"""

# 必须指定 parser='earley'，因为 LALR(1) 不支持左递归
parser = Lark(grammar, parser='earley')

tree = parser.parse("10 - 3 - 2")
print(tree.pretty())