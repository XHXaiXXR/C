# coding=utf-8

guess = 1

import random
ret = random.randint(1,10)

while guess != ret:
    tmp = input("请输入数字：")
    guess = int(tmp)
    if guess == ret:
        print("猜对了")
    else:
        if guess > ret:
            print("大了大了...")
        else:
            print ("小了小了")

print("游戏结束了")