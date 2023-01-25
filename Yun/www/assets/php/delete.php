<?php
$id = $_POST["id"];
$db = new SQLite3('../../project.db');
$query = "DELETE FROM RFID WHERE ID = :id;";
$statement =  $db->prepare($query);
$statement->bindValue(':id', $id);
$result = $statement->execute();
$db->exec("UPDATE RFID SET ID=ID-1 where ID > $id;");
$db->exec("DELETE FROM sqlite_sequence;");
