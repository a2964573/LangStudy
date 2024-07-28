# temp = 0
# if temp == 1 :
#     print(temp)
# elif temp == 0 :
#     print(temp)
#     temp += 1
#     print(temp)



# list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
# for i in list:
#     temp += i
#     print(temp)

temp2 = 0
list2 = [1]
for j in list2 :
    temp2 += j
    list2.append(j)
    print(j)
    if len(list2) == 100 :
        break



def main(string) :
    print(string)



main("Hello, world!")