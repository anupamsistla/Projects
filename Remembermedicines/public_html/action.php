<?php  require_once('config.php');
// require_once('action.class.php');


if (isset($_GET['code'])) {
    $token = $gClient->fetchAccessTokenWithAuthCode($_GET['code']);
}else{
     echo '<script>
            window.location.href="index.php";
		</script>';
    exit();
}

$oAuth = new Google_Service_Oauth2($gClient);
$userData = $oAuth->userinfo_v2_me->get();
if(isset($token["error"]) && ($token["error"] != "invalid_grant")){
    // get data from google
         echo '<script>
                 alert("Incorrect email or password");
                window.location.href="login.php";
        </script>';
}else{
    
   $sql = "SELECT * FROM `user` WHERE email = '$userData[email]'";
    $rs=mysqli_query($conn,$sql);
    $data =mysqli_fetch_assoc($rs); 
    
    if($data > 0 || $data !="")
    {
         
           $sql="SELECT * FROM `user` WHERE email='".$userData['email']."' AND  status='Active'";
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
    
    exit();
}



?>