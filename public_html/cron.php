<?php

// error_reporting(1);
include_once('config.php');

        date_default_timezone_set('Asia/Kolkata');
        
        $date=date('Y-m-d');
        $Today=strtolower(date('l', strtotime($date)));
        $firstTime = (new DateTime)->format('H:i:s')."<br/>";
        $secondTime = (new DateTime)->modify('+30 minutes')->format('H:i:s');

       $sql1="SELECT medicine_schedule.notification,medicines.name,medicines.meansTotake,medicines.userId,medicines.medicineId,medicine_schedule.day,medicine_schedule.scheduleId,medicine_schedule.medTime,medicines.createdDate,medicines.updateDate
           FROM `medicines` LEFT JOIN medicine_schedule on medicines.medicineId=medicine_schedule.medicineId 
           WHERE medicine_schedule.day LIKE '%$Today%'  AND medicine_schedule.medTime >= '$firstTime' AND medicine_schedule.medTime <= '$secondTime'";

        $rs1=mysqli_query($conn,$sql1);
        $data1=mysqli_num_rows($rs1); 

      if($data1 > 0)
      {
            while($data2=mysqli_fetch_assoc($rs1))
            {
               if($data2['notification']=='N')
                {     
                        $sql3="SELECT userId,email FROM `user` WHERE userId= '".$data2['userId']."'";
                        $rs3=mysqli_query($conn,$sql3);
                        $data3=mysqli_fetch_assoc($rs3);
                        $email=$data3['email'];
                      
                                 require_once('phpmailer/class.phpmailer.php');
                                         
                                            $mail = new PHPMailer; // the true param means it will throw exceptions on errors, which we need to catch
                                            $mail->IsSMTP(); // telling the class to use SMTP

                                                    
                                            // $mail->SMTPDebug = 2; 
                                            // $mail->AuthType = 'NTLM';                           // Set mailer to use SMTP
                                            $mail->Host       = "remembermedicines.com";                      // Specify main and backup server
                                            $mail->SMTPAuth = true;                               // Enable SMTP authentication
                                            $mail->Username   = "info@remembermedicines.com"; // SMTP account username
                                            $mail->Password   = "glow@123";                // SMTP password
                                            $mail->SMTPSecure = 'ssl';                            // Enable encryption, 'ssl' also accepted
                                            $mail->Port = 465;                                    //Set the SMTP port number - 587 for authenticated TLS
                                            $mail->setFrom('noreply@remembermedicines.com','Remember Medicines');     //Set who the message is to be sent from
                                            // $mail->addReplyTo('info@remembermedicines.com');  //Set an alternative reply-to address
                                            $mail->addAddress('sonal.sahu1810.ss@gmail.com');  // Add a recipient
                                       
                                             //$mail->isHTML(true);                                  // Set email format to HTML

                                            $mail->Subject = 'Reminder of Medicines';
                            
                                  	  $message .= '<html><body>';
                                         $message .= '<table>';
                                          $message .= "<tr>

                                                     </td></tr>";
                                           $message .= '</table>';
                                            $message .= '</body></html>';
                                       
                                      
                                         $message .= '<html><body>';
                                         $message .= '<table>';
                                       
                                        
						               $message .= "<tr><td <p>Medicine Name <h5>".$data2['name']."</h5></td></tr>";
						              $message .= "<tr><td> <p>Time  <h5>".$data2['medTime']."</h5></td></tr>";            							               
						              $message .= "<tr><td> <p>Means to take <h5>".$data2['meansTotake']."</h5></td></tr>";   
						              
                                        $message .= '</table>';
                                        $message .= '</body></html>';
                                          
                         
                                $mail->msgHTML($message);
                                if(!$mail->send()) {
                                    // echo ("<script LANGUAGE='JavaScript'>
                                    // window.alert(' Mail could not be sent');
                                    // window.location.href='forgotPassword.php';
                                    //  </script>");
                                     echo 'Mailer Error: ' . $mail->ErrorInfo;
                                   //exit;
                                }  
                                // else{
                                     echo 'sended';
                                // } 
                                
                         $sqlQ="UPDATE `medicine_schedule` SET `notification`='Y' WHERE scheduleId='".$data2['scheduleId']."'";
                         $rsQ=mysqli_query($conn,$sqlQ);
                }
            }
      }
      else{
            echo "data not found";
         }

mysqli_close($conn);
// enable_lock_cronjob(FALSE);
?>