def bracket(word, level): # parse 구현 X

    group = []
    # Parse
    return add(group, level) # --> 메인으로 보냄

def add(group, level):
    operator_set = ('+', '-')
    pri_operator = ('*', '/', '^')

    group_out = []

    for i in range(len(group)):
        if group[i][0] == '(' and group[i][-1] == ')':
            group[i] = bracket(group[i][1:-1], level+1)

    prior_start = 0
    past_prior_end = 0
    prior_count = 0
    for i in range(len(group)):
        if group[i] in pri_operator and prior_count == 0:
            prior_count = 1
            prior_start = i-1
        elif group[i] in operator_set and prior_count != 0:
            prior_count = 0
            group_out.extend( group[past_prior_end : prior_start] )
            group_out.append( multiply(group[prior_start : i], level+1) )
            past_prior_end = i
    if prior_count == 1:
        group_out.extend( multiply(group[prior_start :], level+1) )

    if len(group_out) == 1:
        return int(group_out)
    elif len(group_out) == 2:
        if group_out == '-':
            return -int(group_out)
        else:
            return int(group_out)

    elif group_out[-2] == '+':
        return int(add(group_out[:-2])) + group_out[-1]
    else:
        return int(add(group_out[:-2])) - group_out[-1]


def multiply(group, level):
    pass

def power():
    pass