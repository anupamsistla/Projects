
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
