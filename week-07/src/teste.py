import sys

try:
    with open(sys.argv[1],'r') as f:
        print(f.readlines())
except IndexError:
    print("Erro, arquivo não passado!") 
    sys.exit(1)
except FileNotFoundError:
    print("Erro, arquivo não existe!") 
    sys.exit(1)
    
