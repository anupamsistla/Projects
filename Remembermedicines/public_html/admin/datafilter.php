<?php 
include_once('../config.php');
       
global $conn;

$meds= $_POST['meds'];

 $var="";
if($_SESSION['user']['userId']!='' && $_SESSION['user']['userId']!='1')
{
  $var=" AND  medicines.userId='".$_SESSION['user']['userId']."'";
}
        
               if($meds!='')
               {
                   date_default_timezone_set('Asia/Kolkata');
        
                    $date=date('Y-m-d');
                    $Today=strtolower(date('l', strtotime($date)));
                    
                    $firstTime = (new DateTime)->format($meds);
                    $minutes_to_add = 60;
                    $time = new DateTime($meds);
                    $time->add(new DateInterval('PT' . $minutes_to_add . 'M'));
                    $secondTime = $time->format('H:i:s');
              
                   $sql1="SELECT medicines.type,medicines.medicalCondition,medicines.quantity,medicines.image,medicines.prescription,medicines.importance,medicines.name,medicines.meansTotake,medicines.userId,medicines.medicineId,medicine_schedule.day,medicine_schedule.scheduleId,medicine_schedule.medTime,medicines.createdDate,medicines.updateDate
                       FROM `medicines` LEFT JOIN medicine_schedule on medicines.medicineId=medicine_schedule.medicineId 
                       WHERE FIND_IN_SET('$Today', medicine_schedule.day) AND medicine_schedule.medTime >= '$firstTime' AND medicine_schedule.medTime <= '$secondTime' $var  ORDER BY medicines.medicineId ";
               
               }else{
                       $sql = "SELECT medicines.type,medicines.medicalCondition,medicines.quantity,medicines.image,medicines.prescription,medicines.importance,medicines.name,medicines.meansTotake,medicines.userId,medicines.medicineId,medicine_schedule.day,medicine_schedule.scheduleId,medicine_schedule.medTime,medicines.createdDate,medicines.updateDate
                       FROM `medicines` LEFT JOIN medicine_schedule on medicines.medicineId=medicine_schedule.medicineId $var  ORDER BY medicines.medicineId ";
                 }    
                    
                $rs1=mysqli_query($conn,$sql1);
                $data23=mysqli_num_rows($rs1);
                 $i=1;
                if($data23 > 0)
                {
                 while($data=mysqli_fetch_assoc($rs1)){
           
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
                                          <td><?php echo date('d-m-Y',strtotime($data['expiryDate']));?></td>
                                          <td><?php if($data['image']!=''){  ?>
                                           <a href="<?php echo $base_url;?>uploads/<?php echo $data['image'];?>" target="_blank"><?php echo $base_url;?>uploads/<?php echo $data['image']?>"  
                                          <?php } ?></a>
                                          </td>
                                           <td><?php if($data['prescription']!=''){  ?>
                                           <a href="<?php echo $base_url;?>uploads/<?php echo $data['prescription'];?>" target="_blank"> <?php echo $base_url;?>uploads/<?php echo $data['prescription'];?>
                                          <?php } ?></a>
                                          </td>
                                          <td><?php echo $data['importance'];?></td>
                                          <td><?php echo date('d-m-Y',strtotime($data['createdDate']));?></td>                            
                                          <td>
                                              
                                            <a href="<?php echo $base_url;?>admin/actionMedicine.php?id=<?php echo $data['medicineId']; ?>&userid=<?php echo $data['userId']; ?>&submit=taken">Taken</a>
                                          <?php if($_SESSION['user_permission'][4]['moduleId']=='5' && $_SESSION['user_permission'][4]['permissionEdit']=='Y'){ ?>
                                            <a href="<?php echo $base_url;?>admin/updatemedicine.php?id=<?php echo $data['medicineId']; ?>"><i class="fa fa-edit"></i></a>
                                          <?php } if($_SESSION['user_permission'][4]['moduleId']=='5' && $_SESSION['user_permission'][4]['permissionDelete']=='Y'){ ?>
                                            <a href="<?php echo $base_url;?>admin/actionMedicine.php?id=<?php echo $data['medicineId']; ?>&userid=<?php echo $data['userId']; ?>&submit=delete"><i class="fa fa-trash"></i></a>
                                          <?php } ?>
                                          </td>
                                      </tr>

                              <?php $i++; 
                            }  ?>                        
                      
 
<?php }?>