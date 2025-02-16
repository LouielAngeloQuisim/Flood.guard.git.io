<?php
// post_data.php

// Allow cross-origin requests if needed (adjust as necessary)
header("Access-Control-Allow-Origin: *");
header("Content-Type: text/plain");

// Ensure the request method is POST
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    // Check if the 'temp' parameter is set
    if (isset($_POST["alert"])) {
        $alert = $_POST["alert"];

        // Optional: Log the received water level (or save to a database)
        $logEntry = date("Y-m-d H:i:s") . " - Alert: " . $alert . "\n";
        file_put_contents("alert.log", $logEntry, FILE_APPEND);

        // Send a success response
        echo "Alert received: " . $alert;
    } else {
        echo "Error: 'alert' parameter not found.";
    }
} else {
    echo "Error: Only POST requests are accepted.";
}
?>
