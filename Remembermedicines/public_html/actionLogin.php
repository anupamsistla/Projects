<?php  require_once('config.php');

 //print_r($_POST); exit;
if($_POST['login']=='Sign Up')
{
    $sql = "SELECT * FROM `user` WHERE email = '$_POST[email]'";
    $rs=mysqli_query($conn,$sql);
    $data =mysqli_fetch_assoc($rs); 
     
    if($data == 0 || $data =="")
    {
            
           $name= $_POST['name'];
           $email= $_POST['email'];
           $password= $_POST['password'];
           $username= $_POST['username'];
           
           $age= $_POST['age'];
           $gender= $_POST['gender'];
           $medicalCondition= $_POST['medicalCondition'];
           
        
            $date=date('Y-m-d');
          $sql="INSERT INTO  `user`(`name`, `username`, `email`, `password`,`age`, `gender`, `medicalCondition`, `status`, `createdDate`)  
                              VALUEs('".$name."','".$username."'  ,'".$email."' ,'".$password."','".$age."','".$gender."'  ,'".$medicalCondition."' ,'Active','".$date."')";
        
          $rs=mysqli_query($conn,$sql);
        	if($rs)
        	{
        		echo '<script>
                     alert("User registered successfully");
                    window.location.href="login.php";
        		</script>';
        	}else{
             echo '<script>
                     alert("something went wrong.");
                    window.location.href="signup.php";
        		</script>';
        	}
     }else{
        echo ("<script LANGUAGE='JavaScript'>
           alert('you are already registered user');
                   window.location.href='signup.php';
                    </script>");
                                
          }
    
            

}
if($_POST['login']=='LOGIN')
{
    if($_POST['email']!=""  || $_POST['password'] !="")
    {
            $sql = "SELECT * FROM `user` WHERE email = '$_POST[email]'";
            $rs=mysqli_query($conn,$sql);
            $data =mysqli_fetch_assoc($rs); 
             
            if($data > 0 || $data !="")
            {
                   $email= $_POST['email'];
                   $password= $_POST['password'];
                
                   $sql="SELECT * FROM `user` WHERE email='".$email."' AND password='".$password."' AND  status='Active'";
                   $rs=mysqli_query($conn,$sql);
                   $data=mysqli_num_rows($rs);
                   $userdata=mysqli_fetch_assoc($rs);
                  if($data > 0 || $data !="")
                  {
                      $list=array();
                      
                           $_SESSION['user']=$userdata;
                           
                           $sql2="SELECT * FROM `permission` WHERE roleId='".$userdata['userType']."'";
                           $rs2=mysqli_query($conn,$sql2);
                           while($data2=mysqli_fetch_assoc($rs2)){
                               $modulelist[]=$data2;
                           }
                           $list=$modulelist;
                           $_SESSION['user_permission']=$list;
                           
                        //   echo "<pre>";
                        //   print_r($_SESSION);
                        //   echo "</pre>";
                        
                      echo '<script>
                              window.location.href="admin/Dashboardlist.php";
                    </script>';
                    
                  }else{
                      $userdata=array();
                      $data2=array();
                       $_SESSION['user']=$userdata;
                       $_SESSION['user_permissions']=$data2;
                       
                     echo '<script>
                             alert("Incorrect email or password");
                            window.location.href="login.php";
                    </script>';
                  }
            }else{
                
                echo ("<script LANGUAGE='JavaScript'>
                   alert('you are not registered user');
                           window.location.href='signup.php';
                            </script>");
                                        
                  }
            
      }else{
            echo ("<script LANGUAGE='JavaScript'>
               alert('Email and Password both required');
                       window.location.href='login.php';
                        </script>");
                                    
              }
                      

}
?>