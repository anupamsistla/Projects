<?php
include_once('../config.php');

if($_SESSION['user']=="" && $_SESSION['user_permission']=="")
{
   echo '<script>
             alert("Please login first.");
            window.location.href="../../login.php";
    </script>';
}

// print_r($_GET); exit;


if($_POST['submit']=='Update-User')
{

  $userId= $_POST['userId'];
  $name= $_POST['name'];
  $username= $_POST['username'];
  $email= $_POST['email'];
  $password= $_POST['password']; 
  $gender= $_POST['gender'];
  $age= $_POST['age'];
  $medicalCondition= $_POST['medicalCondition'];
  
 $sql="UPDATE `user` SET  `name`='".$name."', `username`='".$username."' , `email`='".$email."',`password`='".$password."',`gender`='".$gender."', 
      `age`='".$age."',`medicalCondition`='".$medicalCondition."' WHERE `userId`='".$userId."'";
   // exit;
  $rs=mysqli_query($conn,$sql);
	if($rs)
	{
	    if($_POST['userType']=='3')
	    {
    		echo '<script>
                 alert("User update successfully");
                window.location.href="Medicinelist.php";
    		</script>';
	    }else{
	        	echo '<script>
                     alert("User update successfully");
                    window.location.href="Userlist.php";
        		</script>';
	    }
	}else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="updateUser.php?id='.$userId.'";
		</script>';
	}

}else{
  if($_GET['submit']=='update-status'){
  $id=$_GET['id'];
 $status="";
  if($_GET['status']=='Active'){
      $status ='Inactive';
    }
     if($_GET['status']=='Inactive'){
        $status ='Active';
    }

  $sql="UPDATE `user` SET `status`='".$status."' WHERE `userId`='".$id."'";
  $rs=mysqli_query($conn,$sql);

 if($rs)
  {
    echo '<script>
             alert("Status updated successfully");
            window.location.href="Userlist.php";
    </script>';
  }else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="Userlist.php";
    </script>';
  }
}
if($_GET['submit']=='delete'){
  $id=$_GET['id'];

  $sql="DELETE from `user` WHERE `userId`='".$id."'";
  $rs=mysqli_query($conn,$sql);
 if($rs)
  {
    echo '<script>
             alert("deleted successfully");
            window.location.href="Userlist.php";
    </script>';
  }else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="Userlist.php";
    </script>';
  }
}

}

?>