# Imports titles and genres from CSV into a SQLite database

import csv
import sqlite3

con = sqlite3.connect('favorites.db')


def add_show(cursor, title):
    res = [r for r in cursor.execute("SELECT id from shows where title = ?", (title,))]
    if res:
        return res[0][0]
    else:
        cursor.execute('INSERT INTO shows (title) VALUES (?)', (title,))
        return cursor.lastrowid

def add_genre(cursor, genre):
    res = [r for r in cursor.execute("SELECT id from genres where genre = ?", (genre,))]
    if res:
        return res[0][0]
    else:
        cursor.execute('INSERT INTO genres (genre) VALUES (?)', (genre,))
        return cursor.lastrowid
    

with open('emap-shows.csv','r') as f:
    reader = csv.DictReader(f)
    cursor=con.cursor()

    for r in reader:
        # prepare data from csv
        title = r['title'].strip()

        genres = [x.strip() for x in r['genres'].split(";")]

        # add genres and titles
        show_id = add_show(cursor, title)
        for g in genres:
            genre_id = add_genre(cursor, g)
            print(f"> debug inserting {title}/{show_id} {g}/{genre_id}")
            cursor.execute('INSERT INTO show_genres (show_id,genre_id) VALUES (?,?)', (show_id,genre_id))

    con.commit()
    con.close()
            
