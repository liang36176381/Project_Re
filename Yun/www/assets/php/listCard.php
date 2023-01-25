<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="../css/listCard.css">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.6.1/jquery.min.js" integrity="sha512-aVKKRRi/Q/YV+4mjoKBsE4x3H+BkegoM/em46NNlCqNTmUYADjBbeNefNxYV7giUp0VxICtqdrbqU7iVaeZNXA==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
    <script>
        function show(target) {
            return confirm("確定刪除" + target.id + "?");
        }
        $(document).ready(function() {
            $('.delete').click(function() {
                let data = {
                    id: $(this).attr("id")
                }
                $.ajax({
                    type: 'POST',
                    url: './delete.php',
                    data: data,
                    success: function(msg) {
                        $("#iframe", parent.document).attr('src', $('#iframe', parent.document).attr('src'));
                    }
                })
                //TODO:刷新control.html iframe
            })
        });
    </script>
</head>

<body>
    <p id="p"></p>
    <?php
    $db = new SQLite3('../../project.db');
    $results = $db->query('SELECT * FROM RFID');
    echo "<table>";
    echo "<thead><tr><th>ID</th><th>nickname</th><th>Rid</th><th>delete</th></tr></thead>";
    echo "<tbody>";
    while ($row = $results->fetchArray()) {
        $id = $row['ID'];
        $nickname = $row['nickname'];
        $Rid = $row['Rid'];
        echo "<tr>";
        echo "<td>$id</td>";
        echo "<td>$nickname</td>";
        echo "<td>$Rid</td>";
        echo "<td><a class = \"delete\" id = $id onclick = \"return show(this)\">
        <img src = \"../image/delete.png\" style = \"width: 60px; height: 60px; cursor: pointer;\"></a></td>";
        echo "</tr>";
    }
    echo "</tbody>";
    echo "</table>";
    $db->close();
    ?>
</body>

</html>