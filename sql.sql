CREATE TABLE IF NOT EXISTS `table1` (
    `id` INTEGER,
    `bla1` TEXT,
    PRIMARY KEY(`id`)
);
CREATE TABLE IF NOT EXISTS `table2` (
    `id` INTEGER,
    `bla2` TEXT,
    PRIMARY KEY(`id`)
);

INSERT INTO `table2` (bla2) VALUES ('Hello World;!');

CREATE TABLE IF NOT EXISTS customers (
    customerID INTEGER PRIMARY KEY AUTOINCREMENT,
    firstName VARCHAR,
    lastName VARCHAR
);
INSERT INTO customers (firstName,lastName) VALUES ('Ali','Nikkhah');
