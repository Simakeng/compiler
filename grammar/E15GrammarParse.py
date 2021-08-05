
def load_file_for_line(file_name):

    with open(file_name, encoding='UTF-8') as f:
        lines = [line[:-1] if line[-1] == '\n' else line for line in f]

    lines = list(filter(lambda x: x != '', lines))
    return lines


def load_grammar_rules():
    rules = load_file_for_line("SYSY.md")
    rule_id = [i for i in range(len(rules))]
    rule_elements = [line.split('->')[0].strip() for line in rules]
    grammar_tokens = [line.split('->')[1].strip() for line in rules]
    non_terminal_tokens = list(set(rule_elements))
    rules = [
        {
            "element": rule_elements[i],
            "tokens": grammar_tokens[i]
        } for i in rule_id]
    rules = dict(zip(rule_id, rules))
    return rules, non_terminal_tokens


def load_lex_mapping():
    rules = load_file_for_line("LexTokens.md")
    lex_tokens = [line.split('->')[0].strip() for line in rules]
    terminal_tokens = [line.split('->')[1].strip() for line in rules]
    mapping = dict(zip(lex_tokens, terminal_tokens))
    mapping_r = dict(zip(terminal_tokens, lex_tokens))
    return terminal_tokens, mapping, mapping_r


terminal_tokens, mapping, reverse_map = load_lex_mapping()
rules, non_terminal_tokens = load_grammar_rules()

first_set = dict(zip(non_terminal_tokens, [[]
                 for _ in range(len(non_terminal_tokens))]))
follow_set = dict(zip(non_terminal_tokens, [[]
                                            for _ in range(len(non_terminal_tokens))]))

can_ntt_be_null = dict(
    zip(non_terminal_tokens, [False for _ in range(len(non_terminal_tokens))]))


def production_contains_term(non_term_sym, aux=set()):
    '''\
        判断该非终结符的所有产生式是否都包含终结符
    '''
    for rule in rules.values():
        elm = rule["element"]
        tkn = rule["tokens"]

        if(elm != non_term_sym):
            continue

        tokens = tkn.split(' ')
        contains = False
        for token in tokens:
            if((token in terminal_tokens) or (token in aux)):
                contains = True
                break
        if(not contains):
            return False

    return True


def init_be_null():

    to_bfs = set()
    searched = set()

    # 首先筛选出所有可以直接推导成空串的项
    for ntt in non_terminal_tokens:
        for rule in rules.values():

            elm = rule["element"]
            tkn = rule["tokens"]

            if(ntt != elm):
                continue
            tokens = tkn.split(' ')

            if(len(tokens) == 1 and tokens[0] == 'ε'):
                can_ntt_be_null[ntt] = True
                to_bfs.add(ntt)
                break

    # 采用深度优先的方式筛选出所有可以间接单链推导为空串的项
    while len(to_bfs) != 0:
        sntt = to_bfs.pop()
        for rule in rules.values():
            elm = rule["element"]
            tkn = rule["tokens"]
            tokens = tkn.split(' ')
            if(len(tokens) == 1 and tokens[0] == sntt):
                can_ntt_be_null[elm] = True
                if((not elm in searched) and (not elm in to_bfs)):
                    to_bfs.add(elm)
                break
        searched.add(sntt)

    # 筛选出所有产生式都包含终结符的“绝对不会为空的非终结符”
    confirmed_not_null = set()
    for k, v in can_ntt_be_null.items():
        if v == True:
            continue
        if(production_contains_term(k)):
            confirmed_not_null.add(k)

    while True:
        len_before_search = len(confirmed_not_null)
        for k, v in can_ntt_be_null.items():
            if v == True:
                continue
            if(production_contains_term(k, confirmed_not_null)):
                confirmed_not_null.add(k)
        if(len(confirmed_not_null) == len_before_search):
            break

    for k, v in can_ntt_be_null.items():
        if v == True:
            continue
        if(not k in confirmed_not_null):
            raise Exception()

    for k, v in can_ntt_be_null.items():
        if v == False:
            if(not k in confirmed_not_null):
                raise Exception()
    pass


init_be_null()


def can_be_null(ntt, n=0):
    return can_ntt_be_null[ntt]


def get_first(ntt):
    result = []
    for rule_id, rule in rules.items():
        elm = rule["element"]
        tkn = rule["tokens"]
        if(elm != ntt):
            continue

        tokens = tkn.split(' ')
        if(tokens[0] == 'ε'):
            continue

        if(tokens[0] in terminal_tokens):
            result.append(tokens[0])
            continue

        selec_idx = 0
        matched = False
        while selec_idx != len(tokens):
            if(tokens[selec_idx] in non_terminal_tokens):
                matched = True
                result += get_first(tokens[selec_idx])
                if(can_be_null(tokens[selec_idx])):
                    selec_idx += 1
                else:
                    break
            elif(tokens[selec_idx] in terminal_tokens):
                matched = True
                result.append(tokens[selec_idx])
                break
            else:
                break

        if matched:
            continue

        raise Exception()

    return list(set(result))


def get_follow(ntt, n=0):
    # 别问，问就是 if else
    if(n > 20):
        return []

    result = []
    for rule_id, rule in rules.items():
        elm = rule["element"]
        tkn = rule["tokens"]

        tokens = tkn.split(' ')
        if(not ntt in tokens):
            continue

        rule_len = len(tokens)
        idx = tokens.index(ntt)
        
        # 不是该产生式的最后一个
        while (idx + 1 != rule_len):
            if(not tokens[idx + 1] in terminal_tokens):  # 如果下一个符号不是终结符
                result += first_set[tokens[idx + 1]]  # 加上下一个产生式的First集
            else:  # 如果下一个符号是终结符
                result.append(tokens[idx + 1])  # 加入这个终结符
                break  # 终结符不可能为空，直接跳出
            # 判断下一个产生式是否可以为空
            if(can_be_null(tokens[idx + 1])):  # 可以
                idx += 1
            else:  # 不可以
                break

        # 一路判断到了产生式的最后一个
        if(idx + 1 == rule_len):
            # if(elm != ntt and elm != tokens[-1]):  # 特判：防止循环
            if(elm != ntt):  # 特判：防止循环
                # print("find:", ntt, ":", elm, '->', ' '.join(tokens))
                
                result += get_follow(elm, n + 5 if elm == tokens[-1] else n + 1)  # 加上该产生的follow集

    return list(set(result))


print("First集：")
for token in non_terminal_tokens:
    first_set[token] = get_first(token)
    print(token, ':', ' '.join(first_set[token]))
print("\nFollow集：")
for token in non_terminal_tokens:
    if(token == 'LvalAuxOrFuncCall'):
        print('f')
    follow_set[token] = get_follow(token)
    print(token, ':', ' '.join(follow_set[token]))


# 如果产生式以终结符开头，其SELECT集就是该终结符
# 如果产生式非空，该产生式的SELECT集就是开头符号的FIRST集
# 如果产生式为空，该产生式的SELECT集就是该产生式的FOLLOW集
# 如果产生式为一对一的关系，则该产生式的SELECT集就是该开头符号的所有SELECT集的并集

# 产生式的FISRT集为所有可以给该产生式开头的符号的FIRST集
# 产生式的FOLLOW集为所有以该符号结尾的产生式的FOLLOW集
rule_ids = range(len(rules.keys()))


def get_select(rid):
    rule = rules[rid]
    elm = rule['element']
    tokens = rule['tokens'].split(' ')
    result = []

    for token in tokens:
        if(token in terminal_tokens):
            result.append(token)
            return list(set(result))
        elif(token == 'ε'):
            result += follow_set[elm]
        else:
            result += first_set[token]
            if(not can_be_null(token)):
                return list(set(result))  # 退出循环

    result += follow_set[elm]

    return list(set(result))


pass

select_set = dict(zip(rule_ids, [get_select(_) for _ in rule_ids]))


# 生成 Parser.h
def gen_parser_h_file():

    ken_types_enum = []
    ken_types_enum.append('	enum class TokenType')
    ken_types_enum.append('	{')

    for term in terminal_tokens:
        tkn = reverse_map[term]
        ken_types_enum.append(
            f'		{tkn} = __cvt(Compiler::Lex::TokenType::{tkn}),')
        pass

    ken_types_enum.append('	')

    for non_term in non_terminal_tokens:
        ken_types_enum.append(f'		{non_term},')
        pass
    ken_types_enum.append('	')

    ken_types_enum.append(
        f'		Empty,')

    ken_types_enum.append('	};')

    ken_types_enum = '\n'.join(ken_types_enum)

    with open('../Parser.h', encoding="utf-8") as f:
        template = f.read()
    start_label = '// ! Auto Generated Content Start'
    end_label = '// ! Auto Generated Content end'
    start = template.index(start_label) + len(start_label)
    end = template.index(end_label)
    template = template[:start] + '\n' + \
        ken_types_enum + '\n\t' + template[end:]

    with open('../Parser.h', 'w', encoding="utf-8") as f:
        f.write(template)
    pass


gen_parser_h_file()

# 生成 Parser.cpp


def gen_parser_cpp_file():

    token_cnt = len(terminal_tokens) + len(non_terminal_tokens) + 1
    rule_cnt = len(rules.keys())

    prod_rule_matches = []
    for i, rule in rules.items():
        token_list = []
        for token in rule['tokens'].split(' '):
            if token in terminal_tokens:
                token = reverse_map[token]
            if(token == 'ε'):
                token = 'Empty'
            token_list.append(
                '\t\t\tparent->tokenList.push_back(CreateNode(TokenType::' +
                token + ', parent));'
            )
        prod_rule_matches.append(
            '\t\t// ' + rule['element'] + ' -> ' + rule['tokens'] + '\n'
            '\t\tprodRules[' + str(i+1) + '] = [](ASTNode* parent, TokenType inputToken){\n' +
            '\n'.join(token_list) +
            '\n\t\t};\n'
        )

        prod_rule_matches.append('\t\t// Select: ' + ', '.join(select_set[i]))

        elm = rule['element']
        for e in select_set[i]:
            prod_rule_matches.append(
                '\t\tLL1Table[__cvt(TokenType::' + elm + 
                ')][__cvt(TokenType::'+reverse_map[e]+')] = '+ str(i+1)+';')
        prod_rule_matches.append('')

    prod_rule_matches = '\n' .join(prod_rule_matches)

    cvt_list = []

    for term in terminal_tokens:
        tkn = reverse_map[term]
        cvt_list.append(f'\t\tcase __cvt(TokenType::{tkn}): return "[{term}]";')

    cvt_list.append('\t\t')

    for non_term in non_terminal_tokens:
        cvt_list.append(f'\t\tcase __cvt(TokenType::{non_term}): return "[{non_term}]";')
    
    cvt_list.append(f'\t\tcase __cvt(TokenType::Empty): return u8"[ε]";')


    with open('../Parser.cpp', encoding="utf-8") as f:
        template = f.read()
        start_label = '// ! Auto Generated Content Start'
        end_label = '// ! Auto Generated Content end'
        start = template.index(start_label) + len(start_label)
        end = template.index(end_label)
        template = template[:start] + '\n' + '''\
	const auto tokenCount = ''' + str(token_cnt) + ''' ;
	int LL1Table[tokenCount][tokenCount];
	ProductionGenerationFunction prodRules[''' + str(rule_cnt + 1)+ '''];
	int InitLL1()
	{
		for (auto i = 0; i < tokenCount; i++)
			for (auto j = 0; j < tokenCount; j++)
				LL1Table[i][j] = 0;

		prodRules[0] = [](ASTNode* Node, TokenType inputToken) {
			Console::Log("Parser Token error when parsing Node",
				__tstr(Node->type),
				", get",__tstr(inputToken)
				, Level::Error);
			Console::SetExitCode(-1);
		};
		\n''' + prod_rule_matches + '''\
		
		return -1;
	}
	int _ = InitLL1();
	
	const char* const __tstr(int rhs)
	{
		switch(rhs)
		{\n''' + '\n'.join(cvt_list) + '''
		default:
			return "[Unknown]";
		}
	}
    \n\n\t''' + template[end:]

    with open('../Parser.cpp', 'w', encoding="utf-8") as f:
        f.write(template)
    pass


gen_parser_cpp_file()

pass
