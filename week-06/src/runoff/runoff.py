
import sys

def read(filename):
    with open(sys.argv[1],"r") as f:
        candidate_count = int(f.readline())

        names = []
        for l in range(candidate_count):
            line = f.readline()
            names.append(line.strip())
            
        voter_count = int(f.readline())

        preferences = []
        for v in range(voter_count):
            current = []
            for c in range(candidate_count):
                line = f.readline()
                current.append(line.strip())
            preferences.append(current)

    return dict(candidate_count = candidate_count,
                names = names,
                voter_count = voter_count,
                preferences = preferences)
    

def eliminate(min):
    pass


def is_tie(min):
    pass


def find_min():
    pass

def print_winner():
    pass

def tabulate():
    pass


def vote(voter, rank, name):
    pass


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: runoff FILE")

    data = read(sys.argv[1])
    print(data)


main()
