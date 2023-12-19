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
  <style>
    table.display {
      margin: 0 auto;
      width: 100%;
      clear: both;
      border-collapse: collapse;
      table-layout: fixed;         // add this 
      word-wrap:break-word;        // add this 
    }  
  </style>
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
            <li class="breadcrumb-item active" aria-current="page"><i class="fas fa-list"></i>Medicine List</li>
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
                      <h4>Medicine List</h4>
                    </div>
                 <?php if($_SESSION['user_permission'][4]['moduleId']=='5' && $_SESSION['user_permission'][4]['permissionAdd']=='Y'){ ?>
                      <div class="col-6" align="right">
                        <a href="<?php echo $base_url;?>admin/addMedcine.php" class="btn btn-info"> Add Medicne</a>
                    </div>
                 <?php } ?>
                  </div>  
                  <div class="card-body">
                    <div class="table-responsive" id="ajaxstatus">
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
                            <th>Stock</th> 
                            <th>Expiry Date</th>   
                            <th>Image</th>   
                            <th>Prescription</th> 
                            <th>Importance</th> 
                            <th>Doctor Contact</th> 
                            <th>Add Date</th>                            
                            <th>Action</th>
                        </tr>
                        </thead>
                        <tbody>

                    <?php
                        if($_SESSION['user']['userId']!='' && $_SESSION['user']['userId']!='1')
                        {
                            $sql="SELECT medicines.doctorContact,medicines.stock,medicines.quantity,medicines.prescription,medicines.userId,medicines.medicineId,medicine_schedule.scheduleId, medicine_schedule.day, 
                            medicine_schedule.medTime, medicines.name, medicines.type, medicines.medicalCondition, medicines.expiryDate, medicines.meansTotake, 
                            medicines.image, medicines.createdDate, medicines.updateDate,medicines.importance FROM medicines 
                            LEFT JOIN medicine_schedule ON medicines.medicineId=medicine_schedule.medicineId WHERE medicines.userId='".$_SESSION['user']['userId']."' ORDER BY medicines.medicineId ";
                        }else{
                            $sql="SELECT medicines.doctorContact,medicines.stock,medicines.quantity,medicines.prescription,medicines.userId,medicines.medicineId,medicine_schedule.scheduleId, medicine_schedule.day, 
                            medicine_schedule.medTime, medicines.name, medicines.type, medicines.medicalCondition, medicines.expiryDate, medicines.meansTotake, 
                            medicines.image, medicines.createdDate, medicines.updateDate,medicines.importance FROM medicines 
                            LEFT JOIN medicine_schedule ON medicines.medicineId=medicine_schedule.medicineId ORDER BY medicines.medicineId ";
                        }
                        $rs=mysqli_query($conn,$sql);
                        // $data=mysqli_fetch_array($rs);
                        // print_r($data);
                        // exit();
                        $i=1;
                                 while ($data=mysqli_fetch_array($rs)) 
                                 {
                                   // print_r($data);
                                  ?>
                                      <tr>
                                          <td><?php echo $i;?></td>
                                          <td><?php echo $data['name'];?></td>
                                          <td><?php echo $data['type'];?></td>
                                          <td><?php echo $data['medicalCondition'];?></td>
                                          <td><?php echo $data['day'];?></td>    
                                          <td><?php echo $data['medTime'];?></td>
                                          <td><?php echo $data['meansTotake'];?></td>
                                          <td><?php echo $data['quantity'];?></td>
                                          <td><?php echo $data['stock'];?></td>
                                          <td><?php echo date('d-m-Y',strtotime($data['expiryDate']));?></td>
                                          <td><?php if($data['image']!=''){  ?>
                                           <a href="<?php echo $base_url;?>uploads/<?php echo $data['image'];?>" target="_blank"><?php echo $base_url;?>uploads/<?php echo $data['image'];?>
                                          <?php } ?></a>
                                          </td>
                                           <td><?php if($data['prescription']!=''){  ?>
                                           <a href="<?php echo $base_url;?>uploads/<?php echo $data['prescription'];?>" target="_blank"> <?php echo $base_url;?>uploads/<?php echo $data['prescription'];?>
                                          <?php } ?></a>
                                          </td>
                                          <td><?php echo $data['importance'];?></td>
                                          <td><?php echo $data['doctorContact'];?></td>
                                          <td><?php echo date('d-m-Y',strtotime($data['createdDate']));?></td>                            
                                          <td>
                                         <?php if($_SESSION['user']['userId']!='1'){ ?>
                                            <a href="<?php echo $base_url;?>admin/actionMedicine.php?id=<?php echo $data['medicineId']; ?>&userid=<?php echo $data['userId']; ?>&schduleId=<?php echo $data['scheduleId']; ?>&submit=taken">Taken</a>
                                          <?php } if($_SESSION['user_permission'][4]['moduleId']=='5' && $_SESSION['user_permission'][4]['permissionEdit']=='Y'){ ?>
                                            <a href="<?php echo $base_url;?>admin/updatemedicine.php?id=<?php echo $data['medicineId']; ?>"><i class="fa fa-edit"></i></a>
                                          <?php } if($_SESSION['user_permission'][4]['moduleId']=='5' && $_SESSION['user_permission'][4]['permissionDelete']=='Y'){ ?>
                                            <a href="<?php echo $base_url;?>admin/actionMedicine.php?id=<?php echo $data['medicineId']; ?>&userid=<?php echo $data['userId']; ?>&submit=delete"><i class="fa fa-trash"></i></a>
                                          <?php } ?>
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
<script>
 $(document).ready(function() {
    
    var table = $('#bootstrap-data-table-export').DataTable( {
        lengthChange: true,
        //order: desc,
        order : [[ 1, 'desc' ]],
        buttons: [ 
        {
                extend: 'excelHtml5',      
                title: 'remembermedicines',
                filename: 'remembermedicines'
            },
              {
                extend: 'print',      
                title: 'remembermedicines',
                filename: 'remembermedicines'
            },
              {
                    extend: 'pdfHtml5',
                    orientation : 'landscape',
                    pageSize : 'LEGAL',
                    titleAttr : 'remembermedicines',
                    exportOptions: {
                        columns: [1,2,3,4,5,6,7,8,9,10,11,12,13,14]
                    },
                    customize : function(doc) {
                        doc.content[1].table.widths = [ '5%', '5%', '10%', '10%', '5%', '5%', '10%','5%', '5%', '10%', '10%', '5%', '5%', '5%'];
                    }
            },               
        ],
            lengthChange: true,
            dom: 'Blfrtip',
            // // lengthMenu: [ [10, 20, 50, -1], [10, 20, 50, "All"] ],
            // // pageLength: 20,
    } );
     
 
    $("#bootstrap-data-table-export tfoot th").each( function ( i ) {
        var select = $('<select id="option"><option value="">Select</option></select>')
            .appendTo( $(this).empty() )
            .on( 'change', function () {
                table.column( i )
                    .search( $(this).val() )
                    .draw();

            } );
 
        table.column( i ).data().unique().sort().each( function ( d, j ) {
            select.append( '<option value="'+d+'">'+d+'</option>' )
        } );
    } );
 
    table.buttons().container()
        .appendTo( '.new-buttons .col-md-12:eq(0)' );
           
           
    $('#container').css( 'display', 'block' );
    table.columns.adjust().draw();
});
</script>
</body>
</html>