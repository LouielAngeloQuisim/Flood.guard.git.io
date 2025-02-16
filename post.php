<?php
// post_data.php

// Allow cross-origin requests if needed (adjust as necessary)
header("Access-Control-Allow-Origin: *");
header("Content-Type: text/plain");

// Ensure the request method is POST
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    // Check if the 'alert' parameter is set
    if (isset($_POST["alert"])) {
        $alert = $_POST["alert"];

        // Log the received alert locally (or save to a database)
        $logEntry = date("Y-m-d H:i:s") . " - Alert: " . $alert . "\n";
        file_put_contents("alert.log", $logEntry, FILE_APPEND);

        // Send a success response back to the sender
        echo "Alert received: " . $alert . "\n";

        // ------------------------------------------
        // Retrieve registered users' emails
        // (For this example, we're using a static array.
        //  Replace this with your Firebase retrieval code if needed.)
        // ------------------------------------------
        
        $registeredUsers = [
            "user1@example.com",
            "user2@example.com",
            "user3@example.com"
        ];

        // Prepare email details
        $subject = "Water Level Alert";
        $message = "An alert was triggered with value: " . $alert . ".\nPlease take necessary actions.";
        $headers = "From: no-reply@example.com\r\n" .
                   "Reply-To: no-reply@example.com\r\n" .
                   "X-Mailer: PHP/" . phpversion();

        // Send email to each registered user
        foreach ($registeredUsers as $email) {
            $result = mail($email, $subject, $message, $headers);
            if ($result) {
                echo "Email sent successfully to: $email\n";
            } else {
                echo "Failed to send email to: $email\n";
            }
        }
    } else {
        echo "Error: 'alert' parameter not found.";
    }
} else {
    echo "Error: Only POST requests are accepted.";
}
?>
