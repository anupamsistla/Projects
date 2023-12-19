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
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i>Role List</li>
            <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
        </ol>
        </nav>
        
          <div class="section-body">
            <div class="row">
              <div class="col-12">
                <div class="card">
                  <div class="card-header">
                    <div class="col-6">
                    <h4>Role List</h4>
                   </div>
              <?php  if($_SESSION['user_permission'][1]['moduleId']=='2' && $_SESSION['user_permission'][1]['permissionAdd']=='Y') {?>  
                    <div class="col-6" align="right">
                    <a href="<?php echo $base_url?>admin/addrole.php"><button type="button" class="btn btn-primary">Add New Role</button></a>
                   </div>
               <?php } ?>    
                   
                  </div>
                  <div class="card-body">
                    <div class="table-responsive">
                      <table id="save-stage" class="table table-striped table-bordered" style="width:100%;">
                        <thead>
                          <tr> <th>Serial No.</th>
                              <th>Role Name</th>
                              <th>Role Status</th>
                              <th>Add Date</th>
                              <th>Action</th>
                        </tr>
                        </thead>
                        <tbody>
                       <?php
                       $i=1;
                       $sql="SELECT * FROM roles";
                       $rs=mysqli_query($conn,$sql);
                       while($data=mysqli_fetch_assoc($rs))
                       {
                       ?>
                              <tr>
                                  <td><?php echo $i;?></td> 
                                  <td><?php echo $data['roleName'];?></td>
                                  <td><?php echo $data['roleStatus'];?></td>
                                  <td><?php echo date('d-m-Y',strtotime($data['createdDate']));?></td>
                                  <td>
                                 <?php    if($_SESSION['user_permission'][1]['moduleId']=='2' && $_SESSION['user_permission'][1]['permissionEdit']=='Y') {?>  
                                    <a href="<?php echo $base_url;?>admin/UpdateRole.php?id=<?=$data['roleId'];?>" title="Edit"><span class="fas fa-edit"></span> </a>   &nbsp;
                                 <?php }  if($_SESSION['user_permission'][1]['moduleId']=='2' && $_SESSION['user_permission'][1]['permissionDelete']=='Y') {?>  
                                    <a href="<?php echo $base_url;?>admin/actionRole.php?id=<?=$data['roleId'];?>&submit=Delete" title="Delete" onclick="return confirm('Do you want to delete this role?')"><span class="fas fa-trash-alt"></span></a>
                                 <?php } ?>
                                  </td>
                              </tr>  
                              <?php $i++;
                              } ?>
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