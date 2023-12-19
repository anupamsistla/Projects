<?php include_once('../config.php');

if($_SESSION['user']=="" && $_SESSION['user_permission']=="")
{
   echo '<script>
             alert("Please login first.");
            window.location.href="../../login.php";
    </script>';
    exit;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
<?php include_once('header_links.php'); ?> 
</head>

<body>
  
  <div id="app">
    <div class="main-wrapper main-wrapper-1">     
     <?php 
          include_once('headerbar.php');
          include_once('sidebar.php');
          
          
       $sql0="SELECT medicineId FROM medicines WHERE userId='".$_SESSION['user']['userId']."'";
       $rs0=mysqli_query($conn,$sql0);
       $data0=mysqli_num_rows($rs0);
        if($data0=='0' || $data0=="")
        {
            $data0='0';
        }
   
        $date=date('Y-m-d');
        $Today=strtolower(date('l', strtotime($date)));
 
       $sql1="SELECT medicines.userId,medicines.medicineId,medicine_schedule.day,medicine_schedule.scheduleId,medicine_schedule.medTime,medicines.createdDate,medicines.updateDate
       FROM `medicines` LEFT JOIN medicine_schedule on medicines.medicineId=medicine_schedule.medicineId WHERE medicines.userId='".$_SESSION['user']['userId']."' AND medicine_schedule.day LIKE '%$Today%'";
       $rs1=mysqli_query($conn,$sql1);
       $data1=mysqli_num_rows($rs1);
       if($data1=='0' || $data1=="")
        {
            $data1='0';
        }
      
 ?>      
      <!-- Main Content -->
      <div class="main-content">
        <section class="section">
          <div class="row ">
            <div class="col-xl-12 col-lg-12 col-md-12 col-sm-12 col-xs-12">
             <div class="card">
                <div class="card-statistic-4" align="center">
                  <div class="align-items-center justify-content-between">
                    <div class="row ">
                      <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12 pr-0 pt-10">
                        <div class="card-content">
                          <h5 class="font-15" style="padding-top:35px;">Number of Medicines : <?=$data0;?></h5>
                        </div>
                      </div>
                      <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12">
                        <div class="banner-img">
                          <img src="<?php echo $base_url;?>assets/admin/img/banner/download.jpg" alt="" style="max-width:30%;" >
                        </div>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
             
            <!--tabs end -->
          </div> 
            <!--tabs row end --> 
                 <div class="row input-daterange"> 
                    <div class="col-xl-8 col-lg-8 col-md-8 col-sm-12 col-xs-12 ">
                      <input type="text" name="meds" id="meds"  value="<?php if(isset($_POST['meds'])){echo $_POST['meds']; }?>" class="form-control timepicker" autocomplete="off" placeholder="Medicine Time">
                    </div>
                    
                     <div class="col-xl-1 col-lg-1 col-md-1 col-sm-6 col-xs-6 "  >
                      <input type="submit" name="search" id="search" value="Search" class="btn btn-info">
                     </div>
                      <div class="col-xl-1 col-lg-2 col-md-2 col-sm-6 col-xs-6 " >
                      <input type="reset" name="reset" id="reset" value="Clear" class="btn btn-info" onclick="fnResetAllFilters();">
                     </div>          
             </div>
        </section>
    <section class="filterData" style="margin-top:20px;">
        <div class="section-body">
            <div class="row">
              <div class="col-12">
                <div class="card">
                 <div class="card-header">
                    <div class="col-6">
                      <h4>Medicine List</h4>
                    </div>
                  </div>  
                  <div class="card-body">
                    <div class="table-responsive" >
                      <table id="bootstrap-data-table-export" class="table table-striped table-bordered" style="width:100%;">
                        <thead>
                         <tr id="header">
                           <!--<th><input type="checkbox" name="checkAll" id="checkAll"></th> -->
                            <th>S.No</th>
                            <th>Name</th>
                            <th>Type</th>
                            <th>Medical Conditions</th>
                            <th>Day</th>
                            <th>Time</th>  
                            <th>Means to Take</th>
                            <th>Quantity</th> 
                            <th>Expiry Date</th>   
                            <th>Image</th>   
                            <th>Prescription</th> 
                            <th>Importance</th> 
                            <th>Add Date</th>                            
                            <th>Action</th>
                        </tr>
                        </thead>
                        <tbody id="ajaxstatus">
                
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
<script>
    
$(document).ready(function() {
  $("#search").click(function(){
  // alert("hello");
    var meds =$("#meds").val();

        $.ajax({
         url:'datafilter.php',
         method:'POST',
         data:{ 
            meds:meds,
         },
         success:function(data)
         {
            //  alert(data); 
          if(data){
            //   $('.filterData').show();
              $("#ajaxstatus").html(data);
            }
            else{
              $('.filterData').hide();
            alert("Data not found");  
            }
         }
      });
   });
 
 });

 function fnResetAllFilters() {

          $('.filterData').hide();       
     
   }

</script>
</body>
</html>