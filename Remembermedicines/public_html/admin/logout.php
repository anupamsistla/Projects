<?php include_once('../config.php');
 unset($_SESSION['user_data']);
 unset($_SESSION['user']);
 unset($_SESSION['user_permissions']);
 
$userdata=array();
$data2=array();
$_SESSION['user']=$userdata;
$_SESSION['user_permissions']=$data2;
$_GET['code']="";
session_destroy();

     echo '<script>
            window.location.href="../../index.php";
    </script>';

?>