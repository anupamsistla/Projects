<!-- scripit init-->
   <script>var SITEURL = '<?php echo $base_url; ?>';</script>

  <!-- scripit init-->
  <script src="<?php echo $base_url;?>assets/admin/js/app.min.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/apexcharts/apexcharts.min.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/bootstrap-daterangepicker/daterangepicker.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/bootstrap-timepicker/js/bootstrap-timepicker.min.js" defer></script>

  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/bootstrap-tagsinput/dist/bootstrap-tagsinput.min.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/select2/dist/js/select2.full.min.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/jquery-selectric/jquery.selectric.min.js" defer></script>
  
<!-- Page Specific JS File -->
  <script src="<?php echo $base_url;?>assets/admin/bundles/datatables/datatables.min.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/datatables/DataTables-1.10.16/js/dataTables.bootstrap4.min.js" defer></script> 
  <script src="<?php echo $base_url;?>assets/admin/js/page/datatables.js" defer></script>
  

  <script src="<?php echo $base_url;?>assets/admin/bundles/datatables/export-tables/dataTables.buttons.min.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/datatables/export-tables/buttons.flash.min.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/datatables/export-tables/pdfmake.min.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/datatables/export-tables/vfs_fonts.js" defer></script>
  <script src="<?php echo $base_url;?>assets/admin/bundles/datatables/export-tables/buttons.print.min.js" defer></script>
  
    <script src="<?php echo $base_url;?>assets/admin/js/scripts.js" defer></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-validate/1.17.0/jquery.validate.js" defer></script>
    <script src="<?php echo $base_url;?>assets/js/signup_validation.js" defer></script>
<script>  
$(document).ready(function(){
  $("#roleId").change(function(){
     var roldId=$("#roleId").val();
     
     $.ajax({
           url:'ajaxPermission.php',
        method:'POST',
          data:{id:roldId},
       success:function(data)
       {
          $(".ajaxstatus").html(data);
          $("#role").val(roldId);
       }
    });
  });
});

</script>