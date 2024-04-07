

CREATE TABLE IF NOT EXISTS `Owner` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `Phone` VARCHAR(12) UNIQUE NOT NULL,
    `FullName` VARCHAR(100) UNIQUE NOT NULL,
    `InstallDate` DATE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS `Group` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER ,
    `Name` VARCHAR(100) UNIQUE NOT NULL,
    `Description` VARCHAR
);

CREATE TABLE IF NOT EXISTS `Commercial` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `FullName` VARCHAR(100) NOT NULL,
    `phone` VARCHAR(12) UNIQUE NOT NULL,
    `Address` VARCHAR DEFAULT 'Iran, Fars, Shiraz',
    `PostalCode` VARCHAR(10) DEFAULT '1111111111',
    `Email` VARCHAR DEFAULT '',
    `Marked` BOOLEAN DEFAULT FALSE,
    `Comment` VARCHAR DEFAULT '',
    FOREIGN KEY(`OwnerId`) REFERENCES Owner(`Id`)
);

CREATE TABLE IF NOT EXISTS `General` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `FullName` VARCHAR(100) NOT NULL,
    `phone` VARCHAR(12) UNIQUE NOT NULL,
    `Address` VARCHAR DEFAULT 'Iran, Fars, Shiraz',
    `PostalCode` VARCHAR(10) DEFAULT '1111111111',
    `Email` VARCHAR DEFAULT '',
    `Marked` BOOLEAN DEFAULT FALSE,
    `Comment` VARCHAR DEFAULT '',
    FOREIGN KEY(`OwnerId`) REFERENCES Owner(`Id`)
);

INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09171000000','Mohammad');
INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09172000000','Ali');
INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09173000000','Mehdi');
INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'Ali Nikkhah','09172000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'Mehdi Nikkhah','09173000000');

