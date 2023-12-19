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
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>admin/Dashboardlist.php"><i class="fas fa-tachometer-alt"></i> Home</a></li>
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>admin/Permissionlist.php"><i class="far fa-file"></i>Module List</a></li>
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i> Add Module</li>
            <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
         </ol>
        </nav>
          <div class="section-body">
               <div class="row">
              <div class="col-12 col-md-6 col-lg-12">
                <div class="card">
                  <form action="<?php echo $base_url; ?>admin/actionPermission.php" id="ModuleNewFrm" name="ModuleNewFrm" method="post">
                             <div class="card-header">
                                  <h4>Create Module</h4>
                                </div>
                                <div class="card-body form-page-validation">
                                    <div class="form-validation">
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="moduleName">Module Name <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="moduleName" name="moduleName" placeholder="Enter name..">
                                                </div>
                                            </div>
                                        <div class="form-footer">
                                        <button type="submit" class="btn btn-primary" name="submit" value="Add-Module">Add New</button>
                                        <a href="<?php echo $base_url;?>admin/addModule.php" class="btn btn-danger">Cancel</a>
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