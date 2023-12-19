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
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>admin/Medicinelist.php"><i class="far fa-file"></i>Medicine List</a></li>
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i> Add Medicine</li>
            <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
         </ol>
        </nav>
          <div class="col-lg-12 p-r-0 title-margin-right" id="messageId">
         
          <div>
          <div class="section-body">
               <div class="row">
              <div class="col-12 col-md-6 col-lg-12">
                <div class="card">
                  <form action="<?php echo $base_url;?>admin/actionMedicine.php" name="addMedicine" id="addMedicine" method="post" enctype="multipart/form-data">
                             <div class="card-header">
                                  <h4>Add Medicine</h4>
                                </div>
                                <div class="card-body form-page-validation">
                                    <div class="form-validation">
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="name">Medicine Name <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="name" name="name" placeholder="Enter name.." required>
                                                </div>
                                            </div>
                                          <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="type">Medicine Type<span class="text-danger">*</span></label>
                                                    <div class="col-lg-8">
                                                      <input type="text" class="form-control" id="type" name="type" placeholder="Enter Medicine Type.." required />
                                                    </div>
                                             </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="medicalCondition">Medical Condition <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="medicalCondition" name="medicalCondition" placeholder="Enter Medical Condition.." required />
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="day">Day <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <select  id="day" name="day[]" class="form-control selectric" multiple="">
                                                        <option value="">Select Day</option>
                                                        <option value="monday">Monday</option>
                                                        <option value="tuesday">Tuesday</option>
                                                        <option value="wednesday">Wednesday</option>
                                                        <option value="thursday">Thursday</option>
                                                        <option value="friday">Friday</option>
                                                        <option value="saturday">Saturday</option>
                                                        <option value="sunday">Sunday</option>
                                                    </select>
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="medTime">Time <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control timepicker" id="medTime" name="medTime" placeholder="Enter Medicine Time.."  required />                                                   
                                                </div>
                                            </div>
                                             <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="expiryDate"> Expiry Date <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="date" class="form-control" id="expiryDate" name="expiryDate" placeholder="Enter Expiry Date.." required />
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="meansTotake"> Means To Take <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="meansTotake" name="meansTotake" placeholder="Enter Means To Take.." required />
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="quantity"> Quantity <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="quantity" name="quantity" placeholder="ex: 1 spoon, 1 ML, 1 Tablet, 1 Puff..." required />
                                                </div>
                                            </div>
                                            
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="stock"> Stock <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="stock" name="stock" placeholder="ex: Stock of medicine.." required />
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="image">Image <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                 <input type="file" class="form-control" id="image" name="image" placeholder="Enter Medicine Image.." required />
                                                </div>
                                            </div>

                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="prescription">Prescription </label>
                                                <div class="col-lg-8">
                                                 <input type="file" class="form-control" id="prescription" name="prescription" placeholder="Enter Medicine Prescription..">
                                                </div>
                                            </div>
                                            
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="importance"> Importance</label>
                                                <div class="col-lg-8">
                                                    <select name="importance" id="importance" class="form-control" required />
                                                        <option value="">Select Importance</option>
                                                        <option value="Not Important">Not Important</option>
                                                        <option value="Moderate">Moderate</option>
                                                        <option value="Very Important">Very Important</option>
                                                    </select>
                                                </div>
                                            </div>
                                        
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="doctorContact">Doctor Contact <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                   <input type="text" class="form-control" id="doctorContact" name="doctorContact" placeholder="Enter Doctor Contact.." >
                                                </div>
                                            </div>    
                                        <input type="hidden" name="userId" value="<?php echo $_SESSION['user']['userId'];?>">
                                        <div class="form-footer">
                                        <button type="submit" class="btn btn-primary" value="Add-Medicine" name="submit">Add New</button>
                                        <a href="<?php echo $base_url;?>admin/Medicinelist.php" class="btn btn-danger">Cancel</a>
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