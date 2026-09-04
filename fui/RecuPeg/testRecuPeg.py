from arpeggio import ParserPython, visit_parse_tree, PTNodeVisitor

# 1. 定义语法规则 (Python 函数)
# 注意：列表 [] 表示有序选择 (PEG 的 /)

def expression(): 
    # 左递归分支在前，基础分支在后
    return [addition, subtraction, term]

def addition():     
    return expression, '+', term   # 直接左递归

def subtraction():  
    return expression, '-', term   # 直接左递归

def term():         
    return number

def number():       
    return r'\d+'  # 正则匹配数字

# 2. 定义语义动作 (将解析树转换为 AST 或计算结果)
class CalcVisitor(PTNodeVisitor):
    def visit_expression(self, node, children):
        return children[0] # 直接透传
        
    def visit_addition(self, node, children):
        return children[0] + children[2] # left + right
        
    def visit_subtraction(self, node, children):
        return children[0] - children[2] # left - right
        
    def visit_term(self, node, children):
        return children[0]
        
    def visit_number(self, node, children):
        return int(node.value)

# 3. 运行解析
parser = ParserPython(expression)
parse_tree = parser.parse("10 - 3 - 2")

# 4. 访问解析树
result = visit_parse_tree(parse_tree, CalcVisitor())
print(f"计算结果: {result}")  # 输出: 5 (证明了左结合性: (10-3)-2 = 5)