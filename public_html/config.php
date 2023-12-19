<?php 



require_once('google-api/vendor/autoload.php');

$gClient = new Google_Client();
$gClient->setClientId("249721743136-49jhdt2lnh4c8vu47df3o219p2lrpkhb.apps.googleusercontent.com");
$gClient->setClientSecret("j9VhqhBBpGrGJVZ7JErP3R5e");
$gClient->setApplicationName("Remember Medicine");
$gClient->setRedirectUri('https://remembermedicines.com/action.php');
$gClient->addScope('https://www.googleapis.com/auth/plus.login https://www.googleapis.com/auth/userinfo.email');

$login_url=$gClient->createAuthUrl();



session_start();


//$base_url="http://localhost:8080/remembermedicines/";
$base_url="https://remembermedicines.com/";

$servername = "localhost";
//$username = "root";
//$password = "";
$username = "remem6uj_medicar";
$password = "medi@2021";
$database = "remem6uj_medicare";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $database);

// Check connection
if (!$conn) {
  die("Connection failed: " . mysqli_connect_error());
}
//echo "Connected successfully";




?>
