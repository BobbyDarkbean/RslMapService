CREATE TABLE employees (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR,
    isactive INTEGER
);

CREATE TABLE currentusers (
    id INTEGER PRIMARY KEY,
    hallnum INTEGER,
    cardnum INTEGER,
    name VARCHAR,
    isoff INTEGER
);

CREATE TABLE currentrequests (
    id INTEGER PRIMARY KEY,
    userid INTEGER,
    doctitle VARCHAR,
    doctype INTEGER,
    itemcount INTEGER,
    status INTEGER,
    FOREIGN KEY(userid) REFERENCES currentusers(id)
);
