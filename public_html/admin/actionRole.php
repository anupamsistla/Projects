<?php
include_once('../config.php');

if($_SESSION['user']=="" && $_SESSION['user_permission']=="")
{
   echo '<script>
             alert("Please login first.");
            window.location.href="../../login.php";
    </script>';
}

// print_r($_POST); die();


if($_POST['submit']=='Add-Role')
{

  $roleName= $_POST['roleName'];
  $roleStatus= $_POST['roleStatus'];
  $createdDate=date('Y-m-d H:i:s');
  
  $sql="INSERT into roles (`roleName`,`roleStatus`,`createdDate`) VALUES('".$roleName."','".$roleStatus."','".$createdDate."')";
 //  exit;
  $rs=mysqli_query($conn,$sql);
	if($rs)
	{
		echo '<script>
             alert("Role added successfully");
            window.location.href="Rolelist.php";
		</script>';
	}else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="Rolelist.php;
		</script>';
	}

}
if($_POST['submit']=='Update-Role')
{

  $roleName= $_POST['roleName'];
  $roleStatus= $_POST['roleStatus'];
  $id=$_POST['roleId'];
  
 $sql="UPDATE `roles` SET  `roleName`='".$roleName."', `roleStatus`='".$roleStatus."' WHERE `roleId`='".$id."' ";
   // exit;
  $rs=mysqli_query($conn,$sql);
	if($rs)
	{
		echo '<script>
             alert("Role update successfully");
            window.location.href="Rolelist.php";
		</script>';
	}else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="UpdateRole.php?id='.$id.'";
		</script>';
	}

}

if($_GET['submit']=='Delete'){
  $id=$_GET['id'];

  $sql="DELETE from `roles` WHERE `roleId`='".$id."'";
  $rs=mysqli_query($conn,$sql);
 if($rs)
  {
    echo '<script>
             alert("role deleted successfully");
            window.location.href="Rolelist.php";
    </script>';
  }else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="Rolelist.php";
    </script>';
  }

}

?>