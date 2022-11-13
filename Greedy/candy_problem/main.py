def find_candies(days, candies):
    total = sum(candies)
    cand = [0 for i in range(len(candies))]
    eaten = []
    for i in range(1, days + 1):
        difference_list = []
        # print("---------------------------------")
        # print("cand list ==>", cand)
        for j in range(1, len(candies)):
            # print(i * candies[j] / total, cand[j], i * candies[j] / total - cand[j])
            diff = i * candies[j] / total - cand[j]
            difference_list.append((j, diff))
        print("diff list =====>", difference_list)
        max_index = max(difference_list, key=lambda item: item[1])[0]
        cand[max_index] += 1
        eaten.append(max_index)
    return eaten


count, days = map(int, input().split())
candies = (list(map(int, input().split())))
candies.insert(0, 0)
print(*find_candies(days, candies))
