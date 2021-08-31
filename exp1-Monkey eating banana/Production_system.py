import numpy as np

site = ['a', 'b', 'c']

class status:
    def __init__(self, loc_monkey='a', loc_box='b', loc_banana='c', on_box=0, hold=0, father=-1):
        self.loc_monkey = loc_monkey
        self.loc_box = loc_box
        self.loc_banana = loc_banana
        self.on_box = on_box
        self.hold = hold
        self.father = father

    def goto(self, index):
        new_status = []
        if self.on_box == 1:
            return new_status
        for item in site:
            if item != self.loc_monkey:
                new_status.append(status(loc_monkey=item, loc_box=self.loc_box, on_box=self.on_box, hold=self.hold, father=index))
        return new_status

    def push_box(self, index):
        new_status = []
        if self.on_box == 1 or self.loc_box != self.loc_monkey:
            return new_status
        for item in site:
            if item != self.loc_monkey:
                new_status.append(status(loc_monkey=item, loc_box=item, on_box=self.on_box, hold=self.hold, father=index))
        return new_status

def is_equal(status1, status2):
    if __name__ == '__main__':
        if status1.loc_monkey==status2.loc_monkey and status1.loc_box==status2.loc_box and status1.loc_banana==status2.loc_banana and status1.on_box==status2.on_box\
            and status1.hold == status2.hold:
            return True
        else:
            return False

def print_status(status, database):
    if database[status.father].father != -1:
        print_status(database[status.father], database)
    father_status = database[status.father]
    print('if (' + father_status.loc_monkey + ',' + father_status.loc_box + ',' + father_status.loc_banana + ',' + str(father_status.on_box) + ',' + str(father_status.hold) + \
          ')  then (' + status.loc_monkey + ',' + status.loc_box + ',' + status.loc_banana + ',' + str(status.on_box) + ',' + str(status.hold) + ')')
    return

def add(database, new_status):

    flag = True
    for new in new_status:
        for old in database:
            if is_equal(new, old):
                flag = False
                break
        if flag:
            database.append(new)

    return database

def init_database():
    database = []
    init_status = status()
    database.append(init_status)
    return database

def main():
    final_status = status('c','c','c',0,0)
    database = init_database()
    already_checked = 0
    is_found = False
    # 如果database中还有未check的事实，就拿出一个，求它产生的新状态，加入database中
    while already_checked<len(database):
        now_status = database[already_checked]
        # 得到goto能够产生的状态
        new_status = now_status.goto(already_checked)
        # 判断new_status中的状态是否已存在，不存在则加入data_base
        database = add(database, new_status)

        for item in database:
            if is_equal(item, final_status):
                is_found = True
                final_status.father = item.father
                break
        if is_found:
            break

        # 得到push能够产生的状态
        new_status = now_status.push_box(already_checked)
        database = add(database, new_status)

        for item in database:
            if is_equal(item, final_status):
                is_found = True
                final_status.father = item.father
                break
        if is_found:
            break

        already_checked += 1

    if is_found:
        print_status(final_status,database)
        print("if (c,c,c,0,0)  then (c,c,c,1,0)\nif (c,c,c,1,0)  then (c,c,c,1,1)")
    else:
        print('Not found.')

if __name__ == '__main__':
    main()