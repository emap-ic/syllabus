import sys


def read(filename):
    with open(filename,"r") as f:
        candidate_count = int(f.readline())

        names = {}
        for l in range(candidate_count):
            line = f.readline()
            names[line.strip()] = 0
            
        voter_count = int(f.readline())

        preferences = []
        for v in range(voter_count):
            current = []
            for c in range(candidate_count):
                line = f.readline()
                if line == '':
                    print("There are missing preferences for a voter!")
                    return 1

                print('good read')
                current.append(line.strip())
            preferences.append(current)

    return dict(names = names, preferences = preferences)
    

def eliminate(data, minim):
    for cand, votes in data['names'].items():
        if votes == minim:
            data['names'][cand] = 'eliminated'


def is_tie(data, minim):
    print("tie")
    for votes in data['names'].values():
        if votes != minim and votes != 'eliminated':
            return False

    return True

def find_min(data):
    print('min')
    m = len(data['preferences'])

    for cand, votes in data['names'].items():
        if votes != 'eliminated' and votes < minim:
            m = votes

    return m

def print_winner(data):
    print('win')
    for cand, votes in data['names'].items():
        print(cand)
        print(votes)
        print(int(data['voter_count'])/2)

        if votes != 'eliminated' and votes > int(data['voter_count'])/2:
            print('winner:')
            print(cand)
            return True

    return False

def tabulate(data):
    print('tab')
    for i in range(data['voter_count']):
        for j in range(data['candidate_count']):
            preference = data['preferences'][i][j]

            if data['names'][preference] != 'eliminated':
                data['names'][preference] += 1
                print(preference)
                break

def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: runoff FILE")
    if read(sys.argv[1]) == 1:
        sys.exit(1)
    data = read(sys.argv[1])

    while True:
        tabulate(data)

        if print_winner(data):
            print(data['names'])
            break
        
        min_votes = find_min(data)
        tie = is_tie(data, min_votes)

        if tie:
            for cand, votes in data['names'].items():
                if votes != 'eliminated':
                    print(cand)
                    print(data['names'])

            break

        eliminate(data, min_votes)

        for cand, votes in data['names'].items():
            if votes != 'eliminated':
                data['names'][cand] = 0

    sys.exit(0)

main()
