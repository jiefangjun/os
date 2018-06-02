#!/usr/bin/python

class mM():
    def __init__(self, size):
        self.cursize = size
        self.size = size
        '''
        维护一个分区空闲表
        空闲分区表中存储字典 各字段分别为 分区号 分区大小 分区起始地址 以及分区状态 0 代表空闲 其它代表已分配作业号
        '''
        self.free = [{'pnum' : 1, 'psize' : self.size, 'pstart' : 0, 'pstate' : 0}]

    def allot(self, num, size):
        if size <= self.size:
            # 准备分配,不分配已有作业号
            for item in self.free:
                if num == item['pstate']:
                    print('已存在作业号，不予分配')
                    return
            for item in self.free: 
                if item['psize'] >= size and item['pstate'] == 0:
                    if item['psize'] > size and item['pstate'] == 0:
                        # 新块剩余内存
                        nf = item['psize'] - size;
                        # 已分配内存比当前块内存小，产生新块
                        index = self.free.index(item)
                        # 产生一个空闲分区
                        new = {'pnum' : self.free[index]['pnum'] + 1, 'psize' : nf, 'pstart' : item['pstart'] + size, 'pstate' : 0}
                        self.free.insert(index + 1, new)

                        # 整理块号
                        self.trim(index)

                    # 修改当前块状态
                    item['pstate'] = num
                    item['psize'] = size
                    self.cursize -= size
                    print("分配成功")
                    return
            print("分配失败，无可分配内存")
            return
        print("分配失败，作业内存大于系统内存")
    
    def recycle(self, num):
        print("recycle")
        for item in self.free:
            if item['pstate'] == num and num != 0:

                index = self.free.index(item)
                print("存在作业号，索引位置：" + str(index))

                # 加上当前作业块内存
                self.cursize += item['psize']

                # 准备回收， 判断回收情况
                # 前后同时邻接
                if index != 0 and self.free[index - 1]['pstate'] == 0 and index + 1 < len(self.free) and self.free[index + 1]['pstate'] == 0:
                    # 调整分区大小
                    self.free[index - 1]['psize'] += item['psize'] + self.free[index + 1]['psize']
                    self.free.pop(index)
                    # 弹出一个元素后，后一个元素前移
                    self.free.pop(index)

                # 前邻接,非队首
                elif index != 0 and self.free[index - 1]['pstate'] == 0:
                    #print(self.free[index - 1].values())
                    # 只改变大小
                    self.free[index - 1]['psize'] += item['psize']
                    self.free.pop(index)
                # 后邻接,非队尾
                elif index + 1 < len(self.free) and self.free[index + 1]['pstate'] == 0:
                    item['psize'] += self.free[index + 1]['psize']
                    item['pstate'] = 0
                    self.free.pop(index + 1)

                # 一个也不邻接
                else:
                    print(item['pstate'])
                    item['pstate'] = 0
                
                self.trim(index)
                return

        print("未找到作业号，回收失败")

    
    def status(self):
        print("当前内存状态")
        print("总内存为：" + str(self.size) + " 空闲内存为：" + str(self.cursize))
        for item in self.free:
            print(str(item))

    def trim(self, index):
        # 整理块号
        for block in self.free[index:]:
            block['pnum'] = index + 1
            index += 1



if __name__ == '__main__':
    # 初始化分区大小

    size = int(input("输入分区初始大小："))
    print(size)
    
    mm = mM(size);

    print("选择菜单:\n1 分配\n2 回收\n3 显示内存状态\n4 退出\n")

    while True:

        item = int(input("选择："))
        if item == 1:
            num = int(input("输入作业号："))
            size = int(input("输入作业大小："))
            mm.allot(num, size)
        elif item == 2:
            num = int(input("输入回收作业号："))
            mm.recycle(num)
        elif item == 3:
            mm.status()
        elif item == 4:
            break
        else:
            print("请选择正确的选项！")
            print("选择菜单:\n1 分配\n2 回收\n3 显示内存状态\n")


