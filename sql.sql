

CREATE TABLE IF NOT EXISTS `Owner` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `Phone` VARCHAR(12) UNIQUE NOT NULL,
    `FullName` VARCHAR(100) NOT NULL,
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
    `phone` VARCHAR(12) NOT NULL,
    `Address` VARCHAR DEFAULT 'Iran, Fars, Shiraz',
    `PostalCode` VARCHAR(10) DEFAULT '1111111111',
    `Email` VARCHAR DEFAULT '',
    `Marked` BOOLEAN DEFAULT FALSE,
    `Comment` VARCHAR DEFAULT '',
    UNIQUE(OwnerId,phone),
    FOREIGN KEY(`OwnerId`) REFERENCES `Owner`(`Id`)
);

CREATE TABLE IF NOT EXISTS `General` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `FullName` VARCHAR(100) NOT NULL,
    `phone` VARCHAR(12) NOT NULL,
    `Address` VARCHAR DEFAULT 'Iran, Fars, Shiraz',
    `PostalCode` VARCHAR(10) DEFAULT '1111111111',
    `Email` VARCHAR DEFAULT '',
    `Marked` BOOLEAN DEFAULT FALSE,
    `Comment` VARCHAR DEFAULT '',
    UNIQUE(OwnerId,phone),
    FOREIGN KEY(`OwnerId`) REFERENCES `Owner`(`Id`)
);

CREATE TABLE IF NOT EXISTS `Group` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `name` VARCHAR UNIQUE NOT NULL,
    `Description` VARCHAR DEFAULT '',
    FOREIGN KEY(`OwnerId`) REFERENCES Owner(`Id`),
    FOREIGN KEY(`CommercialId`) REFERENCES `Commercial`(`Id`)
);

CREATE TABLE IF NOT EXISTS `GroupMembersOfCommercialContacts` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `GroupId` INTEGER NOT NULL,
    `CommercialId` INTEGER NOT NULL,
    FOREIGN KEY(`OwnerId`) REFERENCES Owner(`Id`),
    FOREIGN KEY(`GroupId`) REFERENCES `Group`(`Id`)
    FOREIGN KEY(`CommercialId`) REFERENCES `Commercial`(`Id`)
);
CREATE TABLE IF NOT EXISTS `GroupMembersOfGeneralContacts` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `GroupId` INTEGER NOT NULL,
    `GeneralId` INTEGER NOT NULL,
    FOREIGN KEY(`OwnerId`) REFERENCES `Owner`(`Id`),
    FOREIGN KEY(`GroupId`) REFERENCES `Group`(`Id`)
    FOREIGN KEY(`GeneralId`) REFERENCES `General`(`Id`)
);

INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09171000000','Mohammad');
INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09172000000','Ali');
INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09173000000','Mehdi');
INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09177000000','Afshin');

INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'Ali','09172000000');
INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'Ahmad Adib','09174000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'Mehdi','09173000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'Bagher Babaali','09175000000');

INSERT INTO `Group` (`OwnerId`,`Name`,`Description`) VALUES (1,'Neighbours','Group of people in my neighbourhood');

INSERT INTO `GroupMembersOfCommercialContacts` (`OwnerId`,`GroupId`,`CommercialId`) VALUES (1,1,1);
INSERT INTO `GroupMembersOfCommercialContacts` (`OwnerId`,`GroupId`,`CommercialId`) VALUES (1,1,2);
INSERT INTO `GroupMembersOfGeneralContacts` (`OwnerId`,`GroupId`,`GeneralId`) VALUES (1,1,1);


INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (2,'Mohammad Nikkhah','09171000000');
INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (2,'Mohammad Bahrani','09176000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (2,'Bagher Babaali','09175000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (2,'Mehdi Nikkhah','09173000000');


INSERT INTO `Group` (`OwnerId`,`Name`,`Description`) VALUES (2,'Roomate','My Roomates');
INSERT INTO `Group` (`OwnerId`,`Name`,`Description`) VALUES (2,'Friends','My Friends');

INSERT INTO `GroupMembersOfCommercialContacts` (`OwnerId`,`GroupId`,`CommercialId`) VALUES (2,1,1);
INSERT INTO `GroupMembersOfGeneralContacts` (`OwnerId`,`GroupId`,`GeneralId`) VALUES (2,1,2);

INSERT INTO `GroupMembersOfCommercialContacts` (`OwnerId`,`GroupId`,`CommercialId`) VALUES (2,2,2);
INSERT INTO `GroupMembersOfGeneralContacts` (`OwnerId`,`GroupId`,`GeneralId`) VALUES (2,2,1);

INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (3,'Ali Nikkhah','09172000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (3,'Afshin Akbari','09177000000');
