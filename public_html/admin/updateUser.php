<?php include_once('../config.php');

if($_SESSION['user']=="" && $_SESSION['user_permission']=="")
{
   echo '<script>
             alert("Please login first.");
            window.location.href="../../login.php";
    </script>';
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <?php 
include_once('header_links.php');
?>
</head>

<body>
  
  <div id="app">
    <div class="main-wrapper main-wrapper-1">
     <?php 
          include_once('headerbar.php');
          include_once('sidebar.php');
       ?>
      <!-- Main Content -->
    
      <div class="main-content">         
        <section class="section">
         <nav aria-label="breadcrumb">
          <ol class="breadcrumb" id="border">
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>Admin/Dashboardlist.php"><i class="fas fa-tachometer-alt"></i> Home</a></li>
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>admin/Userlist.php"><i class="far fa-file"></i>User List</a></li>
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i> Update Profile</li>
            <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
         </ol>
        </nav>
          <div class="col-lg-12 p-r-0 title-margin-right" id="messageId">
         
          <div>
<?php //echo $_GET['id'];
include_once('../config.php');
$sql="SELECT `userId`,  `userType`,`name`, `username`, `email`, `password`, `gender`, `age`, `medicalCondition`, `doctorContact`, `status`, `createdDate`, `updateDate` FROM user WHERE userId='".$_GET['id']."'";
$rs=mysqli_query($conn,$sql);
$data=mysqli_fetch_assoc($rs);
// print_r($data);
//exit;
?>           
          <div class="section-body">
               <div class="row">
              <div class="col-12 col-md-6 col-lg-12">
                <div class="card">
                  <form action="<?php echo $base_url;?>admin/actionUser.php" name="updateUser" id="updateUser" method="post" enctype="multipart/form-data">
                             <div class="card-header">
                                  <h4>Update Profile</h4>
                                </div>
                                <div class="card-body form-page-validation">
                                    <div class="form-validation">
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="name">User Name <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="name" name="name" placeholder="Enter name.." value="<?php echo $data['name']?>">
                                                </div>
                                            </div>
                                          <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="type">Username<span class="text-danger">*</span></label>
                                                    <div class="col-lg-8">
                                                      <input type="text" class="form-control" id="username" name="username" placeholder="Enter Username.." value="<?php echo $data['username']?>">
                                                    </div>
                                             </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="email">Email <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="email" name="email" placeholder="Enter Email.." value="<?php echo $data['email']?>">
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="password">Password <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="password" name="password" placeholder="Enter Password.." value="<?php echo $data['password']?>">
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="gender">Gender <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="gender" name="gender" placeholder="Enter Medicine Gender.." value="<?php echo $data['gender']?>">                                                   
                                                </div>
                                            </div>
                                             <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="age"> Age <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="type" class="form-control" id="age" name="age" placeholder="Enter Age.." value="<?php echo $data['age']?>">
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="medicalCondition"> Medical Condition <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="medicalCondition" name="medicalCondition" placeholder="Enter Medical Condition.." value="<?php echo $data['medicalCondition']?>">
                                                </div>
                                            </div>
                                            
                                            <input type="hidden" name="userType" id="userType" value="<?php echo $data['userType'];?>">
                                            <input type="hidden" name="userId" id="userId" value="<?php echo $data['userId'];?>">
                                        <div class="form-footer">
                                        <button type="submit" class="btn btn-primary" value="Update-User" name="submit">Update</button>
                                        <a href="<?php echo $base_url;?>admin/Userlist.php" class="btn btn-danger">Cancel</a>
                                    </div>
                                    </div>
                                </div>
                         </form>
                      </div>
                  </div>
                </div>
              </div>
        </section>
      </div>
    </div>
  </div>
<?php 
  include_once('footer_links.php');
?>
</body>

</html>