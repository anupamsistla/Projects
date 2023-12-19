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
            <li class="breadcrumb-item"><a href="<?php echo $base_url;?>admin/Medicinelist.php"><i class="far fa-file"></i>Medicine List</a></li>
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i>Update Medicine</li>
            <li class="breadcrumb-item"><span class="backbtn"  onclick="goBack()">Go Back</span></li>
         </ol>
        </nav>
          <div class="col-lg-12 p-r-0 title-margin-right" id="messageId">
         
          <div>
      <?php //echo $_GET['id'];
          include_once('../config.php');
          $sql="SELECT  user.name as userName,medicines.quantity,stock,medicines.prescription,medicines.userId,medicines.medicineId, medicine_schedule.day, medicine_schedule.medTime, medicines.name, medicines.type, medicines.medicalCondition, medicines.expiryDate, medicines.meansTotake, medicines.image, medicines.createdDate, medicines.updateDate,medicines.importance FROM medicines LEFT JOIN medicine_schedule ON medicines.medicineId=medicine_schedule.medicineId LEFT JOIN user ON medicines.userId=user.userId WHERE medicines.medicineId='".$_GET['id']."'";
          $rs=mysqli_query($conn,$sql);
          $data=mysqli_fetch_assoc($rs);
      // print_r($data);
      // exit;
      ?>           
          <div class="section-body">
               <div class="row">
              <div class="col-12 col-md-6 col-lg-12">
                <div class="card">
                  <form action="<?php echo $base_url;?>admin/actionMedicine.php" name="updateMedicine" id="updateMedicine" method="post" enctype="multipart/form-data">
                             <div class="card-header">
                                  <h4>Update Medicine</h4>
                                </div>
                                <div class="card-body form-page-validation">
                                    <div class="form-validation">
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="name">Medicine Name <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="name" name="name" placeholder="Enter name.." value="<?php echo $data['name']?>">
                                                </div>
                                            </div>
                                          <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="type">Medicine Type<span class="text-danger">*</span></label>
                                                    <div class="col-lg-8">
                                                      <input type="text" class="form-control" id="type" name="type" placeholder="Enter Medicine Type.." value="<?php echo $data['type']?>">
                                                    </div>
                                             </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="medicalCondition">Medical Condition <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="medicalCondition" name="medicalCondition" placeholder="Enter Medical Condition.." value="<?php echo $data['medicalCondition']?>">
                                                </div>
                                            </div>
                                            
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="day">Day <span class="text-danger">*</span></label>
                                                <div class="col-lg-8 form-group">
                                                    <select class="form-control selectric" id="day" name="day" multiple="">
                                                        <option value="">Select Day</option>
                                                        <option value="monday"<?php if($data['day']=='monday'){echo "selected";}?>>Monday</option>
                                                        <option value="tuesday"<?php if($data['day']=='tuesday'){echo "selected";}?>>Tuesday</option>
                                                        <option value="wednesday"<?php if($data['day']=='wednesday'){echo "selected";}?>>Wednesday</option>
                                                        <option value="thursday"<?php if($data['day']=='thursday'){echo "selected";}?>>Thursday</option>
                                                        <option value="friday"<?php if($data['day']=='friday'){echo "selected";}?>>Friday</option>
                                                        <option value="saturday"<?php if($data['day']=='saturday'){echo "selected";}?>>Saturday</option>
                                                        <option value="sunday"<?php if($data['day']=='sunday'){echo "selected";}?>>Sunday</option>
                                                    </select>
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="medTime">Time <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control timepicker" id="medTime" name="medTime" placeholder="Enter Medicine Time.." value="<?php echo $data['medTime']?>">                                                   
                                                </div>
                                            </div>
                                             <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="expiryDate"> Expiry Date <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="date" class="form-control" id="expiryDate" name="expiryDate" placeholder="Enter Expiry Date.." value="<?php echo $data['expiryDate']?>">
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="meansTotake"> Means To Take <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="meansTotake" name="meansTotake" placeholder="Enter Means To Take.." value="<?php echo $data['meansTotake']?>">
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="quantity"> Quantity <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" id="quantity" name="quantity" placeholder="ex: 1 spoon, 1 ML, 1 Tablet, 1 Puff..." value="<?php echo $data['quantity']?>">
                                                </div>
                                            </div>
                                            
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="stock"> Stock <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                    <input type="text" class="form-control" value="<?php echo $data['stock'];?>" id="stock" name="stock" placeholder="ex: Stock of medicine.." required />
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="image">Image <span class="text-danger">*</span></label>
                                                <div class="col-lg-6">
                                                 <input type="file" class="form-control" id="image" name="image" placeholder="Enter Medicine Image.." >
                                                </div>
                                                <div class="col-lg-4">
                                               <img src="<?php echo $base_url;?>uploads/<?php echo $data['image'];?>" alt="<?php echo $data['image']?>"  width="60" height="60"/>
                                                </div>
                                            </div>
                                            
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="prescription">Prescription </label>
                                                <div class="col-lg-6">
                                                 <input type="file" class="form-control" id="prescription" name="prescription" placeholder="Enter Prescription.." >
                                                </div>
                                                <div class="col-lg-4">
                                               <img src="<?php echo $base_url;?>uploads/<?php echo $data['prescription'];?>" alt="<?php echo $data['prescription']?>"  width="60" height="60"/>
                                                </div>
                                            </div>
                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="importance"> Importance</label>
                                                <div class="col-lg-8">
                                                    <select name="importance" id="importance" class="form-control">
                                                        <option value="">Select Importance</option>
                                                        <option value="Not Important"<?php if($data['importance']=='Not Important'){echo "selected";}?>>Not Important</option>
                                                        <option value="Moderate"<?php if($data['importance']=='Moderate'){echo "selected";}?>>Moderate</option>
                                                        <option value="Very Important"<?php if($data['importance']=='Very Important'){echo "selected";}?>>Very Important</option>
                                                    </select>
                                                </div>
                                            </div>

                                            <div class="form-group row">
                                                <label class="col-lg-2 col-form-label" for="doctorContact">Doctor Contact <span class="text-danger">*</span></label>
                                                <div class="col-lg-8">
                                                   <input type="text" class="form-control" id="doctorContact" name="doctorContact" placeholder="Enter Doctor Contact.." value="<?php echo $data['doctorContact']?>">
                                                </div>
                                            </div>
                                            
                                            <input type="hidden" name="userId" id="userId" value="<?php echo $data['userId'];?>">
                                            <input type="hidden" name="medId" id="medId" value="<?php echo $data['medicineId'];?>">
                                            <input type="hidden" name="filename" id="filename" value="<?php echo $data['image'];?>">
                                            <input type="hidden" name="presname" id="presname" value="<?php echo $data['prescription'];?>">
                                        <div class="form-footer">
                                        <button type="submit" class="btn btn-primary" value="Update-Medicine" name="submit">Update</button>
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