<?php
	include_once('config.php');
?>
<!DOCTYPE html>
<html lang="en" >
<head>
        <meta charset="UTF-8">
        <title>Remember Medicines</title>
        <meta name="viewport" content="width=device-width, maximum-scale=1, minimum-scale=1">
        <link href="https://fonts.googleapis.com/css?family=Rubik:400,700|Crimson+Text:400,400i" rel="stylesheet">
        <meta name="description" content="Try and test HTML code online in a simple and easy way using our free HTML editor and see the results in real-time." />
        <meta charset="UTF-8" />
        <meta property="og:title" content="Bootstrap 4 Responsive Layout Example" />
        <meta property="og:description" content="View the live example as well as try and test it using the online HTML editor." />
        <meta name="robots" content="noindex, nofollow">
        <link rel="icon" href="<?php echo $base_url;?>assets/images/remember_medicines.png" type="image/x-icon">
        <link rel="stylesheet" href="<?php echo $base_url;?>assets/css/loginstyle.css">
        <link rel="stylesheet" href="https://code.jquery.com/ui/1.10.4/themes/smoothness/jquery-ui.css">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
          <script src="https://www.google.com/recaptcha/api.js" async defer></script>
</script>
</head>
<body>
 <div class="login-container">
       <form name="signupform" id="signupform" action="<?php echo $base_url;?>actionLogin.php" method="post">
           <a href="<?php echo $base_url;?>" style="text-align: center;"><img alt="image" src="<?php echo $base_url; ?>assets/images/remember_medicines.png" class="header-logo" /> </a>
          <div class="row form-group"> 
               <div class="col-12 col-lg-6">
                   <label>Name <span>*</span></label>
                   <input class="form-control" type="text" name="name" placeholder="Enter your name here" id="name" />
               </div>
                
                <div class="col-12 col-lg-6">
                   <label>Username <span>*</span></label>
                   <input class="form-control" type="text" name="username" placeholder="Enter your username here" id="username" />
               </div>
           </div>
           <div class="row form-group"> 
               <div class="col-12 col-lg-12">              
                     <label>Email <span>*</span></label> 
                     <input class="form-control" type="email" name="email" placeholder="Enter your email here" id="email" />
               </div>
           </div>

           <div class="row form-group"> 
               <div class="col-12 col-lg-6">              
                     <label>Age <span id="marker">*</span></label>
                     <input class="form-control" type="text" name="age" placeholder="Enter your age here" id="age" />
               </div>
                <div class="col-12 col-lg-6">
                    <label>Gender  <span  id="marker"></span></label>
                    <select class="form-control" name="gender" id="gender" >
                      <option value="">Select Gender</option>
                      <option value="Male">Male</option>
                      <option value="Female">Female</option>
                      <option value="Other">Other</option>
                    </select>
              </div>
           </div>
            <div class="row form-group"> 
               <div class="col-12 col-lg-12">
                   <label>Medical Condition <span id="marker">*</span></label>
                   <input class="form-control" type="text" name="medicalCondition" placeholder="Enter your medical condition here" id="medicalCondition" />
               </div>
           </div>
           <div class="row form-group"> 
               <div class="col-12 col-lg-6">              
                     <label>Password <span id="marker">*</span></label>
                     <input class="form-control" type="password" name="password" placeholder="Enter your password here" id="password" />
               </div>
                <div class="col-12 col-lg-6">
                    <label>Confirm Password <span id="marker">*</span></label>
                    <input class="form-control" type="password" name="confirmpassword" placeholder="Confirm password" id="confirmpassword" />
              </div>
           </div>
           <input type="submit" name="login" value="Sign Up"  />   
            <div class="g-recaptcha" data-sitekey='6LfYfJgbAAAAAGpZgA4EOVZr72_GbEN6Xnj06PG3' style="padding-top:10px;"></div>
       </form>
            <p style="text-align: center;">If you already have registered, <a style="font-size: 14px;display: inline-block;" href="<?php echo $base_url;?>login.php">Login</a></p>
            
            
          <!--Site key-6LfkW5gbAAAAAInTOHJ5ju-puTLugeQ47-S7CCMd-->
          <!--Secret key-6LfkW5gbAAAAAPs-jaAMHGLxP2LsAe1B9wkmcS6k-->
                
   </div>	


  <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.0/jquery.min.js" ></script> 
  <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-validate/1.19.1/jquery.validate.min.js" ></script> 
  <script src="<?php echo $base_url;?>assets/js/signup_validation.js" ></script> 
  <!-- <script src="http://code.jquery.com/jquery-1.9.1.js" ></script> -->
  <script src="https://code.jquery.com/ui/1.10.4/jquery-ui.js" ></script>
 <script>
//   function onSubmit(token) {
//      document.getElementById("signupform").submit();
//   }
 </script>
 <script type="text/javascript">
  var onloadCallback = function() {
    alert("grecaptcha is ready!");
  };
</script>