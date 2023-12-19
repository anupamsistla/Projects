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
  <?php include_once('header_links.php');?>
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
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>Admin/Dashboard"><i class="fas fa-tachometer-alt"></i> Home</a></li>
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i>User List</li>
            <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
          </ol>
        </nav>
        <div class="col-lg-8 p-r-0 title-margin-right" id="messageId">
    
       </div>
          <div class="section-body">
            <div class="row">
              <div class="col-12">
                <div class="card">
                 <div class="card-header">
                    <div class="col-6">
                      <h4>User List</h4>
                    </div>
                  </div>   
                  <div class="card-body">
                    <div class="table-responsive">
                      <table id="save-stage" class="table table-striped table-bordered" style="width:100%;">
                        <thead>
                         <tr id="header">
                           <!--<th><input type="checkbox" name="checkAll" id="checkAll"></th> -->
                            <th>S.No</th>
                            <th>Name</th>
                            <th>Username</th>
                            <th>Age</th>
                            <th>Medical Conditions</th>
                            <th>Doctor's Contact</th>  
                            <th>Email</th>
                            <th>Password</th>
                            <th>Gender</th>  
                            <th>Status</th>                            
                            <th>Action</th>

                        </tr>
                        </thead>
                        <tbody>

                          <?php include_once('../config.php'); 

                            $sql="SELECT * FROM `user` ";
                             $rs=mysqli_query($conn,$sql);
                             // $data=mysqli_fetch_array($rs);
                             $i=1;
                                 while ($data=mysqli_fetch_array($rs)) 
                                 {
                                    // print_r($key." => ".$value);data 
                                  ?>
                                      <tr>
                                          <td><?php echo $i;?></td>
                                          <td><?php echo $data['name'];?></td>
                                          <td><?php echo $data['username'];?></td>
                                          <td><?php echo $data['age'];?></td>
                                          <td><?php echo $data['medicalCondition'];?></td>
                                          <td><?php echo $data['doctorContact'];?></td>    
                                          <td><?php echo $data['email'];?></td>
                                          <td><?php echo $data['password'];?></td>
                                          <td><?php echo $data['gender'];?></td>
                                          <td><?php echo $data['status'];?></td>                            
                                          <td>
                                       <?php if($_SESSION['user_permission'][3]['moduleId']=='4' && $_SESSION['user_permission'][3]['permissionEdit']=='Y'){ ?>
                                            <a href="<?php echo $base_url;?>admin/updateUser.php?id=<?php echo $data['userId']; ?>"><i class="fa fa-edit"></i></a>
                                          <?php } ?>
                                       <?php if($_SESSION['user_permission'][3]['moduleId']=='4' && $_SESSION['user_permission'][3]['permissionStatus']=='Y'){ ?>
                                            <?php if($data['status']=='Active'){?>
                                            <a href="<?php echo $base_url;?>admin/actionUser.php?id=<?php echo $data['userId']; ?>&submit=update-status&status=<?php echo $data['status'];?>"><i class="fa fa-times"></i></a>
                                          <?php }else{?>
                                             <a href="<?php echo $base_url;?>admin/actionUser.php?id=<?php echo $data['userId']; ?>&submit=update-status&status=<?php echo $data['status'];?>"><i class="fa fa-check"></i></a>
                                          <?php }?>
                                        <?php }?>
                                        <?php if($_SESSION['user_permission'][3]['moduleId']=='4' && $_SESSION['user_permission'][3]['permissionDelete']=='Y'){ ?>
                                           <a href="<?php echo $base_url;?>admin/actionUser.php?id=<?php echo $data['userId']; ?>&submit=delete" onclick="return confirm('Do you want to delete this user?')"><i class="fa fa-trash"></i></a>
                                        <?php }?>
                                          </td>
                                      </tr>

                              <?php $i++; 
                            }  ?>                        
                        </tbody>
                      </table>
                    </div>
                  </div>
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