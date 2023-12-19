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
      <?php include_once('headerbar.php');
            include_once('sidebar.php');
        ?>
      <!-- Main Content -->    
        <div class="main-content">         
          <section class="section">
              <nav aria-label="breadcrumb">
                <ol class="breadcrumb" id="border">
                  <li class="breadcrumb-item"><a href="<?php echo $base_url;?>Admin/Dashboard"><i class="fas fa-tachometer-alt"></i> Home</a></li>
                  <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i> Permission List</li>
                  <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
                </ol>
              </nav>
            <div class="section-body">
                <div class="row">
                    <div class="col-12 col-md-6 col-lg-12">
                        <div class="card">
                          <div class="card-header">
                              <div class="col-6">
                                <h4>Permission List</h4>
                              </div>
              <?php  if($_SESSION['user_permission'][2]['moduleId']=='3' && $_SESSION['user_permission'][2]['permissionAdd']=='Y') {?>                              
                              <div class="col-6" align="right">
                                    <a href="<?php echo $base_url?>admin/addModule.php"><button type="button" class="btn btn-primary">Add Module</button></a>
                               </div>
                      <?php }?>                       
                            </div>
                            
                        <?php
                           include_once('../config.php'); 
                           $sql="SELECT * FROM roles";
                           $rs=mysqli_query($conn,$sql);
                          
                          // print_r($data);
                        ?>
      
                            <form id="permissionfrm" name="permissionfrm"  method="post" action="<?php echo $base_url;?>admin/actionPermission.php">
                              <div class="card-body" >
                                     <div class="form-group">
                                        <strong>Role Name</strong>
                                        <select class="form-control" name="roleId" id="roleId">
                                              <option value="">Select Role</option>
                                            <?php while ($data=mysqli_fetch_assoc($rs)){?>
                                              <option value="<?php echo $data['roleId'];?>"><?php echo $data['roleName'];?></option>
                                              <?php }?>
                                          </select>
                                     </div>
                                    <div class="form-group">              
                                        <div class="table-responsive">
                                            <table  class="table table-striped table-bordered" style="width:100%;">
                                                 <thead>
                                                    <tr id="header">
                                                      <th scope="col"> <label>Select :</label> </th>
                                                      <th scope="col">
                                                        <label> View </label>
                                                      </th>
                                                    <th scope="col">
                                                        <label>Add </label>
                                                      </th>
                                                      <th scope="col">
                                                        <label> Update </label>
                                                      </th>
                                                      <th scope="col">
                                                        <label> Delete </label>
                                                      </th>
                                                      <th scope="col">
                                                        <label> Active/Inactive </label>
                                                      </th>     
                                                    </tr>
                                                  </thead>
                                                  <tbody class="ajaxstatus"> 
                                     
                                                   </tbody>
                                            </table> 
                                              <div class="form-footer">
                                                  <a href="<?php echo $base_url;?>admin/Permissionlist.php/" class="btn btn-danger">Clear</a>
                                           <?php if(($_SESSION['user_permission'][2]['moduleId']=='3' && $_SESSION['user_permission'][2]['permissionEdit']=='Y') || ($_SESSION['user_permission'][2]['moduleId']=='3' && $_SESSION['user_permission'][2]['permissionEdit']=='Y')) {?>  
                                                  <button type="submit" class="btn btn-primary"name="submit" value="Add-Permission">Save</button>
                                          <?php } ?>
                                              </div>
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
        <!-- end main content -->
    </div>
 </div>
<?php 
  include_once('footer_links.php');
?>
</body>
</html>