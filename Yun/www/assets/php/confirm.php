<?php
function alert($msg)
{
    echo "<script>alert('$msg');</script>";
}
function jump($url)
{
    echo "<script>window.open(\"$url\",\"_self\");</script>";
}

$wrong_msg = "account or password wrong";
$acc = $_POST["account"];
$pwd = md5($_POST["password"]);
$db = new SQLite3("../../project.db");

// 使用 prepared statement 避免 SQL injection 的問題
$query = "SELECT * FROM Account WHERE Acc=:acc;";
$statement = $db->prepare($query);
$statement->bindValue(":acc", $acc);
$result = $statement->execute();
if ($result != false) {
    $row = $result->fetchArray();
    if ($row[2] == $pwd) {
        jump("../../control.html");
    } else {
        alert($wrong_msg);
        jump("../../index.html");
    }
} else {
    alert($wrong_msg);
    jump("../../index.html");
}
