from subprocess import run, PIPE



for i in range(1000):
    file = open(f'./test_cases/test_case{i}.txt','r')
    # file2 = open(f'./output/test_case{i}.txt','r')
    stri = ""
    strik = ""
    for line in file.readlines():
        stri += line
    # for line in file2.readlines():
    #     strik += line
    file.close()
    # file2.close()
    p1 = run(['./fixed.exe'], stdout=PIPE,
            input=f"""{stri}""", encoding='ascii')
    ss = (p1.stdout).strip()
    p2 = run(['./mine.exe'], stdout=PIPE,
            input=f"""{stri}""", encoding='ascii')
    tt =( p2.stdout).strip()
    # list(p.stdout.split(" "))
    if tt != ss:
        print(f"test case {i} ===> mine:",tt," --- fixed :  ",ss)
