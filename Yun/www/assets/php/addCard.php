<?php
/*openwrt的opkg到底是甚麼破爛，PHP/5.4.5居然沒有json_encode可以用??不是應該5.2.0就內建支援了???，還得自己刻一個*/
function array_to_json($data)
{
    $json = "{";
    foreach ($data as $key => $value) {
        $json .= "\"$key\":\"$value\",";
    }
    $json = rtrim($json, ",");
    $json .= "}";
    return $json;
}
$nickname = $_POST["nickname"];
$rid = join(",", $_POST["v"]);
if (!empty($_POST)) {
    try {
        $db = new SQLite3("../../project.db");
    } catch (Exception $e) {
        echo array_to_json(array("status" => "Error", "msg" => "Can't Connect to Database, Please Please Contact Your System Admin"));
        exit();
    }
    $query = "INSERT INTO RFID (ID, nickname, Rid) VALUES (:id, :nickname, :rid)";
    $statement = $db->prepare($query);
    $statement->bindValue(':id', NULL);
    $statement->bindValue(':nickname', empty($nickname) ? NULL : $nickname);
    $statement->bindValue(':rid', $rid);
    $result = $statement->execute();
    if ($result != false) {
        echo array_to_json(array("status" => "Success", "msg" => "Insert Successfully"));
    } else {
        echo array_to_json(array("status" => "Error", "msg" => "Insert Error, Please Try Again Latter"));
    }
    $db->close();
}
