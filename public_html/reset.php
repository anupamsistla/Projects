<?php

include_once('config.php');
session_start();
//print_r($_SESSION);

//  print_r($_POST);
// exit;
$email=$_POST['email'];
if($_POST['submit']=='forgot'){
    global $conn; 
    $sql = "SELECT * FROM `user` WHERE email = '$email'";
    $rs=mysqli_query($conn,$sql);
    $data =mysqli_fetch_assoc($rs); 
     
    if($data > 0 || $data !="")
    {
                             date_default_timezone_set('Asia/Kolkata');
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
                                            $mail->setFrom('noreply@remembermedicines.com','remembermedicines');     //Set who the message is to be sent from
                                            // $mail->addReplyTo('info@remembermedicines.com');  //Set an alternative reply-to address
                                            $mail->addAddress($email);  // Add a recipient
                                       
                                             //$mail->isHTML(true);                                  // Set email format to HTML

                                            $mail->Subject = 'Your Password';
                            
                                  	  $message .= '<html><body>';
                                         $message .= '<table>';
                                          $message .= "<tr>

                                                     </td></tr>";
                                           $message .= '</table>';
                                            $message .= '</body></html>';
                                       
                                      
                                         $message .= '<html><body>';
                                         $message .= '<table>';
                                       
                                        
            							               $message .= "<tr><td> <p>Your Current Password <h1>".$data['password']."</h1></td></tr>";
            							
                                        $message .= '</table>';
                                        $message .= '</body></html>';
                                          
                         
                        //   $_SESSION['email'] = $data['email'];
                            
                                $mail->msgHTML($message);
                                if(!$mail->send()) {
                                    echo ("<script LANGUAGE='JavaScript'>
                                    window.alert(' Mail could not be sent');
                                    window.location.href='forgotPassword.php';
                                     </script>");
                                // echo 'Mailer Error: ' . $mail->ErrorInfo;
                                   exit;
                                }
                            else{
                            //   echo 'Mailer Error: ' . $mail->ErrorInfo;
//                                   exit;
                                 echo ("<script LANGUAGE='JavaScript'>
                                  window.alert('Please Check Your Mail.');
                                    window.location.href='login.php';
                                     </script>");

                                      				
                                  }   
                          }                   

     // print_r($_SESSION);

else{
            echo ("<script LANGUAGE='JavaScript'>
               alert('you are not registered user');
                       window.location.href='signup.php';
                        </script>");
                                    
      }

}
	
?>