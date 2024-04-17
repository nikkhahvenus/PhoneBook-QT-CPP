DROP TABLE `GroupMembersOfGeneralContacts`;
DROP TABLE `GroupMembersOfCommercialContacts`;
DROP TABLE `Groups`;
DROP TABLE `General`;
DROP TABLE `Commercial`;
DROP TABLE `Owner`;


CREATE TABLE IF NOT EXISTS `Owner` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `Phone` VARCHAR(12) UNIQUE NOT NULL,
    `FullName` VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS `Commercial` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `FullName` VARCHAR(100) NOT NULL,
    `Phone` VARCHAR(12) NOT NULL,
    `Address` VARCHAR DEFAULT 'Iran, Fars, Shiraz',
    `PostalCode` VARCHAR(10) DEFAULT '1111111111',
    `Email` VARCHAR DEFAULT '',
    `Marked` BOOLEAN DEFAULT FALSE,
    `Comment` VARCHAR DEFAULT '',
    FOREIGN KEY(`OwnerId`) REFERENCES `Owner`(`Id`)
);

CREATE TABLE IF NOT EXISTS `General` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `FullName` VARCHAR(100) NOT NULL,
    `Phone` VARCHAR(12) NOT NULL,
    `Address` VARCHAR DEFAULT 'Iran, Fars, Shiraz',
    `PostalCode` VARCHAR(10) DEFAULT '1111111111',
    `Email` VARCHAR DEFAULT '',
    `Marked` BOOLEAN DEFAULT FALSE,
    `Comment` VARCHAR DEFAULT '',
    FOREIGN KEY(`OwnerId`) REFERENCES `Owner`(`Id`)
);

CREATE TABLE IF NOT EXISTS `Groups` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `Name` VARCHAR UNIQUE NOT NULL,
    `Description` VARCHAR DEFAULT '',
    FOREIGN KEY(`OwnerId`) REFERENCES Owner(`Id`)
);

CREATE TABLE IF NOT EXISTS `GroupMembersOfCommercialContacts` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `GroupId` INTEGER NOT NULL,
    `CommercialId` INTEGER NOT NULL,
    FOREIGN KEY(`OwnerId`) REFERENCES Owner(`Id`),
    FOREIGN KEY(`GroupId`) REFERENCES `Groups`(`Id`)
    FOREIGN KEY(`CommercialId`) REFERENCES `Commercial`(`Id`)
);
CREATE TABLE IF NOT EXISTS `GroupMembersOfGeneralContacts` (
    `Id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `OwnerId` INTEGER NOT NULL,
    `GroupId` INTEGER NOT NULL,
    `GeneralId` INTEGER NOT NULL,
    FOREIGN KEY(`OwnerId`) REFERENCES `Owner`(`Id`),
    FOREIGN KEY(`GroupId`) REFERENCES `Groups`(`Id`)
    FOREIGN KEY(`GeneralId`) REFERENCES `General`(`Id`)
);

INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09171000000','mohammad');
INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09172000000','ali');
INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09173000000','mehdi');
INSERT INTO `Owner` (`Phone`,`FullName`) VALUES ('09177000000','afshin');

INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`, `Address`, `Email`, `Marked`, `Comment`) VALUES (1,'ali','09172000000', 'Iran Shiraz','ali@gmail.com', true, 'Ali is my best brother' );
INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'ahmad','09174000000');
INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'bagher','09174500000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'mehdi','09173000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'bagher','09175000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'bagher','09178000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (1,'bagher','09179000000');

INSERT INTO `Groups` (`OwnerId`,`Name`,`Description`) VALUES (1,'Neighbours','Group of people in my neighbourhood');

INSERT INTO `GroupMembersOfCommercialContacts` (`OwnerId`,`GroupId`,`CommercialId`) VALUES (1,1,1);
INSERT INTO `GroupMembersOfCommercialContacts` (`OwnerId`,`GroupId`,`CommercialId`) VALUES (1,1,2);
INSERT INTO `GroupMembersOfGeneralContacts` (`OwnerId`,`GroupId`,`GeneralId`) VALUES (1,1,1);


INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (2,'mohammad','09171000000');
INSERT INTO `Commercial` (`OwnerId`,`FullName`,`Phone`) VALUES (2,'mohammad','09176000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (2,'bagher','09175000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (2,'mehdi','09173000000');


INSERT INTO `Groups` (`OwnerId`,`Name`,`Description`) VALUES (2,'roomate','My Roomates');
INSERT INTO `Groups` (`OwnerId`,`Name`,`Description`) VALUES (2,'friends','My Friends');

INSERT INTO `GroupMembersOfCommercialContacts` (`OwnerId`,`GroupId`,`CommercialId`) VALUES (2,1,4);
INSERT INTO `GroupMembersOfGeneralContacts` (`OwnerId`,`GroupId`,`GeneralId`) VALUES (2,1,6);

INSERT INTO `GroupMembersOfCommercialContacts` (`OwnerId`,`GroupId`,`CommercialId`) VALUES (2,2,5);
INSERT INTO `GroupMembersOfGeneralContacts` (`OwnerId`,`GroupId`,`GeneralId`) VALUES (2,2,5);

INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (3,'ali','09172000000');
INSERT INTO `General` (`OwnerId`,`FullName`,`Phone`) VALUES (3,'afshin','09177000000');
