<?php 
// print_r($_GET); die();
include_once('config.php');


function emailcheck()
{
	$email=$_POST['email'];
	$sql="SELECT * FROM user WHERE `email`='".$email."' ";
	$rs=mysqli_query($conn,$sql);
	$data=mysqli_num_rows($rs); 
	if($data > 0 || $data !='')
	{
		return "email exists";
	}

}
function usernamecheck()
{

	$username=$_GET['username'];
    $sql="SELECT * FROM user WHERE `username`='".$username."' ";
	$rs=mysqli_query($conn,$sql);
	$data=mysqli_num_rows($rs); 

	if($data > 0 || $data !='') 
	{
		return "username exist";
	}

}


?>
