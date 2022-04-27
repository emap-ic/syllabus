

CREATE TABLE shows
 (id INTEGER,
  title TEXT NOT NULL,
  PRIMARY KEY(id));

CREATE TABLE genres
 (id INTEGER,
  genre TEXT NOT NULL,
  PRIMARY KEY(id));
  
CREATE TABLE show_genres
 (show_id INTEGER,
  genre_id INTEGER,
  FOREIGN KEY(show_id) REFERENCES shows(id),
  FOREIGN KEY(genre_id) REFERENCES shows(id));
