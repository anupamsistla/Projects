<?php
include_once('../config.php');

if($_SESSION['user']=="" && $_SESSION['user_permission']=="")
{
   echo '<script>
             alert("Please login first.");
            window.location.href="../../login.php";
    </script>';
}

//print_r($_POST); die();


if($_POST['submit']=='Add-Permission')
{
  $role=$_POST['role'];
  
 $sql1="SELECT * FROM module"; 
 $rs1=mysqli_query($conn,$sql1);
 $data0=mysqli_num_rows($rs1);
 
 if($data0 > 0)
 {
    while($data1=mysqli_fetch_assoc($rs1))
    {
          $permissionView= 'N';
          $permissionAdd=  'N';
          $permissionEdit=  'N';
          $permissionDelete=  'N';
          $permissionStatus=  'N';
          
          if($_POST['permissionView_'.$data1['moduleId']]=='Y')
          {
              $permissionView= 'Y';
          }
          if($_POST['permissionAdd_'.$data1['moduleId']]=='Y')
          {
              $permissionAdd= 'Y';
          }          
          if($_POST['permissionEdit_'.$data1['moduleId']]=='Y')
          {
              $permissionEdit= 'Y';
          }          
          if($_POST['permissionDelete_'.$data1['moduleId']]=='Y')
          {
              $permissionDelete= 'Y';
          }
          if($_POST['permissionStatus_'.$data1['moduleId']]=='Y')
          {
              $permissionStatus= 'Y';
          }
          
           $createdDate=date('Y-m-d h:i:s');
          
           $sql2="SELECT * FROM permission WHERE roleId='".$role."' AND moduleId='".$data1['moduleId']."'"; 
           $rs2=mysqli_query($conn,$sql2);
           $data2=mysqli_num_rows($rs2);
          if($data2 > 0)
          {
              $sql3="UPDATE permission SET roleId='".$role."', moduleId='".$data1['moduleId']."', permissionView='".$permissionView."', permissionAdd='".$permissionAdd."',
              permissionEdit='".$permissionEdit."', permissionDelete='".$permissionDelete."', permissionStatus='".$permissionStatus."' WHERE roleId='".$role."' AND moduleId='".$data1['moduleId']."' "; 
              $rs3=mysqli_query($conn,$sql3);
           
          }else{
              $sql4="INSERT into permission(`roleId`, `moduleId`, `permissionView`, `permissionAdd`, `permissionEdit`, `permissionDelete`, `permissionStatus`, `createdDate`) 
                                      VALUES('".$role."','".$data1['moduleId']."','".$permissionView."','".$permissionAdd."','".$permissionEdit."','".$permissionDelete."','".$permissionStatus."','".$createdDate."')"; 
              $rs4=mysqli_query($conn,$sql4);
          }
    }
    
     echo '<script>
             alert("Permissions set successfully");
            window.location.href="Permissionlist.php";
		</script>';
    
 }else{
     echo '<script>
             alert("Module not found");
            window.location.href="Permissionlist.php";
		</script>';
 }
 
}
if($_POST['submit']=='Add-Module')
{
  $moduleName= $_POST['moduleName'];
  $createdDate=date('Y-m-d H:i:s');
  
$sql="INSERT into module(`moduleName`,`createdDate`) VALUES('".$moduleName."','".$createdDate."')";
 //exit;
  $rs=mysqli_query($conn,$sql);
	if($rs)
	{
		echo '<script>
             alert("Module added successfully");
            window.location.href="Permissionlist.php";
		</script>';
	}else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="Permissionlist.php";
		</script>';
	}

}
if($_POST['submit']=='Update-Module')
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

?>