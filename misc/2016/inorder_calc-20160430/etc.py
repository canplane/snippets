mark = ('+', '-', '*', '/', '^', '(', ')', ' ', '.')
a = "2 * ( 6 + ( 12 ^ 5 + 4 * 5 ) + 4 ) - 2.4"
'''
for i in mark:
    print(i)
    a = a.replace(i, '_')
'''
a = a.split()
print(mark[0], mark[-9])

#

def parse(list):
    pass

def bracket(list):
    if (list[0] != '(') or (list[-1] != ')'):
        raise SyntaxError()
    else:
        parse(list[1 : -1]) # 이거 크기가 0이면 오류 반환해야함

def add(list, operand_2, operator):
    pri_op = ('*', '/', '^')
    mark = ('+', '-')

    if list[0][0] == '(' or list[0][-1] == ')':
        operand_1 = bracket(list[1 : -1])
    elif len(list) == 1:
        operand_1 = list[0]
    elif list[-2] in pri_op:
        operand_1 = multiply(list[:-2], list[-2], list[-1])
    else:
        operand_1 = add(list[:-2], list[-2], list[-1])

    if operand_2[0] == '(' or operand_2[-1] == ')':
        operand_2 = bracket(operand_2[1 : -1])

    if operator == '*':
        return int(operand_1) * int(operand_2)
    else:
        return int(operand_1) / int(operand_2)

def multiply(list, operator, operand_2):
    pri_op = ('^')
    mark = ('*', '/')

    if list[0][0] == '(' or list[0][-1] == ')':
        operand_1 = bracket(list[1 : -1])
    elif len(list) == 1:
        operand_1 = list[0]
    elif list[-2] in pri_op:
        operand_1 = power(list[:-2], list[-1])
    else:
        operand_1 = multiply(list[:-2], list[-2], list[-1])

    if operand_2[0] == '(' or operand_2[-1] == ')':
        operand_2 = bracket(operand_2[1 : -1])

    if operator == '*':
        return int(operand_1) * int(operand_2)
    else:
        return int(operand_1) / int(operand_2)


def power(list, operand_2):
    mark = ('^')

    if list[0][0] == '(' or list[0][-1] == ')':
        operand_1 = bracket(list[1 : -1])
    elif len(list) == 1:
        operand_1 = list[0]
    else:
        operand_1 = power(list[:-2], list[-1])

    if operand_2[0] == '(' or operand_2[-1] == ')':
        operand_2 = bracket(operand_2[1 : -1])

    return int(operand_1) ** int(operand_2)

'''


    pri_domain = ['-1', '-1'] # priority 연산자 영역 감지
    for i in len(list):
        if list[i] == '(':
            pri_domain[0] = i
            break
    for i in len(list):
        j = -(i+1) # 마지막부터 세는 것
        if list[j] == ')':
            pri_domain[1] = len(list)+j
    if ((pri_domain[0] < 0) ^ (pri_domain[1] < 0)) or (pri_domain[0] > pri_domain[1]):
        raise SyntaxError()
    elif (pri_domain[0] >= 0) and (pri_domain[1] >= 0):
        addition( list[ pri_domain[0] : pri_domain[1] ] )
    else:
        return int(list) ** int(operand)













            if pri_domain[0] == -1:
                raise SyntaxError()
            else:
                pri_domain[1] = i







    bracket_check = 0
    past_bracket_end = -1
    bracket_start = -1

    # 괄호 처리
    for i in range(len(list)):
        if list[i] == '(':
            if bracket_check == 0:
                bracket_start = i
            bracket_check += 1
        elif list[i] == ')':
            bracket_check -= 1
            if bracket_check == 0:
                group.extend( list[past_bracket_end+1 : bracket_start] )
                group.append( list[bracket_start+1 : i] )
                parse(group[-1])
                past_bracket_end = i
    group.extend( list[past_bracket_end+1 :] )



    for i in len(list):
        if list[-(i+1)] == ')':


        if list[-(i+1)] == '^':
            domain_end = -(i+1)

def bracket(list)

'''