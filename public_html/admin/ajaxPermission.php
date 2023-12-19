<?php include_once('../config.php');

if($_SESSION['user']=="" && $_SESSION['user_permission']=="")
{
   echo '<script>
             alert("Please login first.");
            window.location.href="../../login.php";
    </script>';
}
?>
                      <tr><?php
                                  
                                      $sql1="SELECT * FROM module"; 
                                            $rs1=mysqli_query($conn,$sql1);
                                             $data0=mysqli_num_rows($rs1);
                                             if($data0 > 0)
                                             {
                                                while($data1=mysqli_fetch_assoc($rs1))
                                                {
                                                  $sql2="SELECT * FROM permission WHERE moduleId='".$data1['moduleId']."' AND roleId='".$_POST['id']."'"; 
                                                    $rs2=mysqli_query($conn,$sql2);
                                                    $data2=mysqli_fetch_assoc($rs2);
                                                // print_r($data2);        
                                                    
                                                  ?>
                                                                <td scope="row">
                                                                    <?php echo $data1['moduleName'];?>
                                                                </td>               
                                                                    <td>
                                                                    <input type="checkbox" name="permissionView.<?php echo $data1['moduleId'];?>"  class="view_class" value="Y"   <?php  if($data2['permissionView']=='Y'){ echo "checked"; }?> />      
                                                                    </td>
                                                                    <td>
                                                                    <input type="checkbox" name="permissionAdd.<?php echo $data1['moduleId'];?>" class="add_class" value="Y"  <?php if($data2['permissionAdd']=='Y'){  echo "checked"; }?> /> 
                                                                    </td>
                                                                    <td>
                                                                    <input type="checkbox" name="permissionEdit.<?php echo $data1['moduleId'];?>" class="edit_class" value="Y"   <?php if($data2['permissionEdit']=='Y'){  echo "checked"; }?> />  
                                                                    </td>
                                                                    <td>
                                                                    <input type="checkbox" name="permissionDelete.<?php echo $data1['moduleId'];?>"  class="delete_class" value="Y"   <?php if($data2['permissionDelete']=='Y'){   echo "checked"; }?> />      
                                                                    </td>
                                                                    <td>
                                                                    <input type="checkbox" name="permissionStatus.<?php echo $data1['moduleId'];?>"  class="actInactive_class" value="Y"   <?php if($data2['permissionStatus']=='Y'){ echo "checked";  }?> />      
                                                                    </td>
                                                            </tr>
                                                            
                                                          <input type="hidden" name="role" id="role" value="<?=$_POST['id'];?>">
                                                    <?php }
                                                    
                                                    }else{ ?>
                                                    <tr>
                                                        
                                                    Data not found
                                                        
                                                    </tr>
                                                    
                                                    
                                                    <?php }?>