<?php
include_once('../config.php');

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
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>Component"><i class="far fa-file"></i>Component List</a></li>
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i> Add Component</li>
            <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
         </ol>
        </nav>
          <div class="col-lg-12 p-r-0 title-margin-right" id="messageId">
            <?php  if($this->session->flashdata('message')){
              ?>
               <div class="alert alert-danger" id="Sucsmsg"><?php echo $this->session->flashdata('message'); ?></div>
              <?php
            }?>
          <div>
          <div class="section-body">
               <div class="row">
              <div class="col-12 col-md-6 col-lg-12">
                <div class="card">
                  <?php echo form_open('Component/AddComponent',['Component'=>'form', 'id'=>'ComponentNewFrm', 'name'=>'ComponentNewFrm']);?>
                             <div class="card-header">
                                  <h4>Create Component</h4>
                                </div>
                                <div class="card-body form-page-validation">
                                    <div class="form-validation">
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="cmp_name">Name <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="cmp_name" name="cmp_name" placeholder="Enter name..">
                                                </div>
                                            </div>
                                          <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="cmp_view">Controller / Model / View Name<span class="text-danger">*</span></label>
                                                    <div class="col-lg-3">
                                                      <input type="text" class="form-control" id="cmp_controller" name="cmp_controller" placeholder="Enter name..">
                                                    </div>
                                                    <div class="col-lg-3">
                                                      <input type="text" class="form-control" id="cmp_model" name="cmp_model" placeholder="Enter name..">
                                                    </div>
                                                    <div class="col-lg-3">
                                                      <input type="text" class="form-control" id="cmp_view" name="cmp_view" placeholder="Enter name..">
                                                    </div>
                                             </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="cmp_favicon">Favicon <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="cmp_favicon" name="cmp_favicon" placeholder="Enter name..">
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="cmp_priority">Priority <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="cmp_priority" name="cmp_priority" placeholder="Enter name..">
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="cmp_activites">Component Activites <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <select class="js-select2 form-control" id="cmp_activites" name="cmp_activites" style="width: 100%;">
                                                      <option value="">Select Activity</option>
                                                        <?php foreach($CmpActivityList as $val){ ?>
                                                            <option value="<?php echo $val->cmpactivity_id;?>"><?= ucfirst($val->cmpactivity_name);?></option>
                                                      <?php }?>
                                                   </select>
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="cmp_parent_id">Parent <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                <select class="js-select2 form-control" id="cmp_parent_id" name="cmp_parent_id" style="width: 100%;">
                                                <option value="">Select Parent</option>
                                                   <?php foreach($CmpActiveList as $val){ ?>
                                                         <option value="<?php echo $val->cmp_id;?>"><?= $val->cmp_name;?></option>
                                                   <?php }?>
                                                   </select>
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="cmp_status">Status <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                <select class="js-select2 form-control" id="cmp_status" name="cmp_status" style="width: 100%;">
                                                        <option value="Y">Active</option>
                                                        <option value="N">In-Active</option>
                                                    </select>
                                                </div>
                                            </div>
                                            
                                        <div class="form-footer">
                                        <button type="submit" class="btn btn-primary" id="sbtcam">Add New</button>
                                        <a href="<?php echo $base_url;?>Component/" class="btn btn-danger">Cancel</a>
                                    </div>
                                    </div>
                                </div>
                      <?php echo form_close();?>
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