BEGIN TRANSACTION;
DROP TABLE IF EXISTS "Account";
CREATE TABLE IF NOT EXISTS "Account" (
	"ID" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"Acc" TEXT NOT NULL UNIQUE,
	"Pwd" TEXT NOT NULL,
	CHECK ("Acc" != ""),
	CHECK ("Pwd" != "")
);
INSERT INTO "Account" ("Acc", "Pwd")
VALUES ("Acc", "a8ce55ab5c4cafcf959b534ff5bb8dcf");
INSERT INTO "Account" ("Acc", "Pwd")
VALUES ("Acc2", "a8ce55ab5c4cafcf959b534ff5bb8dcf");
INSERT INTO "Account" ("Acc", "Pwd")
VALUES ("Acc3", "a8ce55ab5c4cafcf959b534ff5bb8dcf");
INSERT INTO "Account" ("Acc", "Pwd")
VALUES ("Acc4", "a8ce55ab5c4cafcf959b534ff5bb8dcf");
INSERT INTO "Account" ("Acc", "Pwd")
VALUES ("Acc5", "a8ce55ab5c4cafcf959b534ff5bb8dcf");
DROP TABLE IF EXISTS "Login_Log";
CREATE TABLE IF NOT EXISTS "Login_Log" (
	"ID" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"User" INTEGER NOT NULL,
	"Time" TEXT NOT NULL,
	FOREIGN KEY("User") REFERENCES "Account"("ID"),
	CHECK ("Time" != "")
);
INSERT INTO "Login_Log" ("User", "Time")
VALUES (1, "2022/09/27 09:21:10");
DROP TABLE IF EXISTS "RFID";
CREATE TABLE IF NOT EXISTS "RFID" (
	"ID" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"nickname" TEXT,
	"Rid" TEXT NOT NULL,
	CHECK("Rid" != "")
);
INSERT INTO "RFID" ("ID", "Rid")
VALUES (1, "A,B,C,D");
COMMIT;