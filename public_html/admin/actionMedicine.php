<?php include_once('../config.php');

if($_SESSION['user']=="" && $_SESSION['user_permission']=="")
{
   echo '<script>
             alert("Please login first.");
            window.location.href="../../login.php";
    </script>';
}

//print_r($_GET); exit;


if($_GET['submit']=='delete'){
  $id=$_GET['id'];
  $userid=$_GET['userid'];

  $sql="DELETE from `medicines` WHERE `medicineId`='".$id."' AND userId='".$userid."'";
  $rs=mysqli_query($conn,$sql);
 if($rs)
  {
     $sql1="DELETE from `medicine_schedule` WHERE `medicineId`='".$id."'";
     $rs1=mysqli_query($conn,$sql1);
    echo '<script>
             alert("Medicine deleted successfully");
            window.location.href="Medicinelist.php";
    </script>';
  }else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="Medicineslist.php";
    </script>';
  }
}
if($_POST['submit']=='Update-Medicine')
{

  $medId= $_POST['medId'];
  $name= $_POST['name'];
  $type= $_POST['type'];
  $medicalCondition= $_POST['medicalCondition'];
  $day = implode(',', $_POST['day']);
  $medTime= $_POST['medTime'];
  $expiryDate= date('Y-m-d',strtotime($_POST['expiryDate']));
  $meansTotake= $_POST['meansTotake'];
  $importance= $_POST['importance'];
  $doctorContact= $_POST['doctorContact'];
  $quantity= $_POST['quantity'];
  $stock= $_POST['stock'];
  $userId= $_POST['userId'];

  if(!empty($_FILES["prescription"]["name"])){
      $target_dir='../uploads/';   // print_r($_FILES);
      $target_file=$target_dir.basename(time()."_".$_FILES["prescription"]["name"]);
      $filepre=time()."_".$_FILES["prescription"]["name"];
      $checkfileType=strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

      if(move_uploaded_file($_FILES["prescription"]["tmp_name"], $target_file)){
         //echo "uploaded";
      }
  }else{
      $filepre=$_POST['presname'];
    }
    
    
    if(!empty($_FILES["image"]['name']))
    {
      $target_dir='../uploads/';   // print_r($_FILES);
      $target_file=$target_dir.basename(time()."_".$_FILES["image"]["name"]);
      $file=time()."_".$_FILES["image"]["name"];
      $checkfileType=strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
    
        if(move_uploaded_file($_FILES["image"]["tmp_name"], $target_file)){
           //echo "uploaded";
        }
    }else{
      $file=$_POST['filename'];
    }
    
    // echo $file;
    // exit;
  $createdDate= date('Y-m-d h:i:s');
   
  $sql="UPDATE `medicines` SET `doctorContact`='".$doctorContact."', `stock`='".$stock."',`quantity`='".$quantity."',`prescription`='".$filepre."',`name`='".$name."', `type`='".$type."', `medicalCondition`='".$medicalCondition."' , `meansTotake`='".$meansTotake."',`expiryDate`='".$expiryDate."',`image`='".$file."', `importance`='".$importance."' WHERE medicineId='".$medId."' AND userId='".$userId."'";
  $rs=mysqli_query($conn,$sql);
  //echo $insertId; exit;
	if($rs)
	{
      $sql1="UPDATE  `medicine_schedule` set `medicineId`='".$medId."',`day`='".$day."', `medTime`='".$medTime."'";
      $rs1=mysqli_query($conn,$sql1);
		echo '<script>
             alert("Medicine update successfully");
            window.location.href="Medicinelist.php";
		</script>';
	}else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="updatemedicine.php?id='.$medId.'";
		</script>';
	}

}

if($_POST['submit']=='Add-Medicine')
{

  $name= $_POST['name'];
  $type= $_POST['type'];
  $medicalCondition= $_POST['medicalCondition'];
  $medTime= $_POST['medTime'];
  $expiryDate= date('Y-m-d',strtotime($_POST['expiryDate']));
  $meansTotake= $_POST['meansTotake'];
  $importance= $_POST['importance'];
  $doctorContact= $_POST['doctorContact'];
  $userId= $_POST['userId'];
  $quantity= $_POST['quantity'];
  $stock= $_POST['stock'];
  $day = implode(',', $_POST['day']);

  if($_FILES["image"]["name"]!=''){
      $target_dir='../uploads/';   // print_r($_FILES);
      $target_file=$target_dir.basename(time()."_".$_FILES["image"]["name"]);
      $file=time()."_".$_FILES["image"]["name"];
      $checkfileType=strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

      if(move_uploaded_file($_FILES["image"]["tmp_name"], $target_file)){
         //echo "uploaded";
      }
  }

  if($_FILES["prescription"]["name"]!=''){
      $target_dir='../uploads/';   // print_r($_FILES);
      $target_file=$target_dir.basename(time()."_".$_FILES["prescription"]["name"]);
      $filepre=time()."_".$_FILES["prescription"]["name"];
      $checkfileType=strtolower(pathinfo($target_file,PATHINFO_EXTENSION));

      if(move_uploaded_file($_FILES["prescription"]["tmp_name"], $target_file)){
         //echo "uploaded";
      }
  }

   $createdDate= date('Y-m-d h:i:s');
  
   $sql="INSERT INTO  `medicines` (`userId`,`name`, `type`, `medicalCondition`, `meansTotake`,`expiryDate`,`image`,`quantity`,`stock`, `prescription`, `importance`,`doctorContact`, `createdDate`)  
   VALUEs('".$userId."','".$name."','".$type."'  ,'".$medicalCondition."' ,'".$meansTotake."' ,'".$expiryDate."' ,'".$file."','".$quantity."','".$stock."','".$filepre."','".$importance."',
   '".$doctorContact."','".$createdDate."')";
   //exit;
  $rs=mysqli_query($conn,$sql);
  $insertId=mysqli_insert_id($conn);

  if($rs)
  {
     $sql1="INSERT INTO  `medicine_schedule` (`medicineID`,`day`, `medTime`,`createdDate`)  VALUEs('".$insertId."','".$day."','".$medTime."'  ,'".$createdDate."')";
     $rs1=mysqli_query($conn,$sql1);
    echo '<script>
             alert("Medicine added successfully");
            window.location.href="Medicinelist.php";
    </script>';
  }else{
     echo '<script>
             alert("something went wrong.");
            window.location.href="addMedicine.php";
    </script>';
  }
}
if($_GET['submit']=='taken')
{

  $medId= $_GET['id'];
  $userId= $_GET['userid'];
  $scheduleId=$_GET['scheduleId'];
  
 $sql1="SELECT stock From medicines  WHERE medicineId='".$medId."' AND userId='".$userId."'";
     $rs1=mysqli_query($conn,$sql1);
     $data1=mysqli_fetch_assoc($rs1);
 
  if($data1['stock'] != 0 || $data1['stock'] < 0)
  {
      $stock=$data1['stock']-1;
      $sql="UPDATE `medicines` SET `stock`='".$stock."' WHERE medicineId='".$medId."' AND userId='".$userId."'";
      $rs=mysqli_query($conn,$sql);
      //echo $insertId; exit;
    	if($rs)
    	{
    	      $sqlQ="UPDATE `medicine_schedule` SET `notification`='N' WHERE scheduleId='".$scheduleId."'";
              $rsQ=mysqli_query($conn,$sqlQ);
              
    		echo '<script>
                 alert("Medicine update successfully");
                window.location.href="Medicinelist.php";
    		</script>';
    	}else{
         echo '<script>
                 alert("something went wrong.");
                window.location.href="updatemedicine.php?id='.$medId.'";
    		</script>';
    	}
    }else{
         echo '<script>
                 alert("medicine is out of stock.");
                window.location.href="Medicinelist.php";
    		</script>';
    }

}
?>