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
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>Admin/Dashboard"><i class="fas fa-tachometer-alt"></i> Home</a></li>
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>admin/Rolelist.php"><i class="far fa-file"></i>Role List</a></li>
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i> Update Role</li>
            <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
         </ol>
        </nav>
        <?php
         include_once('../config.php');
         $id= $_GET['id'];
         $sql="SELECT * FROM roles WHERE `roleId`='".$id."'";
         $rs=mysqli_query($conn,$sql);
         $data=mysqli_fetch_assoc($rs);
         ?>
          <div class="section-body">
               <div class="row">
              <div class="col-12 col-md-6 col-lg-12">
                <div class="card">
                  <form action="<?php echo $base_url; ?>admin/actionRole.php" id="RoleNewFrm" name="RoleNewFrm" method="post">
                             <div class="card-header">
                                  <h4>Update Role</h4>
                                </div>
                                <div class="card-body form-page-validation">
                                    <div class="form-validation">
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="roleName">Role Name <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="roleName" name="roleName" placeholder="Enter name.." value="<?php echo $data['roleName'];?>">
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="roleStatus">Role Status <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                <select class="js-select2 form-control" id="roleStatus" name="roleStatus" style="width: 100%;">
                                                         <option value="">Select Status</option>
                                                        <option value="Active"<?php if($data['roleStatus']=='Active'){ echo "selected"; }?>>Active</option>
                                                        <option value="Inactive"<?php if($data['roleStatus']=='Inactive'){ echo "selected"; }?>>In-Active</option>
                                                    </select>
                                                </div>
                                            </div>
                                            <input type="hidden" name="roleId" id="roleId" value="<?=$id;?>">
                                        <div class="form-footer">
                                        <button type="submit" class="btn btn-primary" name="submit" value="Update-Role">Update</button>
                                        <a href="<?php echo $base_url;?>admin/updaterole.php" class="btn btn-danger">Cancel</a>
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