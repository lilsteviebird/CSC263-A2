import random

def create(file1, file2):
    with open(file1) as file:
        lines = [line.rstrip('\n') for line in file]
        
    punctuations = '''!()-[]{};:'"\,<>./?@#$%^&*_~'''

    lines = [l.split(' ') for l in lines]
    for i in lines:
        for j in i:
            if j in punctuations:
                i.remove(j)

            

    with open(file2) as file:
        #lines2 = file.readlines()
        lines2 = [line.rstrip('\n') for line in file]
    
    for i in lines:
        for j in i:
            if j in lines2:
                i.remove(j)  
    
    cards = [2,20,100,250,500]

    sets = 30

    for i in cards:
        f = open(str(i)+'.txt', 'w')
        for j in range(sets):
            new = []
            for m in range(i):
                num =  random.randrange(len(lines))
                num1 = random.randrange(len(lines[num]))
                print(lines[num][num1])
                new.append(lines[num][num1])
            f.write(','.join(new))
            f.write('\n')

                    
    
    #for i in range(sets):






create('metadata.txt', 'stopwords.txt')
