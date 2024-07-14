# 273*(2^2^2^2-5*6*7)*32/(23-12)*1

class Syntax_Err(Exception):
    pass

def parse(list, level):
    operator_add = ('+', '-')
    operator_mul = ('*', '/', '^')
    if (list[0] in operator_mul) or (list[-1] in operator_add) or (list[-1] in operator_mul):
        raise Syntax_Err()

    group = []
    # group_type = []
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
                group.append( parse(list[bracket_start+1 : i], level+1) )
                past_bracket_end = i
    group.extend( list[past_bracket_end+1 :] )
    if bracket_check != 0:
        raise Syntax_Err()

    result = calculate(group[:])

    if len(list) <= 1:
        pass
    elif list == group or group == result:
        print('Level {} :'.format(level), ''.join(list), '=', result[0])
    else:
        print('Level {} :'.format(level), ''.join(list), '=', ''.join(group), '=', result[0])
    return str(result[0])

    '''
    # 문자 타입 분류
    for i in range(len(group)):
        if group[i] in operator_add:
            group_type.append('add')
        elif group[i] in operator_mul:
            group_type.append('mul')
            if i > 0:
                group_type[i] == group_type[i-1]
        else:
            group_type.append('num')

        if (i > 0) and (group_type[i] != 'add') and (group_type[i] == group_type[i-1]):
            raise Syntax_Err()
    '''

def erase(list):
    new_list = []
    for i in range(len(list)):
        if list[i] != '':
            new_list.append(list[i])
    return new_list


def calculate(list):
    for i in range(len(list)):
        j = -i-1
        if list[j] == '^':
            list[j-1] = int(list[j-1]) ** int(list[j+1])
            list[j] = ''
            list[j+1] = ''
    list = erase(list)

    for i in range(len(list)):
        if list[i] == '*':
            list[i+1] = int(list[i-1]) * int(list[i+1])
            list[i] = ''
            list[i-1] = ''
        elif list[i] == '/':
            list[i+1] = int(list[i-1]) / int(list[i+1])
            list[i] = ''
            list[i-1] = ''
    list = erase(list)

    for i in range(len(list)): # 덧셈에 대해선 추가 수정 필요 -5*(...), +-5, --5 오류
        if list[i] == '+':
            list[i+1] = int(list[i-1]) + int(list[i+1])
            list[i] = ''
            list[i-1] = ''
        elif list[i] == '-':
            list[i+1] = int(list[i-1]) - int(list[i+1])
            list[i] = ''
            list[i-1] = ''
    list = erase(list)

    return list


try:
    mark = ('+', '-', '*', '/', '^', '(', ')', ' ') # float는 포함 X

    expression = input('Expression : ')

    for letter in expression:
        if (ord(letter) not in range(48, 58)) and (letter not in mark):
            raise Syntax_Err()

    for letter in mark:
        expression = expression.replace(letter, ' '+letter+' ')

    rearrange = expression.split() # ' ' 제거
    result = parse(rearrange[:], 0)
    print('Answer :', result)

except KeyboardInterrupt:
    print('KeyboardInterrupt Error!')
except EOFError:
    print('\nEOF Error!')
except Syntax_Err:
    print('\nSyntax Error!')
else:
    print('\nNo exception was raised')
