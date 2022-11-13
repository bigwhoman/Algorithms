def find_steps(num_list):
    if len(num_list) == 0:
        return 0
    elif len(num_list) == 1:
        if num_list[0] <= 0:
            return 0
        else:
            return 1
    else:
        answer = 0
        one_is_there = False
        if 1 in num_list:
            num_list = list(map(lambda x: x - 1, num_list))
            answer += 1
            one_is_there = True
        for k in range(len(num_list)):
            l = len(num_list)
            if len(num_list) == 1:
                if num_list == [0]:
                    return answer
                else:
                    return answer + 1
            moo = []
            for t in range(l):
                if t == 0 and num_list[t] > num_list[t + 1]:
                    moo.append(t)
                    answer += 1
                elif t == len(num_list) - 1:
                    if num_list[t] > num_list[t - 1]:
                        moo.append(t)
                        answer += 1
                else:
                    if num_list[t] > num_list[t - 1] and num_list[t] > num_list[t + 1]:
                        moo.append(t)
                        answer += 1
            if len(moo) == 0:
                break
            num_list = [i for j, i in enumerate(num_list) if j not in moo]
        if not one_is_there:
            max_num = max(num_list)
            min_num = min(num_list)
            if max_num < len(num_list):
                zero_indexes = [i for i, val in enumerate(num_list) if val == min_num]
                if len(zero_indexes) > 0:
                    new_list = []
                for i in range(len(zero_indexes)):
                    if i == 0:
                        new_list.append(num_list[:zero_indexes[i]])
                        if len(zero_indexes) > 1:
                            new_list.append(num_list[zero_indexes[i] + 1:zero_indexes[i + 1]])
                        else:
                            new_list.append(num_list[zero_indexes[i] + 1:])
                    elif i == len(zero_indexes) - 1:
                        new_list.append(num_list[zero_indexes[i] + 1:])
                    else:
                        new_list.append(num_list[zero_indexes[i] + 1:zero_indexes[i + 1]])
                new_list = list(filter(lambda a: a != [], new_list))
                answer1 = answer
                for number_list in new_list:
                    answer1 += find_steps(list(map(lambda a: a - min_num, number_list)))
                answer1 += min_num
                answer2 = answer + len(num_list)
                return min(answer1, answer2)
            else:
                while max_num in num_list:
                    num_list.remove(max_num)
                    answer += 1
        new_list = [num_list]
        zero_indexes = [i for i, val in enumerate(num_list) if val == 0]
        if len(zero_indexes) > 0:
            new_list = []
        for i in range(len(zero_indexes)):
            if i == 0:
                new_list.append(num_list[:zero_indexes[i]])
                if len(zero_indexes) > 1:
                    new_list.append(num_list[zero_indexes[i] + 1:zero_indexes[i + 1]])
                else:
                    new_list.append(num_list[zero_indexes[i] + 1:])
            elif i == len(zero_indexes) - 1:
                new_list.append(num_list[zero_indexes[i] + 1:])
            else:
                new_list.append(num_list[zero_indexes[i] + 1:zero_indexes[i + 1]])
        new_list = list(filter(lambda a: a != [], new_list))
        for number_list in new_list:
            answer += find_steps(number_list)
        return answer


columns = int(input())
cols = list(map(int, input().split()))
print(find_steps(cols))
