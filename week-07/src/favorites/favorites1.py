import csv

with open("emap-shows.csv", "r") as file:

    reader = csv.DictReader(file)
    
    titles = {}
    for row in reader:
        t = row['title']
        if t not in titles:
            titles[t] = 0
        titles[t] = titles[t] + 1

    for k in sorted(titles, key = lambda k : titles[k], reverse = True):
        print(f"{k} => {titles[k]}")
