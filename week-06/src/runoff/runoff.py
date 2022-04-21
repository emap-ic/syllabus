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


#eliminate the candidate (or candidates) in last place
def eliminate(minimo):
    for i in range(candidate_count):
        if votos[i] == minimo:
            eliminated[i] = True


'''return true if the election is tied between all candidates, false
   otherwise. It's tie when all candidate (not eliminated) have the
   same number of votes and this numbers is min'''
def is_tie(minimo):
    for i in range(candidate_count):
        if eliminated[i] == False and votos[i] > minimo:
            return False
    return True


#Return the minimum number of votes any remaining candidate has
def find_min():
    menor = votos[0]
    for i in range(candidate_count):
        if eliminated[i] == False and votos[i] < menor:
            menor = votos[i]
    return menor


#Print the winner of the election, if there is one
def print_winner():
    minVotes = voter_count/2
    for i in range(candidate_count):
        if votos[i] > minVotes:
            print(nomes[i])
            return True
    return False


#Tabulate votes for non-eliminated candidates
def tabulate():
    preferencia = 0
    cont = 0
    for i in range(voter_count):
        while True:
            if preferences[i][preferencia] == nomes[cont]:
                if eliminated[cont] == True:
                    preferencia +=1
                    cont = 0
                else:
                    votos[cont]+=1
                    cont = 0
                    preferencia = 0
                    break
            else:
                cont += 1

#check if there is a invalid vote
def vote():
    for i in range(voter_count):
        for j in range(candidate_count):
            if preferences[i][j] not in nomes:
                return False
    return True


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: runoff FILE")
        print(len(sys.argv))

    data = read(sys.argv[1])


    global voter_count
    global preferences
    global candidate_count
    global nomes
    global eliminated
    global votos

    voter_count = data['voter_count']
    preferences = data['preferences']
    candidate_count = data['candidate_count']
    nomes = data['names']
    
    #list for each candidate vote and list to atribute bools for each candidate, respectively
    #originally, candidates are non-eliminated and don't have any vote
    votos = []
    eliminated = []
    for j in range(candidate_count):
        votos.append(0)
        eliminated.append(False)

    if vote() == False:
        print('invalid vote.')
        return 4

    #the ellection
    while True:
        tabulate()

        won = print_winner()
        if won:
            break
        
        #Eliminate last-place candidates
        minimo = find_min()
        tie = is_tie(minimo)

        #if tie, everyone wins
        if tie:
            for i in range(candidate_count):
                if eliminated[i] == False:
                    print(nomes[i])
            break

        #eliminate anyone with minimum number of votes
        eliminate(minimo)

        #reset vote counts back to zero
        for i in range(candidate_count):
            votos[i] = 0

    return 0





main()
