# coding=utf-8

guess = 1

import random
ret = random.randint(1,10)

while guess != ret:
    tmp = input("���������֣�")
    guess = int(tmp)
    if guess == ret:
        print("�¶���")
    else:
        if guess > ret:
            print("���˴���...")
        else:
            print ("С��С��")

print("��Ϸ������")